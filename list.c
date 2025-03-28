#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* lista = (List*)malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
     return lista;
}

void * firstList(List * list) {
    if(!list->head)return NULL;
    list->current = list->head;
    return list->head->data;
    
}

void * nextList(List * list) {
    if(!list->current || !list->current->next)return NULL;
    list->current = list->current->next;
    return list->current->data;
}


void * lastList(List * list) {
    if(!list->head){
        return NULL;
    } else {
        list->current = list->head;
        while(list->current->next){
            list->current = list->current->next;
        }
        return list->current->data;
    }
}

void * prevList(List * list) {
    if(!list->current || !list->current->prev)return NULL;

    Node* aux = list->head;
    while(aux->next != list->current){
        aux = aux->next;
    }
    list->current = aux;
    return aux->data;
}

void pushFront(List * list, void * data) {
    Node* newNodo = createNode(data);
    if(!list->head){
        list->head = newNodo;
        list->tail = newNodo;
    } 
    newNodo->next = list->head;
    list->head->prev = newNodo;
    list->head = newNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node* newNodo = createNode(data);
    newNodo->prev = list->current;
    if(!list->current->next){
        list->current->next = newNodo;
        list->tail = newNodo;
    } else {
        newNodo->next = list->current->next;
        newNodo->next->prev = newNodo;
        list->current->next = newNodo;
    }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node* aux = list->head;
    void* data = list->current->data;

    if(!list->current) return NULL;

    if(aux == list->current){
        aux = aux->next;
        if(list->head) aux->prev = NULL;
        list->tail = NULL;

    list->current = aux;
    }
    while (aux->next != list->current){
        aux = aux->next;
    }
    if(aux) {
        aux->next = list->current->next;
        if(list->current->next)list->current->prev = aux;
        free(list->current);
        list->current = aux->next;
    }
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}