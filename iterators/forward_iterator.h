#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include "../iterator.h"

template <typename T> 
class ForwardIterator : public Iterator<T> {
    public:
        ForwardIterator() : Iterator<T>() {};
        ForwardIterator(Node<T> *node) : Iterator<T>(node) {};

        ForwardIterator<T> operator=(ForwardIterator<T> other) {
            return ForwardIterator(other.current);
        }

        bool operator!=(ForwardIterator<T> other) {
            return (this->current != other.current)?true:false;
        }

        ForwardIterator<T> operator++() {
            if(this->current)
                this->current = this->current->next;

            return *this;
        }

        T operator*() {
            return this->current->data;
        }
};

#endif