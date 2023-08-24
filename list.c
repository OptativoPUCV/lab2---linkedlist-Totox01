#include "list.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
  void *data;
  Node *next;
  Node *prev;
};

struct List {
  Node *head;
  Node *tail;
  Node *current;
};

typedef List List;

Node *createNode(void *data) {
  Node *new = (Node *)malloc(sizeof(Node));
  assert(new != NULL);
  new->data = data;
  new->prev = NULL;
  new->next = NULL;
  return new;
}

List *createList() {
  List *list = (List *)malloc(sizeof(List));
  if (list != NULL) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
  }
  return list;
}

void *firstList(List *list) {
  if (list != NULL && list->head != NULL) {
    list->current = list->head;
    return list->current->data;
  }
  return NULL; 
}

void *nextList(List *list) {
  if (list != NULL && list->current != NULL && list->current->next != NULL) {
    list->current = list->current->next;
    return list->current->data;
  }
  return NULL; 
}

void *lastList(List *list) {
  if (list != NULL && list->tail != NULL){
    list->current = list->tail;
    return list->current->data;
  }
  return NULL; 
}

void *prevList(List *list) {
  if (list != NULL && list->current != NULL && list->current->prev != NULL){
    list->current = list->current->prev;
    return list->current->data;
  }
  return NULL; 
}

void pushFront(List *list, void *data) {
  if (list != NULL){
    Node *nuevoNodo = createNode(data);
    if (nuevoNodo != NULL){
      nuevoNodo->next = list->head;
      if (list->head != NULL){
        list->head->prev = nuevoNodo;
      }
      list->head = nuevoNodo;
      if (list->tail == NULL){
        list->tail = nuevoNodo;
      }
    }
  }
}

void pushBack(List *list, void *data) {
  list->current = list->tail;
  pushCurrent(list, data);
}

void pushCurrent(List *list, void *data) {
  if (list != NULL && list->current != NULL){
    Node *nuevoNodo = createNode(data);
    if (nuevoNodo != NULL){
      nuevoNodo->next = list->current->next;
      nuevoNodo->prev = list->current;
      if (list->current->next != NULL){
        list->current->next->prev = nuevoNodo;
      }
      list->current->next = nuevoNodo;
      if (list->tail == list->current){
        list->tail = nuevoNodo;
      }
    }
  }
}

void *popFront(List *list) {
  list->current = list->head;
  return popCurrent(list);
}

void *popBack(List *list) {
  list->current = list->tail;
  return popCurrent(list);
}

void *popCurrent(List *list) {
  if (list != NULL && list->current != NULL){
    void *data = list->current->data;
    Node *nodoActual = list->current;
    if (list->current->prev != NULL){
      list->current->prev->next = list->current->next;
    } else {
      list->tail = list->current->next;
    }
    if (list->current->next != NULL){
      list->current->next->prev = list->current->prev;
    } else {
      list->tail = list->current->prev;
    }
    list->current = list->current->next;
    free(nodoActual);
    return data;
  }
  return NULL;
}

void cleanList(List *list) {
  while (list->head != NULL) {
    popFront(list);
  }
}