# Sistem Antrean Cuci Sepatu (C++)

Implementasi tugas ASD menggunakan OOP sederhana dengan:
- Queue (linked list) untuk antrean pesanan
- Stack (linked list) untuk riwayat pesanan selesai

## Struktur Project

```text
sistem-antrean-cuci-sepatu/
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
└── README.md
```

## Build dan Jalankan (PowerShell)

```powershell
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
.\bin\ASD_ShoeLaundryQueue.exe
```
