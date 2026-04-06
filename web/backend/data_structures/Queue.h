#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <vector>
#include <functional>

class Queue {
private:
    Node* front;
    Node* rear;
    int length;

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    void enqueue(Pesanan pesananBaru);
    Pesanan dequeue();
    Pesanan* getAt(int index);
    bool updateAt(int index, Pesanan newData);
    bool removeAt(int index);
    void calculateTime();
    int size() const;

    template<typename Func>
    void traverse(Func&& func) const {
        Node* current = front;
        while (current != nullptr) {
            func(current->data);
            current = current->next;
        }
    }

    void clear();
};

#endif
