#ifndef STACK_H
#define STACK_H

#include "./Node.h"
#include <iostream>

using namespace std;

class Stack {
private:
    Node* top;

public:
    // Constructor untuk inisialisasi awal riwayat
    Stack();

    // Mengecek apakah riwayat kosong
    bool isEmpty() const;

    // Menambahkan pesanan ke riwayat (LIFO)
    void push(Pesanan pesananBaru);

    // Melihat pesanan yang terakhir kali diselesaikan
    void peek() const;

    // Menampilkan seluruh daftar riwayat pesanan
    void display() const;

    // Traverse semua node (untuk laporan)
    template<typename Func>
    void traverse(Func&& func) const {
        for (Node* cur = top; cur != nullptr; cur = cur->next) {
            func(cur->data);
        }
    }
};

#endif