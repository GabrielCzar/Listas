#ifndef DLISTRECURSIVA_H
#define DLISTRECURSIVA_H

#include <iostream>
#include "DNode.h"

using namespace std;

struct DListRecursiva{
    DNode * head;
    DNode * tail;

    DListRecursiva(){
        head = new DNode;
        tail = new DNode;
        head->next = tail;
        tail->prev = head;
    }

    DListRecursiva * criar (){
        return NULL;
    }

    ~DListRecursiva(){
        destroy();
        delete head;
        delete tail;
    }

    void _rclone(DNode * node, DNode * final){
        if(node == final)
            return;
        push_back(node->value);
        _rclone(node->next, final);
    }

    void clone(DListRecursiva lista_other){
        destroy();
        auto node = lista_other.front();
        _rclone(node, lista_other.tail);
    }

    void push_front(int value){
        DNode * node = new DNode(value, front(), head);
        head->next->prev = node;
        head->next = node;
    }

    void push_back(int value){
        auto node = new DNode(value, tail, back());
        tail->prev->next = node;
        tail->prev = node;
    }

    void destroy(){
        if(size() < 1)
            return;
        pop_front();
        destroy();
    }

    void pop_front(){
        if(front() == tail)
            return;
        auto node = front();
        head->next = node->next;
        node->next->prev = head;
        delete node;

    }

    void pop_back(){
        if(back() == head)
            return;
        auto node = back();
        node->prev->next = tail;
        tail->prev = node->prev;
        delete node;
    }

    DNode * _rremove(DNode * node, int value){
        if(node == tail)
            return nullptr;
        else if(node->value == value){
            node->prev->next = node->next; //ant sabe prox
            node->next->prev = node->prev; //prox sabe ant
            delete node;
            return new DNode(value);
        }
        return _rremove(node->next, value);
    }

    DNode * remove(int value){
        auto node = front();
        return _rremove(node, value);
    }

    DNode * front(){
        return head->next;
    }

    DNode * back(){
        return tail->prev;
    }

    void _rprint(DNode * node){
        if(node != tail){
            cout << node->value << " ";
            _rprint(node->next);
        }
    }

    void print(){
        DNode * node = front();
        cout << "[ ";
        _rprint(node);
        cout << "]";

    }

    void _rreverse_print(DNode * node){
        if(node != head){
            cout << node->value << " ";
            _rreverse_print(node->prev);
        }
    }

    void reverse_print(){
        auto node = back();
        cout << "[ ";
        _rreverse_print(node);
        cout << "]";
    }

    int _rsize(DNode * node){
        if(node != tail)
            return 1 + _rsize(node->next);
        return 0;
    }

    int size(){
        DNode * node = front();
        return _rsize(node);
    }

    bool is_empty(){
        return head->next == tail;
    }

    DNode * _rfind(DNode * node, int value){
        if(node == tail)
            return nullptr;
        if(node->value == value)
            return node;
        return _rfind(node->next, value);
    }

    DNode * find(int value){
        auto node = front();
        return _rfind(node, value);
    }

    bool _requals(DNode * node, DNode * node_other){
        if(node == tail)
            return true;
        return _requals(node->next, node_other->next) && node->value == node_other->value;
    }

    bool equals(DListRecursiva list_other){
        if(size() != list_other.size())
            return false;
        auto node = front(), node_other = list_other.front();
        return _requals(node, node_other);
    }

};

#endif // DLISTRECURSIVA_H
