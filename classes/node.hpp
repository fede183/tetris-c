#ifndef NODE_HPP
#define NODE_HPP

template<class T>
struct Node {
    T data;
    struct Node* next;
};

#endif // NODE_HPP
