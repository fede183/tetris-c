#include <iostream>
#include <stdbool.h>  

#include "../classes/linked_list.hpp"

template<class T>
LinkedList<T>* createList() {
    LinkedList<T>* newList = new LinkedList<T>();

    newList->first = NULL;
    newList->last = NULL;
    newList->size = 0;

    return newList;
}

template<class T>
void clean(LinkedList<T>* list) {
   while(list->first != NULL) {
        Node<T>* temporal = list->first;
        list->first = list->first->next;
        delete temporal;
    }
    delete list;
}

template<class T>
void push(LinkedList<T>* list, T data) {
    Node<T>* new_node = (Node<T>*) malloc(sizeof(Node<T>));
    new_node->data = data;
    new_node->next = NULL;
    if (list->first == NULL) {
        list->first = new_node;
    } else if (list->last == NULL) {
        list->first->next = new_node;
        list->last = new_node;
    } else {
        list->last->next = new_node;
        list->last = new_node;
    }
    list->size++;
}

template<class T>
void remove(LinkedList<T>* list, int index) {
    int size = list->size;
    Node<T>* node_to_delete;
    if (index == 0) {
        node_to_delete = list->first;
        list->first = list->first->next;
        if (size == 2) {
            list->last = NULL;
        }
        
    } else {
        Node<T>* node_iterator = list->first;
        
        for (int i = 0; i < index - 1; i++)
        {
            node_iterator = node_iterator->next;
        }
        
        if (size - 1 == index) {
            node_to_delete = list->last;
            list->last = node_iterator;
        } else {
            node_to_delete = node_iterator->next;
            node_iterator->next = node_iterator->next->next;
        }
    }
    
    delete node_to_delete;
    list->size--;
}

template<class T>
T get_value(LinkedList<T>* list, size_t index) {
    if (index == 0) {
        return list->first->data;
    } else if (index == list->size - 1) {
        return list->last->data;
    } else {
        Node<T>* node_iterator = list->first;
        for (int i = 0; i < index; i++)
        {
            node_iterator = node_iterator->next;
        }
        return node_iterator->data;
    }
}

template<class T>
T* get_all_values(LinkedList<T>* list) {
    Node<T>* node_iterator = list->first;
    unsigned int size = list->size;
    T* values = (T*) malloc(sizeof(T) * size);
    unsigned int i = 0;
    while (node_iterator != NULL) {
        values[i] = node_iterator->data;
        i++;
        node_iterator = node_iterator->next;
    }
    return values;
}

template<class T>
bool has_value(LinkedList<T>* list, T value, bool (*compare) (T, T)) {
    Node<T>* node_iterator = list->first;
    while (node_iterator != NULL)
    {
        if (compare(value, node_iterator->data)) 
            return true;
        node_iterator = node_iterator->next;
    }
    return false;
}