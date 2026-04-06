# Shoe Laundry Web

Implementasi web dari sistem antrean cuci sepatu. Backend C++ (Crow framework) + Frontend Next.js (React + Tailwind).

## Struktur

```
web/
├── backend/              # C++ REST API (Crow)
│   ├── main.cpp
│   ├── CMakeLists.txt
│   ├── Dockerfile        # Build Docker image
│   ├── models/
│   ├── data_structures/
│   └── include/          # Crow framework
├── frontend/             # Next.js (React + Tailwind)
│   ├── app/
│   │   ├── page.tsx      # Antrean
│   │   ├── history/       # Riwayat
│   │   ├── report/        # Laporan
│   │   └── lib/           # API client, types
│   ├── vercel.json       # Vercel config
│   └── .env.local        # API URL
└── README.md
```

## Cara Deploy

### 1. Backend → Render.com (Free Tier)

1. Buat akun di [render.com](https://render.com)
2. Klik **New → Web Service**
3. Hubungkan repo GitHub kamu
4. Seting:
   - **Root Directory:** `backend`
   - **Build Command:** `docker build -t backend .`
   - **Start Command:** `docker run -p 10000:10000 backend`
   - **Plan:** Free
5. Klik **Create Web Service**
6. Tunggu build selesai
7. URL backend akan muncul, contoh: `https://shoe-laundry.onrender.com`

### 2. Frontend → Vercel (Gratis)

1. Buat akun di [vercel.com](https://vercel.com)
2. Import repo GitHub
3. Seting:
   - **Root Directory:** `frontend`
   - **Environment Variables:**
     - `NEXT_PUBLIC_API_URL` = URL backend kamu (contoh: `https://shoe-laundry.onrender.com`)
4. Klik **Deploy**

### 3. Update Frontend Config

Setelah backend di-deploy, update `frontend/vercel.json`:

```json
{
  "rewrites": [
    {
      "source": "/api/proxy/:path*",
      "destination": "https://YOUR-RENDER-APP.onrender.com/:path*"
    }
  ]
}
```

Atau update `.env.local`:

```env
NEXT_PUBLIC_API_URL=https://YOUR-RENDER-APP.onrender.com
```

## API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/` | Health check |
| GET | `/queue` | List semua pesanan |
| POST | `/queue` | Tambah pesanan baru |
| PUT | `/queue/:index` | Edit pesanan |
| DELETE | `/queue/:index` | Hapus pesanan |
| DELETE | `/queue/process` | Proses pesanan berikutnya |
| GET | `/history` | List riwayat |
| GET | `/history/latest` | Pesanan terakhir diproses |
| GET | `/report` | Laporan per jenis layanan |

## Local Development

### Backend (local)

```bash
cd backend
mkdir build && cd build
cmake .. -G "MinGW Makefiles"
make
./backend.exe
```

### Frontend (local)

```bash
cd frontend
npm install
npm run dev
```

### Docker (local)

```bash
cd backend
docker build -t shoe-laundry-backend .
docker run -p 8080:10000 shoe-laundry-backend
```
