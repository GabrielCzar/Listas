#ifndef SLIST_H
#define SLIST_H
#include <iostream>
#include <stack>

#include "SNode.h"

using namespace std;

template<class T> struct SList{

    SNode<T> * head;

    SList(){
        head = new SNode<T>();
    }

    SList(SList & other){
        head = new SNode<T>();
        head->next = clone(this->head, other.head->next);
    }

    ~SList<T>(){
        destroy();
        delete head;
    }

    SNode<T> * clone(SNode<T> * node, SNode<T> * node_other){
        if (node_other == nullptr)
            return nullptr;
        node = new SNode<T> (node_other->value);
        node->next = clone (node->next, node_other->next);
        return node;
    }

    void push_front(T value){ //add no inicio da lista
        SNode<T> * node = new SNode<T>(value, head->next);
        head->next = node;
    }

    void push_back(T value){
        if(is_empty())
            push_front(value);
        else
            back()->next = new SNode<T>(value);
    }

    void destroy(){
        while (!is_empty())
            pop_front();
    }

    void pop_front(){
        if(front() == nullptr)
            return;
        auto node = front();
        head->next = node->next;
        delete node;
    }

    void pop_back(){ //tem q colocar o penultimo apontando pra nullptr
        auto node = front();
        while (node->next != back())
            node = node->next;
        delete back();
        node->next = nullptr;
    }

    SNode<T> * remove(T value){
        for(auto node = front(), node_anterior = head;node != nullptr; node_anterior = node, node = node->next){
            if(node->value == value){
                node_anterior->next = node->next;
                delete node;
                return new SNode<T>(value);
            }
        }
        return nullptr;
    }

    SNode<T> * front(){ //retorna o primeiro nó
        return head->next;
    }

    SNode<T> * back(){ //Retorna o ultimo nó
        auto node = front();
        while (node->next != nullptr)
            node = node->next;
        return node;
    }

    void print(){
        SNode<T> * node = front();
        cout << "[ ";
        while (node != nullptr) {
            cout << node->value << " ";
            node = node->next;
        }
        cout << "]" << endl;
    }

    void reverse_print(){
        SList lista_aux;
        int cont = size();
        auto node = front();
        while (cont--) {
            lista_aux.push_front(node->value);
            node = node->next;
        }
        lista_aux.print();
    }

    int size(){
        int cont = 0;
        SNode<T> * node = front();
        while (node != nullptr) {
            node = node->next;
            cont ++;
        }
        return cont;
    }

    bool is_empty(){
        return front() == nullptr;
    }

    SNode<T> * find(int value){
        auto node = front();
        while (node != nullptr) {
            if(node->value == value)
                return node;
            node = node->next;
        }
        return nullptr;
    }

    bool equals(SList list_other){
        if(size() != list_other.size())
            return false;
        for (auto node = front(), node_lo = list_other.front(); node != nullptr; node = node->next, node_lo = node_lo->next)
            if(node->value != node_lo->value)
                return false;
        return true;
    }

};

#endif // SLIST_H
