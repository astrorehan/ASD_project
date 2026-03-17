#pragma once

#include <sstream>
#include <string>

enum class JenisLayanan {
    Cleaning = 1,
    Treatment = 2,
    Repair = 3
};

inline std::string layananToString(JenisLayanan layanan) {
    switch (layanan) {
        case JenisLayanan::Cleaning:
            return "Cleaning";
        case JenisLayanan::Treatment:
            return "Treatment";
        case JenisLayanan::Repair:
            return "Repair";
        default:
            return "Unknown";
    }
}

class Pesanan {
public:
    Pesanan() = default;

    Pesanan(int id,
            const std::string& nama,
            const std::string& jenisSepatu,
            JenisLayanan layanan,
            const std::string& estimasi)
        : id_(id),
          namaPelanggan_(nama),
          jenisSepatu_(jenisSepatu),
          jenisLayanan_(layanan),
          estimasiSelesai_(estimasi) {}

    int getId() const { return id_; }
    const std::string& getNamaPelanggan() const { return namaPelanggan_; }
    const std::string& getJenisSepatu() const { return jenisSepatu_; }
    JenisLayanan getJenisLayanan() const { return jenisLayanan_; }
    const std::string& getEstimasiSelesai() const { return estimasiSelesai_; }

    std::string ringkasan() const {
        std::ostringstream out;
        out << "ID: " << id_
            << " | Nama: " << namaPelanggan_
            << " | Sepatu: " << jenisSepatu_
            << " | Layanan: " << layananToString(jenisLayanan_)
            << " | Estimasi: " << estimasiSelesai_;
        return out.str();
    }

private:
    int id_{};
    std::string namaPelanggan_;
    std::string jenisSepatu_;
    JenisLayanan jenisLayanan_{JenisLayanan::Cleaning};
    std::string estimasiSelesai_;
};
