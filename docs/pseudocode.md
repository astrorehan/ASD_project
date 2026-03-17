# Pseudocode Sistem Antrean Tempat Cuci Sepatu

## 1. Definisi Struktur Data (Struct)

STRUCT Pesanan:
    STRING nama_pelanggan
    STRING jenis_sepatu
    STRING jenis_layanan
    INTEGER estimasi_waktu


STRUCT Node:
    Pesanan data
    Node pointer next


STRUCT Queue:
    Node pointer front = NULL
    Node pointer rear = NULL


STRUCT Stack:
    Node pointer top = NULL

## 2. Operasi Queue (Antrian)
### 2.1 Tambah Pesanan
PROCEDURE TambahAntrean(Pesanan pesanan_baru):
    Buat Node baru (newNode)
    newNode.data = pesanan_baru
    newNode.next = NULL

    IF Queue.rear == NULL THEN
        Queue.front = newNode
        Queue.rear = newNode
    ELSE
        Queue.rear.next = newNode
        Queue.rear = newNode
    END IF
    PRINT "Pesanan berhasil ditambahkan ke antrean."
END PROCEDURE

### 2.2 Tampilkan Antrian
PROCEDURE TampilAntrean():
    IF Queue.front == NULL THEN
        PRINT "Antrean saat ini kosong."
        RETURN
    END IF

    Node current = Queue.front
    INTEGER nomor = 1
    WHILE current != NULL DO
        PRINT nomor + ". " + current.data.nama_pelanggan + " - " + current.data.jenis_layanan
        current = current.next
        nomor = nomor + 1
    END WHILE
END PROCEDURE

## 3. Operasi Stack (Riwayat)
### 3.1 Tampilkan Pesanan Terakhir (Peek)
PROCEDURE TampilTerakhirDiproses():
    IF Stack.top == NULL THEN
        PRINT "Belum ada riwayat pesanan."
    ELSE
        PRINT "Pesanan terakhir diproses: " + Stack.top.data.nama_pelanggan
        PRINT "Jenis sepatu  : " + Stack.top.data.jenis_sepatu
        PRINT "Jenis layanan : " + Stack.top.data.jenis_layanan
        PRINT "Estimasi waktu: " + Stack.top.data.estimasi_waktu
    END IF
END PROCEDURE

### 3.2 Tampilkan Semua Riwayat
PROCEDURE TampilRiwayat():
    IF Stack.top == NULL THEN
        PRINT "Riwayat kosong."
        RETURN
    END IF

    Node current = Stack.top
    INTEGER nomor = 1
    WHILE current != NULL DO
        PRINT nomor + ". " + current.data.nama_pelanggan + " - " + current.data.jenis_layanan
        current = current.next
        nomor = nomor + 1
    END WHILE
END PROCEDURE

## 4. Operasi Transisi (Memproses Pesanan)
### 4.1 Proses Pesanan (Dequeue & Push)
PROCEDURE ProsesPesanan():
    IF Queue.front == NULL THEN
        PRINT "Antrean kosong. Tidak ada pesanan untuk diproses."
        RETURN
    END IF

    Node temp = Queue.front
    Pesanan pesanan_diproses = temp.data
    Queue.front = Queue.front.next

    IF Queue.front == NULL THEN
        Queue.rear = NULL
    END IF
    Hapus memori temp

    Buat Node baru (newNode)
    newNode.data = pesanan_diproses
    newNode.next = Stack.top
    Stack.top = newNode

    PRINT "Pesanan atas nama " + pesanan_diproses.nama_pelanggan + " telah selesai diproses."
END PROCEDURE

## 5. Operasi file I/O
PROCEDURE SimpanDataKeFile():
    Buka file "antrean.txt" dalam mode TULIS (Write)
    Node current = Queue.front
    WHILE current != NULL DO
        Tulis current.data ke "antrean.txt" (format: nama,sepatu,layanan,waktu)
        current = current.next
    END WHILE
    Tutup file "antrean.txt"

    Buka file "riwayat.txt" dalam mode TULIS (Write)
    Node currentRiwayat = Stack.top
    WHILE currentRiwayat != NULL DO
        Tulis currentRiwayat.data ke "riwayat.txt" (format: nama,sepatu,layanan,waktu)
        currentRiwayat = currentRiwayat.next
    END WHILE
    Tutup file "riwayat.txt"
END PROCEDURE

PROCEDURE MuatDataDariFile():
    Buka file "antrean.txt" dalam mode BACA (Read)
    WHILE tidak di akhir file DO
        Baca 1 baris data
        Pisahkan data menjadi nama, sepatu, layanan, waktu
        Buat Pesanan baru dari data tersebut
        TambahAntrean(Pesanan baru) 
    END WHILE
    Tutup file "antrean.txt"
END PROCEDURE

## 6. Program Utama

START:
    MuatDataDariFile()

    REPEAT
        PRINT "===== Sistem Antrean Cuci Sepatu ====="
        PRINT "1. Tambah Pesanan"
        PRINT "2. Proses Pesanan Berikutnya"
        PRINT "3. Tampilkan Pesanan Terakhir Diproses"
        PRINT "4. Tampilkan Antrean"
        PRINT "5. Tampilkan Riwayat"
        PRINT "0. Keluar"
        INPUT pilihan

        IF pilihan == 1 THEN
            INPUT nama_pelanggan, jenis_sepatu, jenis_layanan, estimasi_waktu
            Buat Pesanan baru dari data tersebut
            TambahAntrean(pesanan_baru)
        ELSE IF pilihan == 2 THEN
            ProsesPesanan()
        ELSE IF pilihan == 3 THEN
            TampilTerakhirDiproses()
        ELSE IF pilihan == 4 THEN
            TampilAntrean()
        ELSE IF pilihan == 5 THEN
            TampilRiwayat()
        ELSE IF pilihan == 0 THEN
            SimpanDataKeFile()
        END IF
    UNTIL pilihan == 0
END