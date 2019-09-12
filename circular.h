#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template<typename T>
class CircularLinkedList : public List<T> {
public:
    CircularLinkedList() : List<T>() {}

    T front() {
        if (this->head == nullptr)
            throw runtime_error("No header");

        return this->head->data;
    }

    T back() {
        if (this->tail == nullptr)
            throw runtime_error("No tail");

        return this->tail->data;
    }

    void push_front(T value) {
        // TODO
    }

    void push_back(T value) {
        Node<T> *newNode = new Node<T>();
        newNode->data = value;

        if (this->head == nullptr) {
            newNode->next = newNode;
            newNode->prev = newNode;

            this->head = newNode;
            this->tail = newNode;
        } else {
            auto aux = this->head;

            while (aux->next != this->head)
                aux = aux->next;

            aux->next = newNode;
            this->head->prev = newNode;

            newNode->prev = aux;
            newNode->next = this->head;

            this->tail = newNode;
        }
        this->nodes++;
    }

    void pop_front() {
        auto oldHeader = this->head;
        auto newHeader = oldHeader->next;

        newHeader->prev  = this->tail;
        this->tail->next = newHeader;

        oldHeader->killSelf();
        oldHeader = nullptr;
        delete oldHeader;

        this->head = newHeader;

        this->nodes--;
    }

    void pop_back() {
        auto oldTail = this->tail;
        auto newTail = oldTail->prev;

        newTail->next  = this->head;
        this->head->prev = newTail;

        oldTail->killSelf();
        oldTail = nullptr;
        delete oldTail;

        this->tail = newTail;

        this->nodes--;
    }

    T operator[](int index) {
        auto mod = index % this->nodes;

        return this->getNode(mod)->data;
    }

    bool empty() {
        return (this->nodes == 0) ? true : false;
    }

    int size() {
        return this->nodes;
    }

    void clear() {
        auto aux = this->head;
        auto aux2 = aux->next;

        while (aux2->next != this->head) {

            aux = aux2;
            aux2 = aux2->next;

            aux->killSelf();
            delete aux;
        }

        if (aux2->next == this->head) {
            aux->killSelf();
            //delete aux; //??? why >:v
        }

        this->head->killSelf();
        this->head = nullptr;

        this->tail->killSelf();
        this->tail = nullptr;
        this->nodes = 0;
    }

    void sort() {
        T *array = new T[this->nodes];
        int i = 1;
        auto aux = this->head->next;

        array[0] = aux->data;
        while (aux->next != this->head) {
            aux = aux->next;
            array[i] = aux->data;
            i++;
        }

        std::sort(array, array + this->nodes);
        aux = this->head->next;
        i = 1;
        aux->data = array[0];
        while (aux->next != this->head) {
            aux = aux->next;
            aux->data = array[i];
            i++;
        }
    }

    void reverse() {
        switch (this->nodes) {
            case 1: {} break;
            case 2: {
                auto node_1 = this->head;
                auto node_2 = this->tail;

                this->tail = node_1;
                node_1->next = node_2;

                node_2->next = node_1;
                this->head = node_2;

            } break;
            default: {
                auto node_1 = this->head;
                auto node_2 = node_1->next;
                auto node_3 = node_2->next;

                this->tail = node_1;

                while(node_3->next != this->head) {
                    node_2->next = node_1;

                    node_1 = node_2;
                    node_2 = node_3;
                    node_3 = node_3->next;
                }

                if ( node_3->next == this->head) {//last
                    node_2->next = node_1;
                    node_3->next = node_2;
                    this->head = node_3;
                    this->tail->next = this->head;
                }

            } break;
        }
    }

    string name() {
        return "Circular Linked List";
    }

    BidirectionalIterator<T> begin() {
        return BidirectionalIterator<T>(this->head);
    }

    BidirectionalIterator<T> end() {
        return BidirectionalIterator<T>(this->tail);
    }

    void merge(CircularLinkedList<T> list) {
        auto aux = list.head;

        while (aux->next != list.head) {
            this->push_back(aux->data);
            aux = aux->next;
        }

        if (aux->next == list.head)
            this->push_back(aux->data);

        list.clear();
    }

    Node<T>* getNode(int index ) {

        int i = 1;
        if (index > this->nodes - 1)
            throw runtime_error("Index out of lenght");

        auto aux = this->head;

        while (aux->next != nullptr && index != 0) {

            if (i == index) {
                break;
            } else {
                aux = aux->next;
                i++;
            }
        }
        return aux->next;
    }
};

#endif