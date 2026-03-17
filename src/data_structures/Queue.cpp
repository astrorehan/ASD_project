#include "Queue.h"

Queue::Queue() : front_(nullptr), rear_(nullptr), size_(0) {}

Queue::~Queue() {
    clear();
}

void Queue::enqueue(const Pesanan& pesanan) {
    auto* nodeBaru = new Node<Pesanan>(pesanan);

    if (rear_ == nullptr) {
        front_ = nodeBaru;
        rear_ = nodeBaru;
    } else {
        rear_->next = nodeBaru;
        rear_ = nodeBaru;
    }

    ++size_;
}

bool Queue::dequeue(Pesanan& outPesanan) {
    if (front_ == nullptr) {
        return false;
    }

    Node<Pesanan>* frontLama = front_;
    outPesanan = frontLama->data;
    front_ = frontLama->next;

    if (front_ == nullptr) {
        rear_ = nullptr;
    }

    delete frontLama;
    --size_;
    return true;
}

bool Queue::peek(Pesanan& outPesanan) const {
    if (front_ == nullptr) {
        return false;
    }

    outPesanan = front_->data;
    return true;
}

bool Queue::empty() const {
    return size_ == 0;
}

std::size_t Queue::size() const {
    return size_;
}

std::vector<Pesanan> Queue::toVector() const {
    std::vector<Pesanan> hasil;
    hasil.reserve(size_);

    Node<Pesanan>* current = front_;
    while (current != nullptr) {
        hasil.push_back(current->data);
        current = current->next;
    }

    return hasil;
}

void Queue::clear() {
    Node<Pesanan>* current = front_;
    while (current != nullptr) {
        Node<Pesanan>* next = current->next;
        delete current;
        current = next;
    }

    front_ = nullptr;
    rear_ = nullptr;
    size_ = 0;
}
