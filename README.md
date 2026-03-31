# Sistem Antrean Cuci Sepatu (C++)

Project ini adalah implementasi tugas ASD untuk manajemen antrean pelanggan tempat cuci sepatu menggunakan:
- Queue berbasis linked list untuk pesanan yang belum diproses
- Stack berbasis linked list untuk riwayat pesanan selesai

## Tujuan Project

Program CLI ini dirancang agar memenuhi fitur minimum tugas:
1. Menambahkan pesanan ke antrean
2. Memproses pesanan berikutnya
3. Menyimpan hasil proses ke riwayat
4. Menampilkan pesanan terakhir yang diproses
5. Menampilkan antrean pesanan
6. Menampilkan riwayat pesanan selesai

## Data Pesanan

Data yang digunakan pada implementasi saat ini:
- nama pelanggan (string)
- jenis sepatu (enum)
- jenis layanan (enum)

Catatan:
- Jenis sepatu dan layanan dipilih dari opsi bernomor agar input lebih valid.
- Estimasi waktu belum dihitung otomatis pada versi saat ini.

## Struktur Project

```text
ASD_project/
├── docs/
│   ├── flowchart.png
│   ├── pseudocode.md
│   └── analisis_big_o.md
├── src/
│   ├── models/
│   │   └── Pesanan.h
│   ├── data_structures/
│   │   ├── Node.h
│   │   ├── Queue.h
│   │   ├── Queue.cpp
│   │   ├── Stack.h
│   │   └── Stack.cpp
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

Setelah program jalan, menu utama tersedia:
1. Tambah pesanan baru
2. Proses pesanan berikutnya
3. Tampil pesanan terakhir diproses
4. Tampil antrean
5. Tampil riwayat
0. Keluar

Alur demo cepat yang disarankan:
1. Tambah 2 pesanan
2. Tampilkan antrean
3. Proses 1 pesanan
4. Tampilkan pesanan terakhir diproses
5. Tampilkan riwayat

## Kesesuaian Dengan Tahapan Tugas

1. Flowchart dan pseudocode: tersedia di folder docs
2. Implementasi C++ stack/queue linked list: tersedia di folder src
3. Analisis Big O: tersedia di docs/analisis_big_o.md

## Analisis Kompleksitas (Ringkas)

- enqueue: O(1)
- dequeue: O(1)
- push riwayat: O(1)
- peek riwayat: O(1)
- tampil antrean: O(n)
- tampil riwayat: O(n)

## Pengembangan Lanjutan

- Hitung estimasi waktu selesai otomatis berdasarkan jenis layanan
- Simpan dan muat data dari file (Database local, gunanya pas presentasi)
- Tambahkan endpoint backend lokal untuk integrasi web KALAU MAU PAKAI WEB
