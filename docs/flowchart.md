flowchart TD
    Start([Mulai]) --> Init[Inisialisasi Queue & Stack]
    Init --> Menu[/Tampil Menu Utama/]
    Menu --> InputPilihan[/Input Angka Pilihan/]
    
    InputPilihan --> Validasi{Input Valid?}
    Validasi -- Tidak --> PesanError[/Tampil Error/] --> Menu
    Validasi -- Ya --> SwitchCase{Cek Pilihan}

    %% Pilihan 0
    SwitchCase -- "Pilih 0" --> Keluar[/Tampil Keluar/] --> End([Selesai])

    %% Pilihan 1
    SwitchCase -- "Pilih 1" --> FormInput[/Input Nama/]
    FormInput --> PilihSepatu[/Input Jenis Sepatu/]
    PilihSepatu --> CekSepatu{Pilih 0?}
    CekSepatu -- Ya --> Batal[/Batal Tambah/] --> Menu
    CekSepatu -- Tidak --> PilihLayanan[/Input Jenis Layanan/]
    
    PilihLayanan --> CekLayanan{Pilih 0?}
    CekLayanan -- Ya --> Batal
    CekLayanan -- Tidak --> HitungProcess[Hitung Estimasi Waktu]
    
    HitungProcess --> Konfirmasi{Konfirmasi?}
    Konfirmasi -- C --> Batal
    Konfirmasi -- Enter --> ProsesEnqueue[Enqueue ke Queue]
    ProsesEnqueue --> PesanSukses1[/Tampil Berhasil/] --> Menu

    %% Pilihan 2
    SwitchCase -- "Pilih 2" --> CekAntreanKosong{Queue Kosong?}
    CekAntreanKosong -- Ya --> PesanKosong1[/Tampil Antrean Kosong/] --> Menu
    CekAntreanKosong -- Tidak --> ProsesDequeue[Dequeue dari Queue]
    ProsesDequeue --> ProsesPush[Push ke Stack Riwayat]
    ProsesPush --> PesanSukses2[/Tampil Proses Selesai/] --> Menu

    %% Pilihan 3
    SwitchCase -- "Pilih 3" --> CekStack1{Stack Kosong?}
    CekStack1 -- Ya --> PesanKosong2[/Tampil Riwayat Kosong/] --> Menu
    CekStack1 -- Tidak --> ProsesPeek[Peek Stack Teratas] --> Menu

    %% Pilihan 4 & 5
    SwitchCase -- "Pilih 4" --> LoopQueue[Traverse & Cetak Semua Node Queue] --> Menu
    SwitchCase -- "Pilih 5" --> LoopStack[Traverse & Cetak Semua Node Stack] --> Menu
    
    %% Default
    SwitchCase -- "Lainnya" --> PesanDefault[/Tampil Pilihan Tidak Valid/] --> Menu