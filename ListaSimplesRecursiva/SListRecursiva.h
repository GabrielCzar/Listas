#ifndef SLISTRECURSIVA_H
#define SLISTRECURSIVA_H

#include "SNode.h"
#include <iostream>

using namespace std;

struct SListRecursiva{
    SNode * head;

    SListRecursiva(){
        head = new SNode();
    }

    ~SListRecursiva(){
        destroy();
        delete head;
    }

    SListRecursiva(SListRecursiva & other){
        head = new SNode();
        head->next = _clone(this->head, other.head->next);
    }

   
    SNode * _clone(SNode * node, SNode * node_other){
        if (node_other == nullptr)
            return nullptr;
        node = new SNode (node_other->value);
        node->next = _clone (node->next, node_other->next);
        return node;
    }

    void push_front(int value){
        SNode * node = new SNode(value, head->next);
        head->next = node;
    }

    void push_back(int value){
        if(size() < 1)
            push_front(value);
        else
            back()->next = new SNode(value);
    }

    void destroy(){
        if(is_empty())
            return;
        pop_front();
        destroy();
    }

    void pop_front(){
        if(front() == nullptr)
            return;
        auto node = front();
        head->next = node->next;
        delete node;
    }

    void _rpop_back(SNode * node){
        if(node == nullptr)
            return;
        else if(node == back())
            pop_front();
        else if(node->next == back()){
            delete back();
            node->next = nullptr;
        }
        _rpop_back(node->next);
    }
    //tem q colocar o penultimo apontando pra nullptr
    void pop_back(){
        auto node = front();
        _rpop_back(node);
    }

   SNode * _rremove(SNode * node, SNode * node_anterior, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value){
            node_anterior->next = node->next;
            delete node;
            return new SNode(value);
        }
        return _rremove(node->next, node, value);
   }


    SNode * remove(int value){
        auto node = front(), node_anterior = head;
        return _rremove(node, node_anterior, value);
    }

    SNode * front(){
        return head->next;
    }

    SNode * _rback(SNode * node){
        if(node->next == nullptr)
            return node;
        return _rback(node->next);
    }

    SNode * back(){
        auto node = front();
        return _rback(node);
    }

    void _rprint(SNode * node){
        if(node != nullptr){
            cout << node->value << " ";
            _rprint(node->next);
        }
    }

    void print(){
        SNode * node = front();
        cout << "[ ";
        _rprint(node);
        cout << "]";

    }

    void _rreverse_print(SNode * node){
        if(node != nullptr){
            _rreverse_print(node->next);
            cout << node->value << " ";
        }
    }

    void reverse_print(){
        auto node = front();
        cout << "[ ";
        _rreverse_print(node);
        cout << "]";
    }

    int _rsize(SNode * node){
        if(node != nullptr)
            return 1 + _rsize(node->next);
        return 0;
    }

    int size(){
        SNode * node = front();
        return _rsize(node);
    }

    bool is_empty(){
        return front() == nullptr;
    }

    SNode * _rfind(SNode * node, int value){
        if(node == nullptr)
            return nullptr;
        if(node->value == value)
            return node;
        return _rfind(node->next, value);
    }

    SNode * find(int value){
        auto node = front();
        return _rfind(node, value);
    }

    bool _requals(SNode * node, SNode * node_other){
        if(node == nullptr || node_other == nullptr)
            return true;
        return _requals(node->next, node_other->next) && node->value == node_other->value;
    }

    bool equals(SListRecursiva list_other){
        if(size() != list_other.size())
            return false;
        auto node = front(), node_other = list_other.front();
        return _requals(node, node_other);
    }

};

#endif // SLISTRECURSIVA_H
