#include "FileManager.h"
#include "../vendor/json.hpp"
#include <fstream>
#include <vector>
#include <sys/stat.h>

#ifdef _WIN32
#include <windows.h>
#endif

using json = nlohmann::json;

const std::string FileManager::SAVE_FILE = "data/save.json";

static bool fileExists(const std::string& path) {
#ifdef _WIN32
    DWORD attr = GetFileAttributesA(path.c_str());
    return (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY));
#else
    struct stat st;
    return (stat(path.c_str(), &st) == 0 && S_ISREG(st.st_mode));
#endif
}

void FileManager::save(const Queue& antrean, const Stack& riwayat) {
    nlohmann::json j;

    // Serialize queue (FIFO: front to rear)
    std::vector<nlohmann::json> queueArr;
    antrean.traverse([&](const Pesanan& p) {
        queueArr.push_back({
            {"namaPelanggan", p.namaPelanggan},
            {"jenisSepatu",  static_cast<int>(p.jenisSepatu)},
            {"jenisLayanan", static_cast<int>(p.jenisLayanan)},
            {"durasiLayananMenit", p.durasiLayananMenit},
            {"estimasiSelesai", p.estimasiSelesai}
        });
    });
    j["queue"] = queueArr;

    // Serialize stack (LIFO: top to bottom)
    std::vector<nlohmann::json> stackArr;
    riwayat.traverse([&](const Pesanan& p) {
        stackArr.push_back({
            {"namaPelanggan", p.namaPelanggan},
            {"jenisSepatu",  static_cast<int>(p.jenisSepatu)},
            {"jenisLayanan", static_cast<int>(p.jenisLayanan)},
            {"durasiLayananMenit", p.durasiLayananMenit},
            {"estimasiSelesai", p.estimasiSelesai}
        });
    });
    j["stack"] = stackArr;

    // Ensure data/ directory exists
#ifdef _WIN32
    CreateDirectoryA("data", NULL);
#else
    mkdir("data", 0755);
#endif

    std::ofstream out(SAVE_FILE);
    out << j.dump(2);
    out.close();
}

void FileManager::load(Queue& antrean, Stack& riwayat) {
    if (!fileExists(SAVE_FILE)) return;

    std::ifstream in(SAVE_FILE);
    if (!in.is_open()) return;

    nlohmann::json j;
    in >> j;
    in.close();

    // Collect queue items, then push in reverse (so front = oldest)
    if (j.contains("queue") && j["queue"].is_array()) {
        std::vector<Pesanan> items;
        for (const auto& item : j["queue"]) {
            Pesanan p;
            p.namaPelanggan   = item["namaPelanggan"].get<std::string>();
            p.jenisSepatu    = static_cast<JenisSepatu>(item["jenisSepatu"].get<int>());
            p.jenisLayanan   = static_cast<JenisLayanan>(item["jenisLayanan"].get<int>());
            p.durasiLayananMenit = item["durasiLayananMenit"].get<int>();
            p.estimasiSelesai    = item["estimasiSelesai"].get<int>();
            items.push_back(p);
        }
        // Reverse to restore FIFO order
        for (auto it = items.rbegin(); it != items.rend(); ++it) {
            antrean.enqueue(*it);
        }
        // Regenerate estimasi
        antrean.calculateTime();
    }

    // Stack: items are in LIFO order already (top = first in array)
    if (j.contains("stack") && j["stack"].is_array()) {
        for (const auto& item : j["stack"]) {
            Pesanan p;
            p.namaPelanggan   = item["namaPelanggan"].get<std::string>();
            p.jenisSepatu    = static_cast<JenisSepatu>(item["jenisSepatu"].get<int>());
            p.jenisLayanan   = static_cast<JenisLayanan>(item["jenisLayanan"].get<int>());
            p.durasiLayananMenit = item["durasiLayananMenit"].get<int>();
            p.estimasiSelesai    = item["estimasiSelesai"].get<int>();
            riwayat.push(p);
        }
    }
}
