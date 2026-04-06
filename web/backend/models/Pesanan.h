#ifndef PESANAN_H
#define PESANAN_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

enum class JenisSepatu {
    SNEAKERS = 0,
    BOOTS = 1,
    SANDALS = 2,
    FORMAL = 3,
    OLAHRAGA = 4
};

enum class JenisLayanan {
    REGULAR = 0,
    DEEP_CLEANING = 1,
    REPAIR = 2,
    REPAINT = 3,
    WHITENING = 4
};

struct Pesanan {
    std::string namaPelanggan;
    JenisSepatu jenisSepatu;
    JenisLayanan jenisLayanan;
    int durasiLayananMenit;
    int estimasiSelesai;

    Pesanan() : jenisSepatu(JenisSepatu::SNEAKERS), jenisLayanan(JenisLayanan::REGULAR),
                 durasiLayananMenit(60), estimasiSelesai(0) {}

    json toJson() const;
    static Pesanan fromJson(const json& j);

    std::string toStringSepatu() const;
    std::string toStringLayanan() const;

    static std::string enumToStringSepatu(JenisSepatu j);
    static std::string enumToStringLayanan(JenisLayanan j);
    static int getDurasi(JenisLayanan layanan);
};

#endif
