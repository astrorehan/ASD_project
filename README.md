# Sistem Antrean Cuci Sepatu (C++)

Project ini adalah implementasi tugas ASD untuk manajemen antrean pelanggan tempat cuci sepatu berbasis CLI.

Struktur data yang digunakan:
- Queue (linked list) untuk pesanan yang belum diproses
- Stack (linked list) untuk riwayat pesanan selesai

## Fitur Utama

1. Menambah pesanan baru ke antrean
2. Validasi input agar menu dan pilihan berupa angka
3. Opsi batal saat pilih jenis sepatu/layanan (0 = Cancel)
4. Perhitungan durasi layanan dan estimasi selesai otomatis
5. Konfirmasi sebelum pesanan dimasukkan ke antrean
6. Memproses pesanan berikutnya (dequeue)
7. Memindahkan pesanan selesai ke riwayat (push stack)
8. Menampilkan pesanan terakhir yang diproses (peek)
9. Menampilkan seluruh antrean aktif dan riwayat selesai

## Data Pesanan

Implementasi saat ini menyimpan data berikut:
- namaPelanggan (string)
- jenisSepatu (enum)
- jenisLayanan (enum)
- durasiLayananMenit (int)
- estimasiSelesai (int, menit)

Durasi standar per layanan:
- REGULAR: 60 menit
- DEEP_CLEANING: 90 menit
- REPAIR: 120 menit
- REPAINT: 150 menit
- WHITENING: 75 menit

## Struktur Project

```text
ASD_project/
├── docs/
│   ├── flowchart.png
│   ├── pseudocode.md
│   └── analisis_big_o.md
├── src/
│   ├── data_structures/
│   │   ├── Node.h
│   │   ├── Queue.h
│   │   ├── Queue.cpp
│   │   ├── Stack.h
│   │   └── Stack.cpp
│   ├── models/
│   │   └── Pesanan.h
│   ├── ui/
│   │   ├── ui.h
│   │   └── ui.cpp
│   └── main.cpp
├── bin/
├── build/
├── CMakeLists.txt
└── README.md
```

## Build dan Jalankan (PowerShell)

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\bin\ASD_ShoeLaundryQueue.exe
```

## Cara Pakai Singkat

Setelah program berjalan, menu utama:
1. Tambah pesanan baru
2. Proses pesanan berikutnya
3. Tampil pesanan terakhir diproses
4. Tampil antrean
5. Tampil riwayat
0. Keluar

Alur demo cepat:
1. Tambah 2 pesanan
2. Lihat antrean
3. Proses 1 pesanan
4. Lihat pesanan terakhir diproses
5. Lihat riwayat

## Dokumen Pendukung

1. Flowchart: docs/flowchart.png
2. Pseudocode: docs/pseudocode.md
3. Analisis Big O: docs/analisis_big_o.md

## Analisis Kompleksitas (Ringkas)

- enqueue: O(1)
- dequeue: O(1)
- push riwayat: O(1)
- peek riwayat: O(1)
- display antrean: O(n)
- display riwayat: O(n)
- calculateTime (dipakai saat tambah pesanan): O(n)

Catatan:
- Secara struktur data, enqueue tetap O(1).
- Pada alur fitur saat ini, tambah pesanan memanggil calculateTime lebih dulu untuk estimasi, sehingga total alur tambah bisa melibatkan traversal O(n).

## Rencana Pengembangan

1. Persistensi data ke file lokal
2. Fitur edit/hapus pesanan yang masih dalam antrean
3. Laporan sederhana (jumlah pesanan per jenis layanan)
