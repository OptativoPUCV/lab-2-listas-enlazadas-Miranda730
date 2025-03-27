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
    if(!list->head){
        return NULL;
    } else {
        list->current = list->head;
        return list->head->data;
    }
}

void * nextList(List * list) {
    if(!list->current || !list->current->next){
        return NULL;
    } else {
        list->current = list->current->next;
        return list->current->data;
    }
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
    if(!list->current || !list->current->prev || !list){
        return NULL;
    }
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
    } 
    list->head->prev = newNodo;
    newNodo->next = list->head,
    newNodo = list->head;
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
    } else {
        newNodo->next = list->current->next;
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
    while (aux->next != list->current){
        aux = aux->next;
    }
    aux->next = list->current->next;
    void * data = list->current->data;
    free(list->current);
    list->current = aux->next;
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}