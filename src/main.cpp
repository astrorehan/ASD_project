#include <iostream>
#include <limits>
#include <string>
#include "models/Pesanan.h"
#include "data_structures/Queue.h"
#include "data_structures/Stack.h"

using namespace std;

void tampilMenu();
void pauseSebelumMenu();
void clearConsole();

int main() {
    Queue antreanCucian; // Object Queue untuk antrean
    Stack riwayatCucian; // Object Stack untuk riwayat
    
    int pilihan;
    
    do {
        clearConsole();
        tampilMenu();
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInput tidak valid. Masukkan angka menu.\n";
            pauseSebelumMenu();
            continue;
        }
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        switch (pilihan) {
            case 0:
            clearConsole();
            cout << "Keluar dari program...\n";
            break;
            case 1: {
                clearConsole();
                bool batalTambah = false;
                
                // Menambahkan pesanan ke antrean                
                Pesanan pesananBaru;
                
                cout << "\n-- Form Pesanan Baru --\n";
                cout << "Nama Pelanggan  : ";
                cin >> ws; // Membersihkan buffer enter sebelumnya
                getline(cin, pesananBaru.namaPelanggan);
                
                int pilihSepatu;
                bool validSepatu = false;

                do {
                    clearConsole();

                    cout << "Jenis Sepatu :" << endl
                        << "0. Cancel\n"
                        << "1. Sneakers\n"
                        << "2. Boots\n"
                        << "3. Sandals\n"
                        << "4. Formal\n"
                        << "5. Olahraga" << endl;

                    cout << "Pilihan : ";
                    cin >> pilihSepatu;

                    // VALIDASI INPUT
                    if (!cin){
                        cin.clear(); // Ngehapus status error di cin
                        cin.ignore(numeric_limits<streamsize>::max(),'\n'); /// Kalau bingung ini apa, intinya ngebuang sisa input di buffer SAMPAi \n (newline).
                        cout << "Input harus angka! \n";
                        continue;
                    }
                    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    validSepatu = fromChoiceSepatu(pilihSepatu, pesananBaru.jenisSepatu);
                    
                    if (pilihSepatu == 0) {
                        batalTambah = true;
                        break;
                    }

                    if(!validSepatu) {
                        cout << "Pilihan sepatu tidak valid. \n";
                    }

                } while (!validSepatu);
                
                if (batalTambah) {
                    cout << "=> Tambah pesanan berhasil dibatalkan.\n";
                    break;
                }
                
                int pilihLayanan;
                bool validLayanan = false;
                
                do {
                    clearConsole();
                    
                    cout << "Jenis Layanan :" << endl
                        << "0. Cancel\n"
                        << "1. Regular\n"
                        << "2. Deep Cleaning\n"
                        << "3. Repair\n"
                        << "4. Repaint\n"
                        << "5. Whitening" << endl;
                        
                        cout << "Pilihan : ";
                        cin >> pilihLayanan;

                        // VALIDASI INPUT
                        if (!cin){
                            cin.clear(); // Ngehapus status error di cin
                            cin.ignore(numeric_limits<streamsize>::max(),'\n'); /// Kalau bingung ini apa, intinya ngebuang sisa input di buffer SAMPAi \n (newline).
                            cout << "Input harus angka! \n";
                            continue;
                        }
                       
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        validLayanan = fromChoiceLayanan(pilihLayanan, pesananBaru.jenisLayanan);
                        
                        if (pilihLayanan == 0){
                            batalTambah = true;
                            break;
                        }

                        if(!validLayanan) {
                            cout << "Pilihan layanan tidak valid. \n";
                        }
                    } while (!validLayanan);
                    
                    if (batalTambah) {
                        cout << "=> Tambah pesanan berhasil dibatalkan.\n";
                        break;
                    }
                    
                    antreanCucian.enqueue(pesananBaru);
                    
                    cout << "=> Berhasil! Pesanan " << pesananBaru.namaPelanggan << " masuk ke antrean.\n";
                    break;
                }
            case 2: {
                clearConsole();
                
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
            case 3: {
                clearConsole();
                
                // Menampilkan pesanan terakhir diproses
                riwayatCucian.peek();
                break;
            }
            case 4: {
                clearConsole();
                
                // Menampilkan antrean pesanan
                antreanCucian.display();
                break;
            }
            case 5: {
                clearConsole();
                
                // Menampilkan riwayat pesanan selesai
                riwayatCucian.display();
                break;
            }
            default:
            cout << "Pilihan tidak valid!\n";
        }

        if (pilihan != 0) {
            pauseSebelumMenu();
        }
    } while (pilihan != 0);

    return 0;
};

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
