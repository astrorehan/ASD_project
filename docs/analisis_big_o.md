# Analisis Big O - Sistem Antrean Cuci Sepatu

Tahap 3: analisis kompleksitas operasi utama.

## Struktur Data
- Queue berbasis linked list
- Stack berbasis linked list

## Operasi Utama
- Tambah pesanan (`enqueue`): **O(1)**
- Proses pesanan berikutnya (`dequeue` + `push`): **O(1)**
- Simpan ke riwayat (`push`): **O(1)**
- Lihat pesanan terakhir diproses (`peek` stack): **O(1)**
- Tampilkan antrean pesanan: **O(n)**
- Tampilkan riwayat pesanan selesai: **O(n)**

## Kompleksitas Ruang
- Queue: **O(n)** untuk n pesanan pending
- Stack: **O(m)** untuk m pesanan yang telah selesai
