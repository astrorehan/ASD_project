#include <iostream>
#include "ui.h"
#include "models/Pesanan.h"
using namespace std;

void tampilMenu() {
        cout << "\n=== SISTEM ANTREAN CUCI SEPATU ===\n";
        cout << "1. Tambah Pesanan Baru (Antrean)\n";
        cout << "2. Proses Pesanan Berikutnya\n";
        cout << "3. Tampil pesanan terakhir diproses\n";
        cout << "4. Tampil antrean\n";
        cout << "5. Tampil riwayat\n";
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