#pragma once

#include <vector>

#include "Node.h"
#include "../models/Pesanan.h"

class Queue {
public:
    Queue();
    ~Queue();

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void enqueue(const Pesanan& pesanan);
    bool dequeue(Pesanan& outPesanan);
    bool peek(Pesanan& outPesanan) const;

    bool empty() const;
    std::size_t size() const;
    std::vector<Pesanan> toVector() const;

private:
    void clear();

    Node<Pesanan>* front_;
    Node<Pesanan>* rear_;
    std::size_t size_;
};
