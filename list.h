#ifndef LIST_H
#define LIST_H

#include "node.h"

template <typename T>
class List {
    protected:
        Node<T>* head;
        Node<T>* tail;
        int nodes;

    public:
        List() : head(nullptr), tail(nullptr), nodes(0) {};

        virtual T front() = 0;
        virtual T back() = 0;
        virtual void push_front(T) = 0;
        virtual void push_back(T) = 0;
        virtual void pop_front() = 0;
        virtual void pop_back() = 0;
        virtual T operator[](int) = 0;
        virtual bool empty() = 0;
        virtual int size() = 0;
        virtual void clear() = 0;
        virtual void sort() = 0;
        virtual void reverse() = 0;
        virtual string name() = 0;

        Node<T>* getNode(int index ) {
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
        };

    //}
        ~List() {
            // TODO
        }
};

#endif