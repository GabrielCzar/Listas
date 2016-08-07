#ifndef SNODE_H
#define SNODE_H

template<class T> //tipo generico
struct SNode{
    T value;
    SNode * next; //Ponteiro pro prox nó

    SNode(T value = 0, SNode * next = nullptr){
        this->value = value;
        this->next = next;
    }
};

#endif // SNODE_H
