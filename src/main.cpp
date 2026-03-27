#include <iostream>
#include <string>
#include "models/Pesanan.h"
#include "data_structures/Queue.h"
#include "data_structures/Stack.h"

using namespace std;

int main() {
    Queue antreanCucian; // Object Queue untuk antrean
    Stack riwayatCucian; // Object Stack untuk riwayat
    
    int pilihan;

    do {
        cout << "\n=== SISTEM ANTREAN CUCI SEPATU ===\n";
        cout << "1. Tambah Pesanan Baru (Antrean)\n";
        cout << "2. Proses Pesanan Berikutnya\n";
        cout << "3. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                // Menambahkan pesanan ke antrean
                Pesanan pesananBaru;
                
                cout << "\n-- Form Pesanan Baru --\n";
                cout << "Nama Pelanggan  : ";
                cin >> ws; // Membersihkan buffer enter sebelumnya
                getline(cin, pesananBaru.namaPelanggan);
                
                cout << "Jenis Sepatu    : ";
                getline(cin, pesananBaru.jenisSepatu);
                
                cout << "Jenis Layanan   : ";
                getline(cin, pesananBaru.jenisLayanan);

                antreanCucian.enqueue(pesananBaru);
                
                cout << "=> Berhasil! Pesanan " << pesananBaru.namaPelanggan << " masuk ke antrean.\n";
                break;
            }
            case 2: {
                // Memproses pesanan berikutnya
                if (antreanCucian.isEmpty()) {
                    cout << "\n=> Antrean masih kosong, tidak ada pesanan yang bisa diproses.\n";
                } else {
                    Pesanan pesananDiproses = antreanCucian.dequeue();
                    
                    cout << "\n=> Memproses pesanan atas nama: " << pesananDiproses.namaPelanggan << "...\n";
                    cout << "=> Cuci sepatu selesai!\n";

                    // Menyimpan hasil proses ke riwayat
                    riwayatCucian.push(pesananDiproses);
                    
                    cout << "=> Pesanan berhasil dipindahkan ke Riwayat Selesai.\n";
                }
                break;
            }
            case 3:
                cout << "Keluar dari program...\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 3);

    return 0;
}