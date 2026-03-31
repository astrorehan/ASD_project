# Pseudocode Sistem Antrean Tempat Cuci Sepatu

Dokumen ini sudah disesuaikan dengan implementasi CLI saat ini:
- Queue dan Stack menggunakan linked list.
- Jenis sepatu dan jenis layanan menggunakan enum.
- Input jenis sepatu/layanan mendukung opsi batal (0 = Cancel).

## 1. Definisi Tipe Data

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

STRUCT Node:
    Pesanan data
    Node pointer next

STRUCT Queue:
    Node pointer front = NULL
    Node pointer rear = NULL

STRUCT Stack:
    Node pointer top = NULL

## 2. Fungsi Bantu Enum

FUNCTION FromChoiceSepatu(INTEGER pilihan, OUT JenisSepatu hasil) -> BOOLEAN:
    SWITCH pilihan
        CASE 1: hasil = SNEAKERS, RETURN TRUE
        CASE 2: hasil = BOOTS, RETURN TRUE
        CASE 3: hasil = SANDALS, RETURN TRUE
        CASE 4: hasil = FORMAL, RETURN TRUE
        CASE 5: hasil = OLAHRAGA, RETURN TRUE
        DEFAULT: RETURN FALSE
    END SWITCH

FUNCTION FromChoiceLayanan(INTEGER pilihan, OUT JenisLayanan hasil) -> BOOLEAN:
    SWITCH pilihan
        CASE 1: hasil = REGULAR, RETURN TRUE
        CASE 2: hasil = DEEP_CLEANING, RETURN TRUE
        CASE 3: hasil = REPAIR, RETURN TRUE
        CASE 4: hasil = REPAINT, RETURN TRUE
        CASE 5: hasil = WHITENING, RETURN TRUE
        DEFAULT: RETURN FALSE
    END SWITCH

FUNCTION ToStringSepatu(JenisSepatu nilai) -> STRING:
    RETURN label teks sepatu sesuai enum

FUNCTION ToStringLayanan(JenisLayanan nilai) -> STRING:
    RETURN label teks layanan sesuai enum

## 3. Operasi Queue

PROCEDURE Enqueue(Pesanan pesananBaru):
    Buat Node baru
    nodeBaru.data = pesananBaru
    nodeBaru.next = NULL

    IF rear == NULL THEN
        front = nodeBaru
        rear = nodeBaru
    ELSE
        rear.next = nodeBaru
        rear = nodeBaru
    END IF
END PROCEDURE

FUNCTION Dequeue() -> Pesanan:
    // Dipanggil hanya jika queue tidak kosong
    temp = front
    hasil = temp.data
    front = front.next

    IF front == NULL THEN
        rear = NULL
    END IF

    Hapus temp
    RETURN hasil
END FUNCTION

PROCEDURE TampilAntrean():
    IF front == NULL THEN
        PRINT "Antrean saat ini kosong."
        RETURN
    END IF

    current = front
    nomor = 1
    WHILE current != NULL DO
        PRINT nomor, current.data.namaPelanggan,
              ToStringSepatu(current.data.jenisSepatu),
              ToStringLayanan(current.data.jenisLayanan)
        current = current.next
        nomor = nomor + 1
    END WHILE
END PROCEDURE

## 4. Operasi Stack

PROCEDURE PushRiwayat(Pesanan pesananSelesai):
    Buat Node baru
    nodeBaru.data = pesananSelesai
    nodeBaru.next = top
    top = nodeBaru
END PROCEDURE

PROCEDURE TampilTerakhirDiproses():
    IF top == NULL THEN
        PRINT "Belum ada riwayat pesanan yang selesai."
        RETURN
    END IF

    PRINT top.data.namaPelanggan,
          ToStringSepatu(top.data.jenisSepatu),
          ToStringLayanan(top.data.jenisLayanan)
END PROCEDURE

PROCEDURE TampilRiwayat():
    IF top == NULL THEN
        PRINT "Riwayat pesanan masih kosong."
        RETURN
    END IF

    current = top
    nomor = 1
    WHILE current != NULL DO
        PRINT nomor, current.data.namaPelanggan,
              ToStringSepatu(current.data.jenisSepatu),
              ToStringLayanan(current.data.jenisLayanan)
        current = current.next
        nomor = nomor + 1
    END WHILE
END PROCEDURE

## 5. Operasi Proses Pesanan

PROCEDURE ProsesPesananBerikutnya():
    IF front == NULL THEN
        PRINT "Antrean masih kosong."
        RETURN
    END IF

    pesananDiproses = Dequeue()
    PRINT "Memproses pesanan", pesananDiproses.namaPelanggan
    PRINT "Cuci sepatu selesai"

    PushRiwayat(pesananDiproses)
    PRINT "Pesanan dipindahkan ke riwayat"
END PROCEDURE

## 6. Program Utama (CLI)

START:
    BUAT objek Queue antreanCucian
    BUAT objek Stack riwayatCucian

    ULANGI
        Tampilkan menu:
            1. Tambah pesanan
            2. Proses pesanan berikutnya
            3. Tampil pesanan terakhir diproses
            4. Tampil antrean
            5. Tampil riwayat
            0. Keluar

        INPUT pilihan menu
        VALIDASI bahwa input menu adalah angka

        SWITCH pilihan
            CASE 1:
                INPUT namaPelanggan

                // Pilih jenis sepatu dengan opsi cancel
                ULANGI
                    Tampilkan opsi sepatu (0-5)
                    INPUT pilihSepatu
                    IF pilihSepatu == 0 THEN
                        tandai batalTambah
                        BREAK
                    END IF
                SAMPAI FromChoiceSepatu valid

                IF batalTambah THEN
                    PRINT "Tambah pesanan dibatalkan"
                    BREAK CASE
                END IF

                // Pilih jenis layanan dengan opsi cancel
                ULANGI
                    Tampilkan opsi layanan (0-5)
                    INPUT pilihLayanan
                    IF pilihLayanan == 0 THEN
                        tandai batalTambah
                        BREAK
                    END IF
                SAMPAI FromChoiceLayanan valid

                IF batalTambah THEN
                    PRINT "Tambah pesanan dibatalkan"
                    BREAK CASE
                END IF

                Enqueue(pesananBaru)
                PRINT "Pesanan berhasil masuk antrean"

            CASE 2:
                ProsesPesananBerikutnya()

            CASE 3:
                TampilTerakhirDiproses()

            CASE 4:
                TampilAntrean()

            CASE 5:
                TampilRiwayat()

            CASE 0:
                PRINT "Keluar program"

            DEFAULT:
                PRINT "Pilihan tidak valid"
        END SWITCH

    SAMPAI pilihan == 0
END