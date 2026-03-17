# Pseudocode Sistem Antrean Tempat Cuci Sepatu

## 1. Definisi Struktur Data (Struct)
// Definisi Data Pesanan
STRUCT Pesanan:
    STRING nama_pelanggan
    STRING jenis_sepatu
    STRING jenis_layanan
    INTEGER estimasi_waktu // dalam menit/jam

// Definisi Node untuk Linked List
STRUCT Node:
    Pesanan data
    Node pointer next

// Definisi Queue (Antrean)
STRUCT Queue:
    Node pointer front = NULL
    Node pointer rear = NULL

// Definisi Stack (Riwayat)
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

## Operasi Stack (Riwayat)
### 3.1 Tampilkan Pesanan Terakhir (Peek)
PROCEDURE TampilTerakhirDiproses():
    IF Stack.top == NULL THEN
        PRINT "Belum ada riwayat pesanan."
    ELSE
        PRINT "Pesanan terakhir diproses: " + Stack.top.data.nama_pelanggan
        // Print detail lainnya (jenis sepatu, layanan, dll)
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

    // Ambil data dari antrean terdepan (Dequeue)
    Node temp = Queue.front
    Pesanan pesanan_diproses = temp.data
    Queue.front = Queue.front.next

    IF Queue.front == NULL THEN
        Queue.rear = NULL
    END IF
    Hapus memori temp

    // Simpan data ke riwayat menggunakan Stack (Push)
    Buat Node baru (newNode)
    newNode.data = pesanan_diproses
    newNode.next = Stack.top
    Stack.top = newNode

    PRINT "Pesanan atas nama " + pesanan_diproses.nama_pelanggan + " telah selesai diproses."
END PROCEDURE

## 5. Program Utama