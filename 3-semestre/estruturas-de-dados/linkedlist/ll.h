#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stddef.h>

#include "untyped.h"

typedef struct ll_node
{
    untyped_t value;
    struct ll_node *next;
} *ll_node_t;

ll_node_t ll_node_new();
void ll_node_print(ll_node_t ll);
void ll_node_destroy(ll_node_t *node);

typedef struct linked_list
{
    ll_node_t head;
    size_t size;
} *linked_list_t;

linked_list_t ll_new();
void ll_insert(linked_list_t ll, untyped_t value);
void ll_insert_at(linked_list_t ll, size_t idx, untyped_t value);
// It destroys the previous item at the index and replaces it with value
void ll_assign(linked_list_t ll, size_t idx, untyped_t value);
ll_node_t ll_get_at(linked_list_t ll, size_t idx);
// It just remove the value from the linked list, it does not destroy it, You
// must do it using untyped_destroy()
ll_node_t ll_delete_at(linked_list_t ll, size_t idx);
void ll_print(linked_list_t ll);
void ll_destroy(linked_list_t *ll);

#endif // LINKEDLIST_H
