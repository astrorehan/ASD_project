#include "Pesanan.h"
#include <sstream>

json Pesanan::toJson() const {
    return {
        {"namaPelanggan", namaPelanggan},
        {"jenisSepatu", static_cast<int>(jenisSepatu)},
        {"jenisLayanan", static_cast<int>(jenisLayanan)},
        {"durasiLayananMenit", durasiLayananMenit},
        {"estimasiSelesai", estimasiSelesai}
    };
}

Pesanan Pesanan::fromJson(const json& j) {
    Pesanan p;
    p.namaPelanggan = j.value("namaPelanggan", "");
    p.jenisSepatu = static_cast<JenisSepatu>(j.value("jenisSepatu", 0));
    p.jenisLayanan = static_cast<JenisLayanan>(j.value("jenisLayanan", 0));
    p.durasiLayananMenit = j.value("durasiLayananMenit", 60);
    p.estimasiSelesai = j.value("estimasiSelesai", 0);
    return p;
}

std::string Pesanan::toStringSepatu() const {
    return enumToStringSepatu(jenisSepatu);
}

std::string Pesanan::toStringLayanan() const {
    return enumToStringLayanan(jenisLayanan);
}

std::string Pesanan::enumToStringSepatu(JenisSepatu j) {
    switch (j) {
        case JenisSepatu::SNEAKERS: return "Sneakers";
        case JenisSepatu::BOOTS: return "Boots";
        case JenisSepatu::SANDALS: return "Sandals";
        case JenisSepatu::FORMAL: return "Formal";
        case JenisSepatu::OLAHRAGA: return "Olahraga";
        default: return "Unknown";
    }
}

std::string Pesanan::enumToStringLayanan(JenisLayanan j) {
    switch (j) {
        case JenisLayanan::REGULAR: return "Regular";
        case JenisLayanan::DEEP_CLEANING: return "Deep Cleaning";
        case JenisLayanan::REPAIR: return "Repair";
        case JenisLayanan::REPAINT: return "Repaint";
        case JenisLayanan::WHITENING: return "Whitening";
        default: return "Unknown";
    }
}

int Pesanan::getDurasi(JenisLayanan layanan) {
    switch (layanan) {
        case JenisLayanan::REGULAR: return 60;
        case JenisLayanan::DEEP_CLEANING: return 90;
        case JenisLayanan::REPAIR: return 120;
        case JenisLayanan::REPAINT: return 150;
        case JenisLayanan::WHITENING: return 75;
        default: return 60;
    }
}
