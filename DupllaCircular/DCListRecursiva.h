#ifndef DCLISTRECURSIVA_H
#define DCLISTRECURSIVA_H

#include <iostream>
#include "DNode.h"

using namespace std;

struct DCListRecursiva{
    DNode * head;

    DCListRecursiva(){
        head = new DNode;
    }

    DCListRecursiva * criar (){
        return NULL;
    }

    ~DCListRecursiva(){
        destroy();
        delete head;
    }

    void _rclone(DNode * node, DNode * node_fim){
        if(node->next == node){
            insert(node->value);
            return;
        }
        else if(node == node_fim)
            return;
        insert(node->value);
        _rclone(node->next, node_fim);
    }
    //copia os valores da lista passada para a lista referenciada
    void clone(DCListRecursiva lista_other){
        destroy();
        _rclone(lista_other.head->next, lista_other.head->prev);
    }

    void _rinsert(DNode * node, int value){
        if(head->next == nullptr){
            DNode * node_new = new DNode(value);
            node_new->next = node_new;
            node_new->prev = node_new;
            head->next = node_new;
            head->prev = node_new;
            return;
        }else if(node->value >= value){
            DNode * node_new = new DNode(value);
            if(node == head->next) {//se for o primeiro
                node_new->next = node;
                node_new->prev = node->prev;
                node->prev = node_new;
                head->next = node_new;
                return;
            }
            node_new->next = node;
            node_new->prev = node->prev;
            node->prev->next = node_new;
            node->prev = node_new;
            return;
        }
        else if(node->value == head->prev->value){
            auto node_new = new DNode(value, node->next, node);
            node->next->prev = node_new;
            node->next = node_new;
            head->prev = node_new;
        }
        _rinsert(node->next, value);
    }

    void insert(int value){
        auto node = head->next;
        _rinsert(node, value);
    }

    void _rdestroy(DNode * node){
        if(is_empty())
            return;
        auto aux = node->next;
        remove(node->value);
        _rdestroy(aux);
    }

    void destroy(){
        _rdestroy(head->next);
    }

    DNode * _rremove(DNode * node, int value){
        if(node->value == value){
            if(size() == 1){
                head->next = nullptr;
                head->prev = nullptr;
            }
            else{
                if(head->next == node) //se for o inicio
                    head->next = node->next;
                if(head->prev == node) //se for o ultimo
                    head->prev = node->prev;
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            delete node;
            return new DNode(value);
        }
        if(is_empty())
            return nullptr;
        return _rremove(node->next, value);
    }

    DNode * remove(int value){
        if(is_empty())
            return nullptr;
        return _rremove(head->next, value);
    }

    void _rprint(DNode * node){
        if(head->next == nullptr || head->prev == nullptr)
            return;
        else if(size() == 1){
            cout << node->value << " ";
        }
        else if(node != head->prev){
            cout << node->value << " ";
            _rprint(node->next);
        }
    }

    void print(){
        DNode * node = head->next;
        cout << "[ ";
        _rprint(node);
        cout << "]";

    }

    void _rreverse_print(DNode * node){
        if(head->next == nullptr || head->prev == nullptr)
            return;
        else if(size() == 1){
            cout << node->value << " ";
        }
        else if(node != head->prev){
            _rprint(node->next);
            cout << node->value << " ";
        }
    }

    void reverse_print(){
        auto node = head->next;
        cout << "[ ";
        _rreverse_print(node);
        cout << "]";
    }

    int _rsize(DNode * node){
        if(node->next == node && node->prev == node)
            return 1;
        if(head->next == nullptr || node == head->prev)
            return 0;
        return 1 + _rsize(node->next);
    }

    int size(){
        return _rsize(head->next);
    }

    bool is_empty(){
        return head->next == nullptr;
    }

    DNode * _rfind(DNode * node, int value){
        if(node->value == value)
            return node;
        else if(node == nullptr || node == head->prev)
            return nullptr;
        return _rfind(node->next, value);
    }

    DNode * find(int value){
        return _rfind(head->next, value);
    }

};

#endif // DCLISTRECURSIVA_H
