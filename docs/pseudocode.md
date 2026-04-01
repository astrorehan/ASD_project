# Pseudocode Sistem Antrean Tempat Cuci Sepatu

Dokumen ini disesuaikan dengan implementasi CLI terbaru di folder src, termasuk:
- Queue dan Stack berbasis linked list.
- Pemilihan enum dari input angka dengan opsi batal (0 = Cancel).
- Perhitungan durasi layanan, total waktu antrean, dan estimasi selesai.
- Konfirmasi sebelum pesanan benar-benar masuk antrean.

## 1. Definisi Tipe Data

```text
ENUM JenisSepatu:
    SNEAKERS
    BOOTS
    SANDALS
    FORMAL
    OLAHRAGA

ENUM JenisLayanan:
    REGULAR
    DEEP_CLEANING
    REPAIR
    REPAINT
    WHITENING

STRUCT Pesanan:
    STRING namaPelanggan
    JenisSepatu jenisSepatu
    JenisLayanan jenisLayanan
    INTEGER durasiLayananMenit
    INTEGER estimasiSelesai

STRUCT Node:
    Pesanan data
    Node POINTER next

STRUCT Queue:
    Node POINTER front = NULL
    Node POINTER rear = NULL

STRUCT Stack:
    Node POINTER top = NULL
```

## 2. Fungsi Bantu Enum dan Durasi

```text
FUNCTION FromChoiceSepatu(INTEGER pilihan, OUT JenisSepatu hasil) -> BOOLEAN:
    SWITCH pilihan
        CASE 1: hasil = SNEAKERS; RETURN TRUE
        CASE 2: hasil = BOOTS; RETURN TRUE
        CASE 3: hasil = SANDALS; RETURN TRUE
        CASE 4: hasil = FORMAL; RETURN TRUE
        CASE 5: hasil = OLAHRAGA; RETURN TRUE
        DEFAULT: RETURN FALSE
    END SWITCH

FUNCTION FromChoiceLayanan(INTEGER pilihan, OUT JenisLayanan hasil) -> BOOLEAN:
    SWITCH pilihan
        CASE 1: hasil = REGULAR; RETURN TRUE
        CASE 2: hasil = DEEP_CLEANING; RETURN TRUE
        CASE 3: hasil = REPAIR; RETURN TRUE
        CASE 4: hasil = REPAINT; RETURN TRUE
        CASE 5: hasil = WHITENING; RETURN TRUE
        DEFAULT: RETURN FALSE
    END SWITCH

FUNCTION DurasiStandarMenit(JenisLayanan nilai) -> INTEGER:
    SWITCH nilai
        CASE REGULAR: RETURN 60
        CASE DEEP_CLEANING: RETURN 90
        CASE REPAIR: RETURN 120
        CASE REPAINT: RETURN 150
        CASE WHITENING: RETURN 75
        DEFAULT: RETURN 0
    END SWITCH

FUNCTION ToStringSepatu(JenisSepatu nilai) -> STRING:
    RETURN label teks sepatu sesuai enum

FUNCTION ToStringLayanan(JenisLayanan nilai) -> STRING:
    RETURN label teks layanan sesuai enum
```

## 3. Operasi Queue

```text
FUNCTION QueueIsEmpty() -> BOOLEAN:
    RETURN (front == NULL)

PROCEDURE Enqueue(Pesanan pesananBaru):
    BUAT Node baru
    newNode.data = pesananBaru
    newNode.next = NULL

    IF QueueIsEmpty() THEN
        front = newNode
        rear = newNode
    ELSE
        rear.next = newNode
        rear = newNode
    END IF
END PROCEDURE

FUNCTION Dequeue() -> Pesanan:
    // Dipanggil saat antrean dipastikan tidak kosong
    temp = front
    pesananDiproses = temp.data
    front = front.next

    IF front == NULL THEN
        rear = NULL
    END IF

    HAPUS temp
    RETURN pesananDiproses
END FUNCTION

FUNCTION CalculateTime() -> INTEGER:
    current = front
    totalTime = 0

    WHILE current != NULL DO
        totalTime = totalTime + current.data.durasiLayananMenit
        current.data.estimasiSelesai = totalTime
        current = current.next
    END WHILE

    RETURN totalTime
END FUNCTION

PROCEDURE TampilAntrean():
    IF QueueIsEmpty() THEN
        PRINT "Antrean saat ini kosong."
        RETURN
    END IF

    current = front
    nomor = 1

    WHILE current != NULL DO
        PRINT nomor,
              current.data.namaPelanggan,
              ToStringSepatu(current.data.jenisSepatu),
              ToStringLayanan(current.data.jenisLayanan),
              current.data.estimasiSelesai
        current = current.next
        nomor = nomor + 1
    END WHILE
END PROCEDURE
```

## 4. Operasi Stack

```text
FUNCTION StackIsEmpty() -> BOOLEAN:
    RETURN (top == NULL)

PROCEDURE PushRiwayat(Pesanan pesananSelesai):
    BUAT Node baru
    newNode.data = pesananSelesai
    newNode.next = top
    top = newNode
END PROCEDURE

PROCEDURE TampilTerakhirDiproses():
    IF StackIsEmpty() THEN
        PRINT "Belum ada riwayat pesanan yang selesai."
        RETURN
    END IF

    PRINT top.data.namaPelanggan,
          ToStringSepatu(top.data.jenisSepatu),
          ToStringLayanan(top.data.jenisLayanan)
END PROCEDURE

PROCEDURE TampilRiwayat():
    IF StackIsEmpty() THEN
        PRINT "Riwayat pesanan masih kosong."
        RETURN
    END IF

    current = top
    nomor = 1

    WHILE current != NULL DO
        PRINT nomor,
              current.data.namaPelanggan,
              ToStringSepatu(current.data.jenisSepatu),
              ToStringLayanan(current.data.jenisLayanan)
        current = current.next
        nomor = nomor + 1
    END WHILE
END PROCEDURE
```

## 5. Fungsi UI (CLI)

```text
PROCEDURE TampilMenu():
    PRINT daftar menu 1..5 dan 0

PROCEDURE PauseSebelumMenu():
    PRINT "Tekan Enter untuk kembali ke menu..."
    TUNGGU satu baris input

PROCEDURE ClearConsole():
    KIRIM ANSI escape code untuk clear screen

FUNCTION KonfirmasiSebelumEnqueue(Pesanan pesananBaru) -> BOOLEAN:
    ULANGI
        ClearConsole()
        Tampilkan rincian pesanan:
            nama
            jenis sepatu
            jenis layanan
            estimasi selesai

        PRINT "Enter = konfirmasi, C = batal"
        INPUT teks

        IF teks kosong THEN
            RETURN TRUE
        ELSE IF teks == "C" atau "c" THEN
            RETURN FALSE
        ELSE
            PRINT "Input tidak valid"
            TUNGGU Enter
        END IF
    SAMPAI mendapat input valid
END FUNCTION
```

## 6. Program Utama

```text
START
    BUAT Queue antreanCucian
    BUAT Stack riwayatCucian

    ULANGI
        ClearConsole()
        TampilMenu()

        INPUT pilihan
        IF input menu bukan angka THEN
            reset status input
            buang buffer sampai newline
            PRINT "Input tidak valid. Masukkan angka menu."
            PauseSebelumMenu()
            LANJUT ke iterasi berikutnya
        END IF

        buang newline tersisa di buffer

        SWITCH pilihan
            CASE 0:
                ClearConsole()
                PRINT "Keluar dari program..."

            CASE 1:
                ClearConsole()
                batalTambah = FALSE

                INPUT namaPelanggan (boleh mengandung spasi)

                ULANGI
                    ClearConsole()
                    Tampilkan opsi jenis sepatu (0..5)
                    INPUT pilihSepatu

                    IF input bukan angka THEN
                        reset input dan buang buffer
                        PRINT "Input harus angka"
                        LANJUTI loop
                    END IF

                    buang newline buffer
                    validSepatu = FromChoiceSepatu(pilihSepatu, pesananBaru.jenisSepatu)

                    IF pilihSepatu == 0 THEN
                        batalTambah = TRUE
                        BREAK
                    END IF

                    IF validSepatu == FALSE THEN
                        PRINT "Pilihan sepatu tidak valid"
                    END IF
                SAMPAI validSepatu == TRUE

                IF batalTambah THEN
                    PRINT "Tambah pesanan berhasil dibatalkan"
                    BREAK CASE
                END IF

                ULANGI
                    ClearConsole()
                    Tampilkan opsi jenis layanan (0..5)
                    INPUT pilihLayanan

                    IF input bukan angka THEN
                        reset input dan buang buffer
                        PRINT "Input harus angka"
                        LANJUTI loop
                    END IF

                    buang newline buffer
                    validLayanan = FromChoiceLayanan(pilihLayanan, pesananBaru.jenisLayanan)

                    IF pilihLayanan == 0 THEN
                        batalTambah = TRUE
                        BREAK
                    END IF

                    IF validLayanan == FALSE THEN
                        PRINT "Pilihan layanan tidak valid"
                    END IF
                SAMPAI validLayanan == TRUE

                IF batalTambah THEN
                    PRINT "Tambah pesanan berhasil dibatalkan"
                    BREAK CASE
                END IF

                pesananBaru.durasiLayananMenit = DurasiStandarMenit(pesananBaru.jenisLayanan)
                totalTime = CalculateTime()
                pesananBaru.estimasiSelesai = totalTime + pesananBaru.durasiLayananMenit

                IF KonfirmasiSebelumEnqueue(pesananBaru) == FALSE THEN
                    PRINT "Tambah pesanan berhasil dibatalkan"
                    BREAK CASE
                END IF

                Enqueue(pesananBaru)
                PRINT "Pesanan berhasil masuk antrean"

            CASE 2:
                ClearConsole()
                IF QueueIsEmpty() THEN
                    PRINT "Antrean masih kosong"
                ELSE
                    pesananDiproses = Dequeue()
                    PRINT "Memproses pesanan", pesananDiproses.namaPelanggan
                    PRINT "Cuci sepatu selesai"
                    PushRiwayat(pesananDiproses)
                    PRINT "Pesanan dipindahkan ke riwayat"
                END IF

            CASE 3:
                ClearConsole()
                TampilTerakhirDiproses()

            CASE 4:
                ClearConsole()
                TampilAntrean()

            CASE 5:
                ClearConsole()
                TampilRiwayat()

            DEFAULT:
                PRINT "Pilihan tidak valid"
        END SWITCH

        IF pilihan != 0 THEN
            PauseSebelumMenu()
        END IF
    SAMPAI pilihan == 0
END
```