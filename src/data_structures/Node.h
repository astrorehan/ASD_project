#pragma once

template <typename T>
struct Node {
    explicit Node(const T& value) : data(value), next(nullptr) {}

    T data;
    Node<T>* next;
};
