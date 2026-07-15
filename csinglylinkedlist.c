#include "csinglylinkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// List wrapper struct. Use List pointers to initialize lists:
// List* myList = createList();
typedef struct List {
    Node* head;
    Node* tail;
    int size;
} List;

// The Node structure. Includes a void pointer which is intended to point to user data. The next pointer points to the next node. 
// Not intended for usage by the coder.
typedef struct Node {
    void* data;
    struct Node* next;
} Node;

// Allocates memory for list creation. Usage:
// List* myList = createList();
List* createList() {
    List* newList = malloc(sizeof(List));
    newList->head = NULL;
    return newList;
}

// Node factory - gets a data pointer and stores it to a functonal node.
// Not intended for usage by the coder.
static Node* createNode(void* newData) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = newData;
    newNode->next = NULL;

    return newNode;
}

// Returns list data based on the index used.
// \note
// Typecast the returned void pointer to your desired pointer type before attempting to access the data.
void* get(List* lst, int k) {
    if (k < 0 || k >= lst->size) {
        printf("Index out of bounds.\n");
        return NULL;
    }
    Node* helper = lst->head;
    for (int i = 0; i < k; i++) {
        helper = helper->next;
    }
    return helper->data;
}
// Returns list node based on the index used.
// Not intended for usage by the coder.
static Node* getNode(List* lst, int k) {
    Node* helper = lst->head;
    for (int i = 0; i < k; i++) {
        helper = helper->next;
    }
    return helper;
}

// Creates a node which contains the data pointer and gets pushed to the end of the desired list.
void add(List* lst, void* newData) {
    if (newData == NULL) {
        printf("NULL data provided. Operation cancelled.");
        return;
    }

    lst->size ++;

    Node* newNode = createNode(newData);
    if (lst->head == NULL) {
        lst->head = newNode;
        lst->tail = newNode;
        return;
    }   

    lst->tail->next = newNode;
    lst->tail = newNode;
}

// Prints the whole list.
// Provide a function that would print one element of your desired data type.
// - Your custom function must take void* as an argument.
// - Typecast the argument void pointer to your desired pointer type.
// - Set the print function as you would.
void printList(List* lst, PrintFunc pf) {
    if (lst->size == 0) {
        printf("Empty list.");
        return;
    }

    Node* curr = lst->head;
    for (int i = 0; i < lst->size; i++) {
        pf(curr->data);
        curr = curr->next;
    }
}

// Returns the size of the list.
int size(List* lst) {
    return lst->size;
}

// Prints an element of the list based on the index provided.
// Provide a function that would print one element of your desired data type.
// - Your custom function must take void* as an argument.
// - Typecast the argument void pointer to your desired pointer type.
// - Set the print function as you would.
void print(List* lst, int k, PrintFunc pf) {
    if (k < 0 || k >= lst->size) {
        printf("Index out of bounds.\n");
        return;
    }
    Node* curr = lst->head;
    for (int i = 0; i < k; i++) {
        curr = curr->next;
    }
    pf(curr->data);
    printf("\n");
}

// Deletes an element from the list based on the index provided.
void pop(List* lst, int k) {
    if (k < 0 || k >= lst->size) {
        printf("Index out of bounds.\n");
        return;
    }

    Node* toDelete = getNode(lst, k);

    // Case 1: toDelete is strictly between the head and the tail of the list.
    if (toDelete != lst->head && toDelete != lst->tail) {
        getNode(lst, k-1)->next = toDelete->next;
    }
    // Case 2: toDelete is the head.
    else if (toDelete == lst->head && toDelete != lst->tail) {
        lst->head = toDelete->next;
        toDelete->next = NULL;
    }
    // Case 3: toDelete is the tail.
    else if (toDelete != lst->head && toDelete == lst->tail) {
        Node* newTail = getNode(lst, k-1);
        lst->tail = newTail;
        newTail->next = NULL;
    }
    // Case 4: default case + toDelete is the head & the tail.
    else if (lst->size == 1) {
        free(toDelete);
        lst->head = NULL;
        lst->tail = NULL;
        (lst->size)--;
        return;
    }

    // for case 1-3
    free(toDelete);
    (lst->size)--;
}