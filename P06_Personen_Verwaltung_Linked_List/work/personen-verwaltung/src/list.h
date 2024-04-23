#ifndef LIST_H
#define LIST_H

#include "person.h"

// Node structure for the linked list.
typedef struct node {
    person_t content; // Person data
    struct node *next; // Pointer to the next node in the list
} node_t;

// Initializes the linked list and returns a pointer to the anchor node.
node_t *list_init();

// Inserts a new person into the list in sorted order.
void list_insert(node_t *head, person_t person);

// Removes a person from the list.
void list_remove(node_t *head, person_t person);

// Checks if the list contains a given person already.
// Returns 1 if it's a duplicate, 0 otherwise.
int list_contains(node_t *head, person_t person);

// Displays all person objects in the list.
void list_show(node_t *head);

// Clears the list and frees all allocated memory.
void list_clear(node_t **head);

#endif //LIST_H
