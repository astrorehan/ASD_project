# Changelog — Pengembangan Fitur Baru

Dokumen ini mencatat penambahan fitur baru yang dikembangkan dari [README.md](./README.md).

---

## Fitur Baru yang Ditambahkan

1. **Edit pesanan** yang masih dalam antrean (Menu 6)
2. **Hapus pesanan** dari antrean (Menu 7)
3. **Laporan sederhana** — jumlah pesanan per jenis layanan (Menu 8)
4. **Persistensi data** — data tersimpan otomatis ke file saat keluar, di-load saat program start

---

## Menu Program (Setelah Pengembangan)

| Menu | Fungsi |
|------|--------|
| 1 | Tambah pesanan baru ke antrean |
| 2 | Proses pesanan berikutnya (dequeue) |
| 3 | Tampil pesanan terakhir diproses |
| 4 | Tampilkan antrean |
| 5 | Tampilkan riwayat selesai |
| 6 | **Edit pesanan dalam antrean** *(BARU)* |
| 7 | **Hapus pesanan dari antrean** *(BARU)* |
| 8 | **Tampilkan laporan** *(BARU)* |
| 0 | Keluar (data otomatis tersimpan) |

---

## Menu 6 — Edit Pesanan dalam Antrean

### Cara Penggunaan

1. Pilih menu **6**
2. Akan ditampilkan daftar antrean saat ini (sama seperti menu 4)
3. Masukkan nomor pesanan yang ingin diedit
4. Edit field yang diinginkan:
   - **Nama** — ketik nama baru (kosongkan = tidak diubah)
   - **Jenis Sepatu** — masukkan angka baru, `0` = tidak diubah
   - **Jenis Layanan** — masukkan angka baru, `0` = tidak diubah
5. Estimasi waktu dihitung ulang secara otomatis

### Catatan
- Jika jenis layanan diubah, durasi也跟着 berubah dan estimasi semua pesanan di antrean di-update
- Pesanan di luar jangkauan antrean akan menolak perubahan

---

## Menu 7 — Hapus Pesanan dari Antrean

### Cara Penggunaan

1. Pilih menu **7**
2. Akan ditampilkan daftar antrean saat ini
3. Masukkan nomor pesanan yang ingin dihapus
4. Pesanan dihapus dari antrean

### Catatan
- Menghapus pesanan di tengah antrean akan menggeser pesanan di belakangnya
- Estimasi semua pesanan tersisa dihitung ulang otomatis
- Antrean kosong tidak bisa dihapus

---

## Menu 8 — Laporan Sederhana

### Cara Penggunaan

1. Pilih menu **8**
2. Laporan ditampilkan langsung

### Contoh Output

```
======================================================
              LAPORAN PESANAN
======================================================
Layanan        | Dalam Antrean | Selesai | Total
----------------------------------------------------
Regular        |       2       |   1     |  3
Deep Cleaning |       1       |   0     |  1
Repair         |       0       |   2     |  2
Repaint        |       1       |   1     |  2
Whitening      |       0       |   0     |  0
----------------------------------------------------
Total          |       4       |   4     |  8
======================================================
```

---

## Persistensi Data

### Cara Kerja

- **Save:** Saat memilih menu **0** (Keluar), data antrean dan riwayat otomatis disimpan ke `data/save.json`
- **Load:** Saat program dibuka, data secara otomatis di-load dari file tersebut

### Lokasi File

```
data/save.json
```

Direktori `data/` dibuat otomatis jika belum ada.

### Format File (JSON)

```json
{
  "queue": [
    {
      "namaPelanggan": "Andi",
      "jenisSepatu": 0,
      "jenisLayanan": 1,
      "durasiLayananMenit": 60,
      "estimasiSelesai": 60
    }
  ],
  "stack": [
    {
      "namaPelanggan": "Budi",
      "jenisSepatu": 2,
      "jenisLayanan": 0,
      "durasiLayananMenit": 90,
      "estimasiSelesai": 0
    }
  ]
}
```

### Enum Mapping

| JenisSepatu | Nilai |
|-------------|-------|
| SNEAKERS | 0 |
| BOOTS | 1 |
| SANDALS | 2 |
| FORMAL | 3 |
| OLAHRAGA | 4 |

| JenisLayanan | Nilai |
|-------------|-------|
| REGULAR | 0 |
| DEEP_CLEANING | 1 |
| REPAIR | 2 |
| REPAINT | 3 |
| WHITENING | 4 |

### Catatan
- Jika file `data/save.json` tidak ditemukan saat program start, program akan mulai dengan antrean & riwayat kosong
- File tidak terenkripsi — hanya untuk development/pembelajaran

---

## Struktur Project (Setelah Pengembangan)

```text
ASD_project/
├── bin/
│   └── ASD_ShoeLaundryQueue.exe
├── build/
├── data/                              # (otomatis dibuat saat pertama kali save)
│   └── save.json
├── docs/
│   ├── flowchart.png
│   ├── pseudocode.md
│   └── analisis_big_o.md
├── src/
│   ├── data_structures/
│   │   ├── Node.h
│   │   ├── Queue.h / Queue.cpp       # + removeAt, updateAt, getAt, traverse
│   │   └── Stack.h / Stack.cpp       # + traverse, const-correctness
│   ├── models/
│   │   └── Pesanan.h
│   ├── ui/
│   │   └── ui.h / ui.cpp            # + formEditPesanan, tampilLaporan
│   ├── utils/
│   │   └── FileManager.h / FileManager.cpp   # (BARU) load/save JSON
│   └── vendor/
│       └── json.hpp                             # (BARU) library nlohmann/json
├── CHANGELOG.md                       # Dokumen ini
├── CMakeLists.txt
└── README.md
```

---

## Analisis Kompleksitas (Lengkap)

### Struktur Data

| Operasi | Kompleksitas | Keterangan |
|--------|-------------|-------------|
| enqueue | O(1) | Tambah di belakang |
| dequeue | O(1) | Hapus di depan |
| push riwayat | O(1) | Tambah di top |
| peek riwayat | O(1) | Lihat top |
| display antrean | O(n) | Traverse seluruh queue |
| display riwayat | O(n) | Traverse seluruh stack |
| calculateTime | O(n) | Traverse + hitung estimasi |
| **getAt** | O(n) | *(BARU)* Akses node by index |
| **updateAt** | O(n) | *(BARU)* Update node by index |
| **removeAt** | O(n) | *(BARU)* Hapus node by index |
| **traverse** | O(n) | *(BARU)* Helper untuk laporan & serialization |

### Persistensi Data

| Operasi | Kompleksitas | Keterangan |
|--------|-------------|-------------|
| Save (serialization) | O(n) | Traverse queue + stack, convert ke JSON |
| Load (deserialization) | O(n) | Parse JSON, push semua item ke queue/stack |

---

## Build Ulang

Karena ada file baru dan library baru, perlu build ulang:

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\bin\ASD_ShoeLaundryQueue.exe
```

> **Catatan:** Library nlohmann/json (single-header) sudah included di `src/vendor/json.hpp` — tidak perlu install manual.
