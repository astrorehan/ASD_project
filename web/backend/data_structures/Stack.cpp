#include "Stack.h"
#include <stdexcept>

Stack::Stack() : top(nullptr), length(0) {}

Stack::~Stack() {
    clear();
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

int Stack::size() const {
    return length;
}

void Stack::push(Pesanan pesananBaru) {
    Node* newNode = new Node();
    newNode->data = pesananBaru;
    newNode->next = top;
    top = newNode;
    length++;
}

Pesanan Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Stack is empty");
    }
    Node* temp = top;
    Pesanan data = temp->data;
    top = top->next;
    delete temp;
    length--;
    return data;
}

Pesanan* Stack::peek() {
    if (isEmpty()) return nullptr;
    return &(top->data);
}

void Stack::clear() {
    while (!isEmpty()) {
        pop();
    }
}
