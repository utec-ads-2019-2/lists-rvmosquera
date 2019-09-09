#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"
#include <algorithm>

template<typename T>
class ForwardList : public List<T> {
public:
    ForwardList() : List<T>() {}

    T front() {
        if ( this->head == nullptr )
            throw runtime_error("No header");

        return this->head->data;
    }

    T back() {
        if( this->tail == nullptr)
            throw runtime_error("No tail");

        return this->tail->data;
    }

    void push_front(T value) {
        // TODO
    }

    void push_back(T value) {
        Node<T> *newNode = new Node<T>();
        newNode->data = value;

        if( this->head == nullptr) {
            this->head = newNode;
            this->tail = newNode;
        } else {
            //auto aux = this->head;
            auto aux = this->tail;

            //while(aux->next != nullptr)
            //    aux = aux->next;

            aux->next = newNode;
            this->tail = newNode;
        }
        this->nodes++;
    }

    void pop_front() {
        if ( this->nodes == 0) {
            throw runtime_error("Length must >= 1");
        } else {
            auto oldHeader = this->head;

            auto newHeader = oldHeader->next;
            this->head = newHeader;

            oldHeader->killSelf();
            delete oldHeader;
            this->nodes--;
        }
    }

    void pop_back() {
        if ( this->nodes == 0) {
            throw runtime_error("Length must >= 1");
        } else {
            auto oldTail = this->tail;

            auto newTail = getNode(size()-1-1);
            newTail->next = nullptr;
            this->tail = newTail;

            oldTail->killSelf();
            delete oldTail;
            this->nodes--;
        }
    }

    T operator[](int index) {
        return getNode(index)->data;
    }

    bool empty() {
        return (this->nodes == 0)?true:false;
    }

    int size() {
        return this->nodes;
    }

    void clear() {
        auto aux = this->head;
        auto aux2 = aux->next;

        this->head->killSelf();
        this->head = nullptr;

        while(aux2->next != nullptr) {

            aux = aux2;
            aux2 = aux2->next;

            aux->killSelf();
            delete aux;
        }

        if ( aux2->next == nullptr) {
            aux->killSelf();
            //delete aux; //??? why >:v
        }

        this->tail->killSelf();
        this->tail = nullptr;
        this->nodes = 0;
    }

    void sort() {
        T *array = new T[this->nodes];
        int i=1;
        auto aux = this->head->next;

        array[0] = aux->data;
        while(aux->next != nullptr ) {
            aux = aux->next;
            array[i] = aux->data;
            i++;
        }

        std::sort(array, array+this->nodes);
        aux = this->head->next;
        i=1;
        aux->data = array[0];
        while (aux->next != nullptr) {
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
                node_1->next = nullptr;

                node_2->next = node_1;
                this->head = node_2;

            } break;
            default: {
                auto node_1 = this->head;
                auto node_2 = node_1->next;
                auto node_3 = node_2->next;

                this->tail = node_1;

                node_1->next = nullptr;

                while(node_3->next != nullptr) {
                    node_2->next = node_1;

                    node_1 = node_2;
                    node_2 = node_3;
                    node_3 = node_3->next;
                }

                if ( node_3->next == nullptr) {//last
                    node_2->next = node_1;
                    node_3->next = node_2;
                    this->head = node_3;
                }

            } break;
        }
    }

    string name() {
        return "Forward List";
    }

    ForwardIterator<T> begin() {
        // TODO
    }

    ForwardIterator<T> end() {
        // TODO
    }

    virtual Node<T> *getNode(int index) {
        int i=1;
        if ( index > this->nodes - 1 )
            throw runtime_error("Index out of lenght");

        auto aux = this->head;

        while(aux->next != nullptr && index != 0) {

            if ( i == index) {
                break;
            } else {
                aux = aux->next;
                i++;
            }
        }
        return aux->next;
    }

    void merge(ForwardList<T> list) {
        auto aux = list.head;

        //list.head->killSelf();

        while(aux->next != nullptr) {
            this->push_back( aux->data );
            aux = aux->next;
        }

        if( aux->next == nullptr)
            this->push_back(aux->data);

        list.clear();
    }
};

#endif