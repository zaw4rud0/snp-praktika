#include "list.h"
#include <stdlib.h>
#include <stdio.h>

node_t *list_init() {
    node_t *head = (node_t *) malloc(sizeof(node_t));
    if (head == NULL) {
        perror("Failed to initialize list");
        return NULL;
    }
    head->next = head; // Cyclic list
    return head;
}

void list_insert(node_t **head, person_t person) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        perror("Failed to insert in list");
        return;
    }
    new_node->content = person;

    node_t *current = *head;
    while(current->next != *head && person_compare(&current->next->content, &person) < 0) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
}

void list_remove(node_t **head, person_t person) {
    node_t *current = *head;
    node_t *prev = NULL;
    do {
        prev = current;
        current = current->next;
        if (person_compare(&current->content, &person) == 0) {
            prev->next = current->next;
            free(current);
            return;
        }
    } while (current != *head);
}

int list_contains(node_t *head, person_t person) {
    node_t *current = head->next;
    while (current != head) {
        if (person_compare(&current->content, &person) == 0) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void list_show(node_t *head) {
    node_t *current = head->next;
    while (current != head) {
        printf("Name: %s, First Name: %s, Age: %u\n",
               current->content.name,
               current->content.first_name,
               current->content.age
        );
        current = current->next;
    }
}

void list_clear(node_t **head) {
    node_t *current = (*head)->next;
    while (current != *head) {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }
    (*head)->next = *head;
}