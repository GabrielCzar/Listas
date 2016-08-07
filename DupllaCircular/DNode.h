#ifndef DNODE_H
#define DNODE_H

struct DNode{
    int value;
    DNode * next;
    DNode * prev;

    DNode(int value = 0, DNode * next = nullptr, DNode * prev = nullptr){
        this->value = value;
        this->next = next;
        this->prev = prev;
    }
};

#endif // DNODE_H
