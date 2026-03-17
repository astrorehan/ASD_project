#ifndef QUEUE_H
#define QUEUE_H

#include "./Node.h"
#include <iostream>

using namespace std;

class Queue {
private:
    Node* front;
    Node* rear;

public:
    // Constructor untuk inisialisasi awal
    Queue();

    // Mengecek apakah antrean kosong
    bool isEmpty();

    // Menambahkan pesanan baru ke belakang antrean
    void enqueue(Pesanan pesananBaru);

    // Mengambil dan menghapus pesanan dari depan antrean
    // Mengembalikan data Pesanan agar nanti bisa dimasukkan ke Stack (Riwayat)
    Pesanan dequeue();

    // Menampilkan seluruh daftar antrean
    void display();
};

#endif