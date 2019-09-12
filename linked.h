#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template<typename T>
class LinkedList : public List<T> {
public:
    LinkedList() : List<T>() {}

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
            this->head = newNode;
            this->tail = newNode;
        } else {
            auto aux = this->head;

            while (aux->next != nullptr)
                aux = aux->next;

            aux->next = newNode;
            newNode->prev = aux;

            this->tail = newNode;
        }
        this->nodes++;
    }

    void pop_front() {
        if (this->nodes == 0) {
            throw runtime_error("Length must >= 1");
        } else {
            auto oldHeader = this->head;

            auto newHeader = oldHeader->next;
            newHeader->prev = nullptr;

            this->head = newHeader;

            oldHeader->killSelf();
            oldHeader = nullptr;
            delete oldHeader;

            this->nodes--;
        }
    }

    void pop_back() {
        if (this->nodes == 0) {
            throw runtime_error("Length must >= 1");
        } else {
            auto oldTail = this->tail;

            auto newTail = this->getNode(size() - 1 - 1);
            newTail->next = nullptr;
            this->tail = newTail;

            oldTail->killSelf();
            delete oldTail;
            this->nodes--;
        }
    }

    T operator[](int index) {
        return this->getNode(index)->data;
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

        this->head->killSelf();
        this->head = nullptr;

        while (aux2->next != nullptr) {

            aux = aux2;
            aux2 = aux2->next;

            aux->killSelf();
            delete aux;
        }

        if (aux2->next == nullptr) {
            aux->killSelf();
            //delete aux; //??? why >:v
        }

        this->tail->killSelf();
        this->tail = nullptr;
        this->nodes = 0;
    }

    void sort() {
        T *array = new T[this->nodes];
        int i = 0;
        auto aux = this->head;

        //array[0] = this->head->data;
        while (aux->next != nullptr) {
            array[i] = aux->data;
            aux = aux->next;
            i++;
        }
        array[i] = aux->data;

        std::sort(array, array + this->nodes);
        //aux = this->head->next;
        i = 1;
        this->head->data = array[0];
        aux = this->head;
        //aux = this->head->next;
        while (aux->next != nullptr) {
            aux->data = array[i];
            aux = aux->next;
            i++;
        }
    }

    void reverse() {
        switch (this->nodes) {
            case 1: {
            }
                break;
            case 2: {
                auto node_1 = this->head;
                auto node_2 = this->tail;

                this->tail = node_1;
                node_1->next = nullptr;
                node_1->prev = node_2;

                node_2->next = node_1;
                node_2->prev = nullptr;
                this->head = node_2;

            }
                break;
            default: {
                auto node_1 = this->head;
                auto node_2 = node_1->next;
                auto node_3 = node_2->next;

                this->tail = node_1;

                node_1->next = nullptr;
                node_1->prev = node_2;

                while (node_3->next != nullptr) {
                    node_2->next = node_1;
                    node_2->prev = node_3;

                    node_1 = node_2;
                    node_2 = node_3;
                    node_3 = node_3->next;
                }

                if (node_3->next == nullptr) {//last
                    node_2->next = node_1;
                    node_2->prev = node_3;

                    node_3->next = node_2;
                    node_3->prev = nullptr;
                    this->head = node_3;
                }

            } break;
        }
    }

    string name() {
        return "Linked List";
    }

    BidirectionalIterator<T> begin() {
        return BidirectionalIterator<T>(this->head);
    }

    BidirectionalIterator<T> end() {
        return BidirectionalIterator<T>(this->tail);
    }

    void merge(LinkedList<T> list) {
        auto aux = list.head;

        while (aux->next != nullptr) {
            this->push_back(aux->data);
            aux = aux->next;
        }

        if (aux->next == nullptr)
            this->push_back(aux->data);

        list.clear();
    }

    Node<T> *getNode(int index) {
        /*int i = 1;
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
        return aux->next;*/
        int i;
        Node<T>* aux;

        if ( index > this->nodes - 1 )
            throw runtime_error("Index out of lenght");

        auto left = this->nodes - index;
        auto right = this->nodes - index;

        if ( index == 0 ) {
            return this->head;
        } else if (index == this->nodes - 1 ) {
            return this->tail;
        }

        if ( left <= right) {
            aux = this->head;
            i=0;
            while(aux->next != nullptr) {

                if ( i == index) {
                    break;
                } else {
                    aux = aux->next;
                    i++;
                }
            }
        } else {
            aux = this->tail;

            i=this->nodes - 1;
            while(aux->prev != nullptr) {

                if ( i == index) {
                    break;
                } else {
                    aux = aux->prev;
                    i--;
                }
            }
        }

        return aux;
    }
};

#endif