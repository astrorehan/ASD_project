#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "data_structures/Queue.h"
#include "data_structures/Stack.h"

namespace {

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

JenisLayanan inputJenisLayanan() {
    while (true) {
        std::cout << "Jenis layanan:\n";
        std::cout << "1. Cleaning\n";
        std::cout << "2. Treatment\n";
        std::cout << "3. Repair\n";
        std::cout << "Pilihan layanan: ";

        int pilihan = 0;
        std::cin >> pilihan;

        if (std::cin.fail()) {
            if (std::cin.eof()) {
                return JenisLayanan::Cleaning;
            }
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Input layanan tidak valid.\n";
            continue;
        }

        clearInputBuffer();

        switch (pilihan) {
            case 1:
                return JenisLayanan::Cleaning;
            case 2:
                return JenisLayanan::Treatment;
            case 3:
                return JenisLayanan::Repair;
            default:
                std::cout << "Pilihan tidak tersedia.\n";
                break;
        }
    }
}

void tampilkanDaftar(const std::vector<Pesanan>& daftar) {
    if (daftar.empty()) {
        std::cout << "Tidak ada data.\n";
        return;
    }

    for (const auto& pesanan : daftar) {
        std::cout << "- " << pesanan.ringkasan() << "\n";
    }
}

}  // namespace

int main() {
    Queue antrean;
    Stack riwayat;
    int nextId = 1;

    bool running = true;
    while (running) {
        std::cout << "===== Sistem Antrean Cuci Sepatu =====\n";
        std::cout << "1. Tambah pesanan ke antrean\n";
        std::cout << "2. Proses pesanan berikutnya\n";
        std::cout << "3. Tampilkan pesanan terakhir diproses\n";
        std::cout << "4. Tampilkan antrean pesanan\n";
        std::cout << "5. Tampilkan riwayat pesanan selesai\n";
        std::cout << "0. Keluar\n";
        std::cout << "Pilih menu: ";

        int pilihanMenu = 0;
        std::cin >> pilihanMenu;

        if (std::cin.fail()) {
            if (std::cin.eof()) {
                break;
            }
            std::cin.clear();
            clearInputBuffer();
            std::cout << "Input menu tidak valid.\n\n";
            continue;
        }

        clearInputBuffer();

        switch (pilihanMenu) {
            case 1: {
                std::string nama;
                std::string jenisSepatu;
                std::string estimasi;

                std::cout << "Nama pelanggan: ";
                std::getline(std::cin, nama);
                std::cout << "Jenis sepatu: ";
                std::getline(std::cin, jenisSepatu);
                JenisLayanan layanan = inputJenisLayanan();
                std::cout << "Estimasi selesai: ";
                std::getline(std::cin, estimasi);

                Pesanan baru(nextId++, nama, jenisSepatu, layanan, estimasi);
                antrean.enqueue(baru);
                std::cout << "Pesanan ditambahkan: " << baru.ringkasan() << "\n\n";
                break;
            }
            case 2: {
                Pesanan diproses;
                if (!antrean.dequeue(diproses)) {
                    std::cout << "Antrean kosong.\n\n";
                    break;
                }
                riwayat.push(diproses);
                std::cout << "Pesanan diproses: " << diproses.ringkasan() << "\n\n";
                break;
            }
            case 3: {
                Pesanan terakhir;
                if (!riwayat.peek(terakhir)) {
                    std::cout << "Belum ada pesanan yang selesai diproses.\n\n";
                    break;
                }
                std::cout << "Pesanan terakhir diproses: " << terakhir.ringkasan() << "\n\n";
                break;
            }
            case 4:
                std::cout << "Jumlah antrean: " << antrean.size() << "\n";
                tampilkanDaftar(antrean.toVector());
                std::cout << "\n";
                break;
            case 5:
                std::cout << "Jumlah riwayat: " << riwayat.size() << "\n";
                tampilkanDaftar(riwayat.toVector());
                std::cout << "\n";
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Menu tidak tersedia.\n\n";
                break;
        }
    }

    return 0;
}
