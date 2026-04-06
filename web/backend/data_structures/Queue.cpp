#include "Queue.h"
#include <stdexcept>

Queue::Queue() : front(nullptr), rear(nullptr), length(0) {}

Queue::~Queue() {
    clear();
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

int Queue::size() const {
    return length;
}

void Queue::enqueue(Pesanan pesananBaru) {
    Node* newNode = new Node();
    newNode->data = pesananBaru;
    newNode->next = nullptr;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    length++;
}

Pesanan Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue is empty");
    }

    Node* temp = front;
    Pesanan data = temp->data;

    if (front == rear) {
        front = rear = nullptr;
    } else {
        front = front->next;
    }

    delete temp;
    length--;
    return data;
}

Pesanan* Queue::getAt(int index) {
    if (index < 0 || index >= length) return nullptr;

    Node* current = front;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return &(current->data);
}

bool Queue::updateAt(int index, Pesanan newData) {
    Pesanan* target = getAt(index);
    if (!target) return false;
    *target = newData;
    return true;
}

bool Queue::removeAt(int index) {
    if (index < 0 || index >= length) return false;

    if (index == 0) {
        Node* temp = front;
        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
        }
        delete temp;
    } else {
        Node* prev = front;
        for (int i = 0; i < index - 1; i++) {
            prev = prev->next;
        }
        Node* target = prev->next;
        prev->next = target->next;
        if (target == rear) {
            rear = prev;
        }
        delete target;
    }
    length--;
    return true;
}

void Queue::calculateTime() {
    int estimasi = 0;
    Node* current = front;
    while (current != nullptr) {
        estimasi += current->data.durasiLayananMenit;
        current->data.estimasiSelesai = estimasi;
        current = current->next;
    }
}

void Queue::clear() {
    while (!isEmpty()) {
        dequeue();
    }
}
