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

    // Menjumlahkan waktu antrean dan mengassign estimasi sekaligus
    int calculateTime();

    // Dapat pointer ke node di index tertentu (0-based), nullptr jika tidak ada
    Node* getAt(int index);

    // Update data pesanan di index tertentu
    bool updateAt(int index, Pesanan newData);

    // Hapus node di index tertentu (0-based)
    bool removeAt(int index);

    // Traverse semua node (untuk laporan)
    template<typename Func>
    void traverse(Func&& func) const {
        for (Node* cur = front; cur != nullptr; cur = cur->next) {
            func(cur->data);
        }
    }
};

#endif