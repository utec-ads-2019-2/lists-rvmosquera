#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T> {
    public:
        LinkedList() : List<T>() {}

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
                auto aux = this->tail;

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
                this->nodes--;
            }
        }

        void pop_back() {

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
            // TODO
        }

        void sort() {
            // TODO
        }

        virtual Node<T>* getNode(int index ) {
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

        void reverse() {
            // TODO
        }

        string name() {
            return "Linked List";
        }

        BidirectionalIterator<T> begin() {
            // TODO
        }

	    BidirectionalIterator<T> end() {
            // TODO
        }

        void merge(LinkedList<T> list) {
            // TODO
        }
};

#endif