#ifndef CLIST_H
#define CLIST_H

typedef struct List List;

typedef struct Node Node;

typedef void (*PrintFunc)(void*);

void printList(List*, PrintFunc);

List* createList();

static Node* createNode(void*);

void add(List*, void*);

static Node* getNode(List*, int);

void* get(List*, int);

int size(List*);

void print(List*, int, PrintFunc);

void pop(List*, int);

#endif