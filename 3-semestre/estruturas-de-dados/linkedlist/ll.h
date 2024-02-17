#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "untyped.h"

typedef struct linked_list_node
{
    untyped_t value;
    struct linked_list_node *next;
} *linked_list_t;

linked_list_t ll_new();
linked_list_t ll_insert(linked_list_t *ll, untyped_t value);
void ll_print(linked_list_t ll);

#endif // LINKEDLIST_H
