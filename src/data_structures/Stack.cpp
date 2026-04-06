#include <iostream>
#include "Stack.h"
#include "../models/Pesanan.h"
using namespace std;

// Inisialisasi awal, riwayat kosong
Stack::Stack() {
    top = nullptr;
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::push(Pesanan pesananBaru) {
    // Buat Node baru di memori
    Node* newNode = new Node();
    newNode->data = pesananBaru;
    
    // Karena Stack (LIFO), Node baru selalu menjadi top
    // Node baru menunjuk ke node yang sebelumnya ada di top
    newNode->next = top;
    top = newNode;
}

void Stack::peek() const {
    if (isEmpty()) {
        cout << "Belum ada riwayat pesanan yang selesai.\n";
        return;
    }
    
    cout << "\n--- Pesanan Terakhir yang Diselesaikan ---\n";
    cout << "Nama    : " << top->data.namaPelanggan << endl;
    cout << "Sepatu  : " << toString(top->data.jenisSepatu) << endl;
    cout << "Layanan : " << toString(top->data.jenisLayanan) << endl;
    cout << "------------------------------------------\n";
}

void Stack::display() const {
    if (isEmpty()) {
        cout << "Riwayat pesanan masih kosong.\n";
        return;
    }

    Node* current = top;
    int nomor = 1;

    cout << "\n--- Daftar Riwayat Pesanan Selesai ---\n";
    while (current != nullptr) {
        cout << nomor << ". " << current->data.namaPelanggan 
             << " | Sepatu: " << toString(current->data.jenisSepatu) 
             << " | Layanan: " << toString(current->data.jenisLayanan) << endl;
        
        current = current->next;
        nomor++;
    }
    cout << "--------------------------------------\n";
}