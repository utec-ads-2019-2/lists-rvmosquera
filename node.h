#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    void killSelf() {
        // TODO
        next = nullptr;
        prev = nullptr;
        delete next;
        delete prev;
    }
};

#endif