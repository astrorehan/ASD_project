#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <functional>

class Stack {
private:
    Node* top;
    int length;

public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    void push(Pesanan pesananBaru);
    Pesanan pop();
    Pesanan* peek();
    int size() const;

    template<typename Func>
    void traverse(Func&& func) const {
        for (Node* cur = top; cur != nullptr; cur = cur->next) {
            func(cur->data);
        }
    }

    void clear();
};

#endif
