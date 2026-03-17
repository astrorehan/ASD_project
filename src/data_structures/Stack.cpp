#include "Stack.h"

Stack::Stack() : top_(nullptr), size_(0) {}

Stack::~Stack() {
    clear();
}

void Stack::push(const Pesanan& pesanan) {
    auto* nodeBaru = new Node<Pesanan>(pesanan);
    nodeBaru->next = top_;
    top_ = nodeBaru;
    ++size_;
}

bool Stack::pop(Pesanan& outPesanan) {
    if (top_ == nullptr) {
        return false;
    }

    Node<Pesanan>* topLama = top_;
    outPesanan = topLama->data;
    top_ = topLama->next;

    delete topLama;
    --size_;
    return true;
}

bool Stack::peek(Pesanan& outPesanan) const {
    if (top_ == nullptr) {
        return false;
    }

    outPesanan = top_->data;
    return true;
}

bool Stack::empty() const {
    return size_ == 0;
}

std::size_t Stack::size() const {
    return size_;
}

std::vector<Pesanan> Stack::toVector() const {
    std::vector<Pesanan> hasil;
    hasil.reserve(size_);

    Node<Pesanan>* current = top_;
    while (current != nullptr) {
        hasil.push_back(current->data);
        current = current->next;
    }

    return hasil;
}

void Stack::clear() {
    Node<Pesanan>* current = top_;
    while (current != nullptr) {
        Node<Pesanan>* next = current->next;
        delete current;
        current = next;
    }

    top_ = nullptr;
    size_ = 0;
}
