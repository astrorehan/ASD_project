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
    bool isEmpty();

    // Menambahkan pesanan ke riwayat (LIFO)
    void push(Pesanan pesananBaru);

    // Melihat pesanan yang terakhir kali diselesaikan
    void peek();

    // Menampilkan seluruh daftar riwayat pesanan
    void display();
};

#endif