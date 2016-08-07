#ifndef SNODE_H
#define SNODE_H

struct SNode{
    int value;
    SNode * next; //Ponteiro pro prox nó

    SNode(int value = 0, SNode * next = nullptr){
        this->value = value;
        this->next = next;
    }
};

#endif // SNODE_H
