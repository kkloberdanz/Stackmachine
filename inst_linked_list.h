#ifndef INST_LINKED_LIST_H
#define INST_LINKED_LIST_H

#define BUFF_SIZE 255

typedef struct node {
    char[BUFF_SIZE] str;
    struct node     *next;
} node_t;

void ll_insert(char*, node_t);

#endif /* INST_LINKED_LIST_H */
