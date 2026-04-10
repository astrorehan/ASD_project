# Sistem Antrean Cuci Sepatu

Manajemen antrean tempat cuci sepatu menggunakan struktur data **Queue** dan **Stack** berbasis **Linked List** dengan implementasi **C++ CLI** dan **Web (Next.js + REST API)**.

## Fitur Utama

### Program CLI
1. **Tambah pesanan** — masukkan pelanggan baru ke antrean
2. **Proses pesanan** — dequeue pesanan depan, push ke riwayat
3. **Edit pesanan** — ubah data pesanan dalam antrean
4. **Hapus pesanan** — hapus pesanan dari antrean
5. **Lihat antrean** — tampilkan semua pesanan aktif
6. **Lihat riwayat** — tampilkan semua pesanan selesai
7. **Laporan** — ringkasan jumlah pesanan per jenis layanan
8. **Persistensi** — data tersimpan otomatis ke file JSON

### Program Web
- Frontend Next.js dengan antarmuka modern
- Backend REST API C++ (Crow framework)
- Deployable ke Railway + Vercel

---

## Menu Program

| Menu | Fungsi |
|------|--------|
| 1 | Tambah pesanan baru |
| 2 | Proses pesanan berikutnya (dequeue) |
| 3 | Tampilkan pesanan terakhir diproses |
| 4 | Lihat antrean |
| 5 | Lihat riwayat selesai |
| 6 | Edit pesanan dalam antrean |
| 7 | Hapus pesanan dari antrean |
| 8 | Tampilkan laporan |
| 0 | Keluar (data otomatis tersimpan) |

---

## Struktur Data

### Queue (Antrean) — FIFO
Menyimpan pesanan yang belum diproses menggunakan linked list dengan pointer `front` dan `rear`.

| Operasi | Kompleksitas | Keterangan |
|---------|-------------|-------------|
| `enqueue` | O(1) | Tambah di belakang |
| `dequeue` | O(1) | Hapus di depan |
| `getAt` | O(n) | Akses node by index |
| `updateAt` | O(n) | Update node by index |
| `removeAt` | O(n) | Hapus node by index |
| `calculateTime` | O(n) | Hitung estimasi semua pesanan |
| `traverse` | O(n) | Kunjungi semua node |

### Stack (Riwayat) — LIFO
Menyimpan pesanan yang telah selesai menggunakan linked list dengan pointer `top`.

| Operasi | Kompleksitas | Keterangan |
|---------|-------------|-------------|
| `push` | O(1) | Tambah di top |
| `pop` | O(1) | Hapus dari top |
| `peek` | O(1) | Lihat top |
| `traverse` | O(n) | Kunjungi semua node |

### Jenis Layanan

| Layanan | Durasi |
|---------|--------|
| Regular | 60 menit |
| Deep Cleaning | 90 menit |
| Repair | 120 menit |
| Repaint | 150 menit |
| Whitening | 75 menit |

---

## Struktur Project

```
ASD_project/
├── .github/
│   └── workflows/
│       └── backend.yml          # CI/CD Docker build
├── docs/
│   ├── flowchart.png
│   ├── pseudocode.md
│   └── analisis_big_o.md
├── src/
│   ├── data_structures/
│   │   ├── Node.h
│   │   ├── Queue.h / Queue.cpp
│   │   └── Stack.h / Stack.cpp
│   ├── models/
│   │   └── Pesanan.h
│   ├── ui/
│   │   ├── ui.h / ui.cpp
│   ├── utils/
│   │   ├── FileManager.h / FileManager.cpp
│   ├── vendor/
│   │   └── json.hpp              # nlohmann/json
│   └── main.cpp
├── web/
│   ├── backend/
│   │   ├── main.cpp              # REST API (Crow)
│   │   ├── Dockerfile
│   │   ├── models/
│   │   ├── data_structures/
│   │   └── include/
│   └── frontend/                 # Next.js
│       ├── app/
│       │   ├── page.tsx          # Antrean
│       │   ├── history/
│       │   ├── report/
│       │   └── components/
│       └── lib/
│           ├── api.ts
│           └── types.ts
├── railway.json                   # Railway deployment
├── CMakeLists.txt
└── README.md
```

---

## Build dan Jalankan (CLI)

### Prerequisites
- CMake 3.15+
- MinGW Makefiles atau compiler C++17

### Build

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

### Jalankan

```powershell
.\bin\ASD_ShoeLaundryQueue.exe
```

### Output Contoh

```
==============================================
   SISTEM ANTrean Cuci Sepatu
==============================================
1. Tambah Pesanan Baru
2. Proses Pesanan Berikutnya
3. Tampilkan Pesanan Terakhir Diproses
4. Lihat Antrean
5. Lihat Riwayat
6. Edit Pesanan
7. Hapus Pesanan
8. Lihat Laporan
0. Keluar
==============================================
Masukkan pilihan: _
```

---

## Deploy Web

### Backend — Railway

1. Buka [railway.app](https://railway.app)
2. Hubungkan repo GitHub
3. Railway auto-read `railway.json`
4. Docker build dari `web/backend/Dockerfile`
5. Backend URL: `https://asdproject-production.up.railway.app`

### Frontend — Vercel

1. Buka [vercel.com](https://vercel.com)
2. Import repo `astrorehan/ASD_project`
3. Set root directory: `web/frontend`
4. Tambahkan environment variable:
   - `NEXT_PUBLIC_API_URL` = URL Railway backend
5. Deploy
6. Frontend URL: `https://shoe-laundry.vercel.app/`

### API Endpoints

| Method | Endpoint | Deskripsi |
|--------|----------|-----------|
| GET | `/` | Health check |
| GET | `/queue` | List antrean |
| POST | `/queue` | Tambah pesanan |
| PUT | `/queue/:index` | Edit pesanan |
| DELETE | `/queue/:index` | Hapus pesanan |
| DELETE | `/queue/process` | Proses berikutnya |
| GET | `/history` | List riwayat |
| GET | `/history/latest` | Pesanan terakhir |
| GET | `/report` | Laporan ringkasan |

---

## Persistensi Data (CLI)

Data disimpan ke `data/save.json` secara otomatis saat keluar.

```json
{
  "queue": [
    {
      "namaPelanggan": "Andi",
      "jenisSepatu": 0,
      "jenisLayanan": 1,
      "durasiLayananMenit": 90,
      "estimasiSelesai": 90
    }
  ],
  "stack": [
    {
      "namaPelanggan": "Budi",
      "jenisSepatu": 2,
      "jenisLayanan": 0,
      "durasiLayananMenit": 60,
      "estimasiSelesai": 0
    }
  ]
}
```

### Enum Mapping

**jenisSepatu:**
| Index | Nilai |
|-------|-------|
| 0 | SNEAKERS |
| 1 | BOOTS |
| 2 | SANDALS |
| 3 | FORMAL |
| 4 | OLAHRAGA |

**jenisLayanan:**
| Index | Nilai |
|-------|-------|
| 0 | REGULAR |
| 1 | DEEP_CLEANING |
| 2 | REPAIR |
| 3 | REPAINT |
| 4 | WHITENING |

---

## Dokumentasi Pendukung

| Dokumen | Lokasi |
|---------|--------|
| Pseudocode | `docs/pseudocode.md` |
| Analisis Big O | `docs/analisis_big_o.md` |

---

## Changelog

### v2.0 — Penambahan Fitur Web
- REST API backend dengan Crow framework
- Frontend Next.js + Tailwind CSS
- Deployment Railway + Vercel
- Docker containerization

### v1.0 — Implementasi Awal
- CLI dengan menu interaktif
- Queue dan Stack dengan linked list
- Persistensi data ke JSON
- Fitur edit, hapus, dan laporan

---
