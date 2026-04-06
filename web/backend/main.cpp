#include <iostream>
#include <string>
#include <map>
#include "include/httplib.h"
#include "models/Pesanan.h"
#include "data_structures/Queue.h"
#include "data_structures/Stack.h"

using namespace std;
using namespace httplib;

static Queue antreanCucian;
static Stack riwayatCucian;

static json pesananToJson(const Pesanan& p) {
    json j;
    j["namaPelanggan"] = p.namaPelanggan;
    j["jenisSepatu"] = static_cast<int>(p.jenisSepatu);
    j["jenisSepatuStr"] = p.toStringSepatu();
    j["jenisLayanan"] = static_cast<int>(p.jenisLayanan);
    j["jenisLayananStr"] = p.toStringLayanan();
    j["durasiLayananMenit"] = p.durasiLayananMenit;
    j["estimasiSelesai"] = p.estimasiSelesai;
    return j;
}

static string okJson(const json& j) {
    json r;
    r["success"] = true;
    r["data"] = j;
    return r.dump();
}

static string okMsg(const string& msg) {
    json r;
    r["success"] = true;
    r["message"] = msg;
    return r.dump();
}

static string errJson(const string& msg, int code = 400) {
    json r;
    r["success"] = false;
    r["message"] = msg;
    r["code"] = code;
    return r.dump();
}

int main() {
    Server srv;

    // CORS
    srv.set_pre_routing_handler([](const Request& req, Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
        if (req.method == "OPTIONS") {
            res.status = 204;
            return Server::HandlerResponse::Handled;
        }
        return Server::HandlerResponse::Unhandled;
    });

    // GET /
    srv.Get("/", [](const Request&, Response& res) {
        json j;
        j["status"] = "ok";
        j["service"] = "ASD Shoe Laundry API";
        res.set_content(j.dump(), "application/json");
    });

    // GET /queue
    srv.Get("/queue", [&](const Request&, Response& res) {
        json::array_t items;
        antreanCucian.traverse([&](const Pesanan& p) {
            items.push_back(pesananToJson(p));
        });
        json r;
        r["success"] = true;
        r["data"] = items;
        r["count"] = antreanCucian.size();
        res.set_content(r.dump(), "application/json");
    });

    // POST /queue
    srv.Post("/queue", [&](const Request& req, Response& res) {
        try {
            auto body = json::parse(req.body);

            Pesanan p;
            p.namaPelanggan = body.value("namaPelanggan", "");
            p.jenisSepatu = static_cast<JenisSepatu>(body.value("jenisSepatu", 0));
            p.jenisLayanan = static_cast<JenisLayanan>(body.value("jenisLayanan", 0));
            p.durasiLayananMenit = Pesanan::getDurasi(p.jenisLayanan);

            if (p.namaPelanggan.empty()) {
                res.set_content(errJson("namaPelanggan is required"), "application/json");
                res.status = 400;
                return;
            }

            int baseEstimasi = 0;
            antreanCucian.traverse([&](const Pesanan& ex) {
                baseEstimasi += ex.durasiLayananMenit;
            });
            p.estimasiSelesai = baseEstimasi + p.durasiLayananMenit;

            antreanCucian.enqueue(p);
            antreanCucian.calculateTime();

            json r;
            r["success"] = true;
            r["message"] = "Pesanan ditambahkan ke antrean";
            r["data"] = pesananToJson(p);
            res.set_content(r.dump(), "application/json");
        } catch (const exception& e) {
            res.set_content(errJson(string("Error: ") + e.what(), 500), "application/json");
        }
    });

    // PUT /queue/:index
    srv.Put(R"(/queue/(\d+))", [&](const Request& req, Response& res) {
        try {
            int idx = stoi(req.matches[1]);

            Pesanan* target = antreanCucian.getAt(idx);
            if (!target) {
                res.set_content(errJson("Index out of range"), "application/json");
                res.status = 400;
                return;
            }

            auto body = json::parse(req.body);

            if (body.contains("namaPelanggan"))
                target->namaPelanggan = body["namaPelanggan"].get<string>();
            if (body.contains("jenisSepatu"))
                target->jenisSepatu = static_cast<JenisSepatu>(body["jenisSepatu"].get<int>());
            if (body.contains("jenisLayanan")) {
                target->jenisLayanan = static_cast<JenisLayanan>(body["jenisLayanan"].get<int>());
                target->durasiLayananMenit = Pesanan::getDurasi(target->jenisLayanan);
            }

            antreanCucian.calculateTime();

            json r;
            r["success"] = true;
            r["message"] = "Pesanan diupdate";
            r["data"] = pesananToJson(*target);
            res.set_content(r.dump(), "application/json");
        } catch (const exception& e) {
            res.set_content(errJson(e.what(), 500), "application/json");
        }
    });

    // DELETE /queue/:index
    srv.Delete(R"(/queue/(\d+))", [&](const Request& req, Response& res) {
        try {
            int idx = stoi(req.matches[1]);

            if (!antreanCucian.removeAt(idx)) {
                res.set_content(errJson("Index out of range"), "application/json");
                res.status = 400;
                return;
            }
            antreanCucian.calculateTime();

            res.set_content(okMsg("Pesanan dihapus dari antrean"), "application/json");
        } catch (const exception& e) {
            res.set_content(errJson(e.what(), 500), "application/json");
        }
    });

    // DELETE /queue/process
    srv.Delete("/queue/process", [&](const Request&, Response& res) {
        try {
            if (antreanCucian.isEmpty()) {
                res.set_content(errJson("Antrean kosong"), "application/json");
                res.status = 400;
                return;
            }

            Pesanan p = antreanCucian.dequeue();
            riwayatCucian.push(p);
            antreanCucian.calculateTime();

            json r;
            r["success"] = true;
            r["message"] = "Pesanan selesai diproses";
            r["data"] = pesananToJson(p);
            res.set_content(r.dump(), "application/json");
        } catch (const exception& e) {
            res.set_content(errJson(e.what(), 500), "application/json");
        }
    });

    // GET /history
    srv.Get("/history", [&](const Request&, Response& res) {
        json::array_t items;
        riwayatCucian.traverse([&](const Pesanan& p) {
            items.push_back(pesananToJson(p));
        });
        json r;
        r["success"] = true;
        r["data"] = items;
        r["count"] = riwayatCucian.size();
        res.set_content(r.dump(), "application/json");
    });

    // GET /history/latest
    srv.Get("/history/latest", [&](const Request&, Response& res) {
        Pesanan* p = riwayatCucian.peek();
        if (!p) {
            res.set_content(errJson("Belum ada riwayat", 404), "application/json");
            return;
        }
        json r;
        r["success"] = true;
        r["data"] = pesananToJson(*p);
        res.set_content(r.dump(), "application/json");
    });

    // GET /report
    srv.Get("/report", [&](const Request&, Response& res) {
        int qCount[5] = {0}, sCount[5] = {0};

        antreanCucian.traverse([&](const Pesanan& p) {
            int idx = static_cast<int>(p.jenisLayanan);
            if (idx >= 0 && idx < 5) qCount[idx]++;
        });
        riwayatCucian.traverse([&](const Pesanan& p) {
            int idx = static_cast<int>(p.jenisLayanan);
            if (idx >= 0 && idx < 5) sCount[idx]++;
        });

        json::array_t layanan;
        string names[] = {"Regular", "Deep Cleaning", "Repair", "Repaint", "Whitening"};
        for (int i = 0; i < 5; i++) {
            json l;
            l["name"] = names[i];
            l["inQueue"] = qCount[i];
            l["completed"] = sCount[i];
            l["total"] = qCount[i] + sCount[i];
            layanan.push_back(l);
        }

        int totalQ = 0, totalS = 0;
        for (int i = 0; i < 5; i++) { totalQ += qCount[i]; totalS += sCount[i]; }

        json data;
        data["layanan"] = layanan;
        data["totalInQueue"] = totalQ;
        data["totalCompleted"] = totalS;
        data["totalAll"] = totalQ + totalS;

        json r;
        r["success"] = true;
        r["data"] = data;
        res.set_content(r.dump(), "application/json");
    });

    const char* PORT_ENV = getenv("PORT");
    int PORT = PORT_ENV ? atoi(PORT_ENV) : 8080;

    cout << "==============================================\n";
    cout << "  ASD Shoe Laundry API\n";
    cout << "  Running on http://0.0.0.0:" << PORT << "\n";
    cout << "==============================================\n";

    srv.listen("0.0.0.0", PORT);
    return 0;
}
