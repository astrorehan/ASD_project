# Shoe Laundry — Web Application

Implementasi web dari sistem antrean cuci sepatu. Backend REST API C++ (Crow) + Frontend Next.js + Tailwind CSS.

## Struktur

```
web/
├── backend/                      # C++ REST API
│   ├── main.cpp                 # Crow HTTP server
│   ├── Dockerfile                # Docker build
│   ├── railway.json              # Railway config
│   ├── models/                  # Pesanan struct
│   ├── data_structures/         # Queue & Stack
│   └── include/                 # Crow + nlohmann/json
│
├── frontend/                     # Next.js + Tailwind
│   ├── app/
│   │   ├── page.tsx             # Halaman Antrean
│   │   ├── history/             # Halaman Riwayat
│   │   ├── report/             # Halaman Laporan
│   │   └── components/         # UI components
│   └── lib/
│       ├── api.ts               # API client
│       └── types.ts            # TypeScript types
│
└── README.md                    # Dokumen ini
```

## API Endpoints

| Method | Endpoint | Deskripsi |
|--------|----------|-----------|
| GET | `/` | Health check |
| GET | `/queue` | List semua pesanan |
| POST | `/queue` | Tambah pesanan baru |
| PUT | `/queue/:index` | Edit pesanan |
| DELETE | `/queue/:index` | Hapus pesanan |
| DELETE | `/queue/process` | Proses pesanan berikutnya |
| GET | `/history` | List riwayat |
| GET | `/history/latest` | Pesanan terakhir diproses |
| GET | `/report` | Laporan ringkasan |

## Deploy

### Backend — Railway

1. Buka [railway.app](https://railway.app)
2. Hubungkan repo GitHub
3. Railway auto-read `railway.json`
4. Deploy

### Frontend — Vercel

1. Buka [vercel.com](https://vercel.com)
2. Import repo
3. Set root: `web/frontend`
4. Environment: `NEXT_PUBLIC_API_URL` = URL Railway
5. Deploy

## Local Development

### Backend (Docker)

```bash
cd backend
docker build -t shoe-laundry-backend .
docker run -p 8080:10000 shoe-laundry-backend
```

### Frontend

```bash
cd frontend
npm install
npm run dev
```

## Tech Stack

| Layer | Teknologi |
|-------|-----------|
| Backend | C++17, Crow Framework |
| Frontend | Next.js 16, React, TypeScript, Tailwind CSS |
| HTTP Server | Crow (header-only C++) |
| Container | Docker, Railway |
| Hosting | Railway (backend), Vercel (frontend) |
