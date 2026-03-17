#pragma once

#include <vector>

#include "Node.h"
#include "../models/Pesanan.h"

class Stack {
public:
    Stack();
    ~Stack();

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const Pesanan& pesanan);
    bool pop(Pesanan& outPesanan);
    bool peek(Pesanan& outPesanan) const;

    bool empty() const;
    std::size_t size() const;
    std::vector<Pesanan> toVector() const;

private:
    void clear();

    Node<Pesanan>* top_;
    std::size_t size_;
};
