#include "inst_linked_list.h"

void ll_insert(char* s) {
    node_t* current = head_ptr;

    /* ensures insertion happens at the end of the list */
    while (current->next != NULL){
        current = current->next;
    }

    current->next = malloc(sizeof(struct node));
    current = current->next;

    current->data = d;
    current = current->next;
}
