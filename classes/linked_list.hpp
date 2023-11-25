#include <stdlib.h>
#include "node.hpp"

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template<class T>
struct LinkedList
{
    size_t size;
    struct Node<T>* first;
    struct Node<T>* last;
};

#endif // LINKED_LIST_HPP