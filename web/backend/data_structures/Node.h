#ifndef NODE_H
#define NODE_H

#include "../models/Pesanan.h"

struct Node {
    Pesanan data;
    Node* next;

    Node() : next(nullptr) {}
};

#endif
