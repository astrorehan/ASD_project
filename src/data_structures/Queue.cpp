#include "Queue.h"
#include "../models/Pesanan.h"

// Inisialisasi awal, antrean kosong
Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

bool Queue::isEmpty() {
    return front == nullptr;
}

void Queue::enqueue(Pesanan pesananBaru) {
    // Buat Node baru di memori
    Node* newNode = new Node();
    newNode->data = pesananBaru;
    newNode->next = nullptr;

    // Jika antrean masih kosong, front dan rear menunjuk ke Node yang sama
    if (isEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        // Jika sudah ada isinya, tambahkan di belakang (rear)
        rear->next = newNode;
        rear = newNode;
    }
}

Pesanan Queue::dequeue() {
    // Asumsi: Fungsi ini dipanggil hanya jika isEmpty() == false
    // Simpan pointer front yang lama di variabel sementara
    Node* temp = front;
    
    // Ambil datanya untuk dikembalikan
    Pesanan pesananDiproses = temp->data;

    // Geser front ke Node berikutnya
    front = front->next;

    // Jika setelah digeser front menjadi null, berarti antrean habis. 
    // Set rear jadi null juga.
    if (front == nullptr) {
        rear = nullptr;
    }

    // Hapus Node lama dari memori agar tidak terjadi memory leak
    delete temp;

    calculateTime();
    return pesananDiproses;
}

void Queue::display() {
    if (isEmpty()) {
        cout << "Antrean saat ini kosong.\n";
        return;
    }

    Node* current = front;
    int nomor = 1;
    
    cout << "\n--- Daftar Antrean Saat Ini ---\n";
    while (current != nullptr) {
        cout << nomor << ". " << current->data.namaPelanggan 
             << " | Sepatu: " << toString(current->data.jenisSepatu)
             << " | Layanan: " << toString(current->data.jenisLayanan)
             << " | Estimasi Waktu: " << current->data.estimasiSelesai << endl;
        
        current = current->next;
        nomor++;
    }
    cout << "-------------------------------\n";
}

int Queue::calculateTime() {
    Node* current = front;
    int totalTime = 0;

    while (current != nullptr) {
        totalTime = totalTime + current->data.durasiLayananMenit;
        current->data.estimasiSelesai = totalTime;

        current = current->next;
    }

    return totalTime;
}