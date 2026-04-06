#include <iostream>
#include <limits>
#include "ui.h"
#include "models/Pesanan.h"
#include "data_structures/Queue.h"
#include "data_structures/Stack.h"
using namespace std;

void tampilMenu() {
        cout << "\n=== SISTEM ANTREAN CUCI SEPATU ===\n";
        cout << "1. Tambah Pesanan Baru (Antrean)\n";
        cout << "2. Proses Pesanan Berikutnya\n";
        cout << "3. Tampil pesanan terakhir diproses\n";
        cout << "4. Tampil antrean\n";
        cout << "5. Tampil riwayat\n";
        cout << "6. Edit Pesanan dalam Antrean\n";
        cout << "7. Hapus Pesanan dari Antrean\n";
        cout << "8. Tampilkan Laporan\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
}
    
void pauseSebelumMenu() {
    cout << "\nTekan Enter untuk kembali ke menu...";
    cin.get();
}
    
void clearConsole() {
    // ANSI escape code to clear screen (2J) and move cursor to top-left (H)
    std::cout << "\x1B[2J\x1B[H";
    std::cout.flush(); // Ensure the command is sent immediately
}

bool konfirmasiSebelumEnqueue(const Pesanan& pesananBaru) {
    while (true) {
        clearConsole();
        cout << "=== Rincian Pesanan yang akan ditambahkan ===\n" << endl
            << "Nama\t\t\t: " << pesananBaru.namaPelanggan << endl
            << "Jenis Sepatu\t\t: " << toString(pesananBaru.jenisSepatu) << endl
            << "Jenis Layanan\t\t: " << toString(pesananBaru.jenisLayanan) << endl
            << "Estimasi Selesai dalam\t\t: " << pesananBaru.estimasiSelesai << " menit" << endl
            << "---------------------------------------\n" << endl;
        
        cout << "\nTekan Enter untuk konfirmasi, ketik C lalu Enter untuk membatalkan pesanan: ";
        string input;
        getline(cin, input);
        
        if (input.empty()) return true;                 // hanya enter
        if (input == "c" || input == "C") return false; // cancel

        cout << "Input tidak valid. Hanya Enter atau C.\n";
        cout << "Tekan Enter untuk coba lagi...";
        getline(cin, input);
    }
}

// ============================================================
// Fitur Edit Pesanan
// ============================================================
bool formEditPesanan(Queue& antrean) {
    if (antrean.isEmpty()) {
        cout << "\n=> Antrean kosong, tidak ada pesanan yang bisa diedit.\n";
        return false;
    }

    antrean.display();

    int nomor;
    cout << "\nMasukkan nomor pesanan yang ingin diedit: ";
    if (!(cin >> nomor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input harus angka!\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int idx = nomor - 1; // konversi ke 0-based
    Node* node = antrean.getAt(idx);
    if (node == nullptr) {
        cout << "=> Pesanan dengan nomor tersebut tidak ditemukan.\n";
        return false;
    }

    Pesanan& p = node->data;

    // Edit nama
    cout << "\n-- Edit Pesanan --\n";
    cout << "Nama saat ini    : " << p.namaPelanggan << endl;
    cout << "Nama baru (kosong = tidak diubah): ";
    string namaBaru;
    getline(cin, namaBaru);
    if (!namaBaru.empty()) p.namaPelanggan = namaBaru;

    // Edit jenis sepatu
    cout << "\nJenis Sepatu saat ini: " << toString(p.jenisSepatu) << endl;
    cout << "Jenis Sepatu baru (0 = tidak diubah):" << endl
         << "1. Sneakers  2. Boots  3. Sandals  4. Formal  5. Olahraga" << endl
         << "Pilihan: ";
    int pilihSepatu;
    if (cin >> pilihSepatu && pilihSepatu != 0) {
        if (fromChoiceSepatu(pilihSepatu, p.jenisSepatu)) {
            cout << "=> Jenis sepatu updated.\n";
        } else {
            cout << "Pilihan tidak valid, jenis sepatu tetap.\n";
            p.jenisSepatu = p.jenisSepatu; // tidak berubah
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Edit jenis layanan
    cout << "\nJenis Layanan saat ini: " << toString(p.jenisLayanan)
         << " (" << p.durasiLayananMenit << " menit)" << endl;
    cout << "Jenis Layanan baru (0 = tidak diubah):" << endl
         << "1. Regular  2. Deep Cleaning  3. Repair  4. Repaint  5. Whitening" << endl
         << "Pilihan: ";
    int pilihLayanan;
    if (cin >> pilihLayanan && pilihLayanan != 0) {
        if (fromChoiceLayanan(pilihLayanan, p.jenisLayanan)) {
            p.durasiLayananMenit = durasiStandarMenit(p.jenisLayanan);
            cout << "=> Jenis layanan & durasi updated.\n";
        } else {
            cout << "Pilihan tidak valid, jenis layanan tetap.\n";
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Regenerate estimasi setelah edit
    antrean.calculateTime();

    cout << "\n=> Pesanan berhasil diedit.\n";
    return true;
}

// ============================================================
// Fitur Laporan
// ============================================================
void tampilLaporan(const Queue& antrean, const Stack& riwayat) {
    // Count per jenis layanan
    int countQueue[5] = {0};
    int countStack[5] = {0};

    // Traverse queue
    antrean.traverse([&](const Pesanan& p) {
        countQueue[static_cast<int>(p.jenisLayanan)]++;
    });

    // Traverse stack
    riwayat.traverse([&](const Pesanan& p) {
        countStack[static_cast<int>(p.jenisLayanan)]++;
    });

    const char* namaLayanan[] = {
        "Regular", "Deep Cleaning", "Repair", "Repaint", "Whitening"
    };

    cout << "\n======================================================\n";
    cout << "              LAPORAN PESANAN\n";
    cout << "======================================================\n";
    cout << "Layanan        | Dalam Antrean | Selesai | Total\n";
    cout << "----------------------------------------------------\n";

    int totalQueue = 0, totalStack = 0, totalAll = 0;
    for (int i = 0; i < 5; i++) {
        int t = countQueue[i] + countStack[i];
        cout << namaLayanan[i] << "    |       "
             << countQueue[i] << "       |   "
             << countStack[i] << "    |  "
             << t << "\n";
        totalQueue += countQueue[i];
        totalStack += countStack[i];
        totalAll   += t;
    }
    cout << "----------------------------------------------------\n";
    cout << "Total          |       "
         << totalQueue << "       |   "
         << totalStack << "    |  "
         << totalAll << "\n";
    cout << "======================================================\n";
}