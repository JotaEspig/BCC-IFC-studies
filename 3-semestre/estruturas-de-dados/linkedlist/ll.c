#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "ll.h"
#include "untyped.h"

ll_node_t ll_node_new()
{
    ll_node_t node = malloc(sizeof(struct ll_node));
    node->value = NULL;
    node->next = NULL;
    return node;
}

void ll_node_print(ll_node_t node)
{
    assert(node != NULL);
    untyped_print(node->value);
}

void ll_node_destroy(ll_node_t *node)
{
    assert(node != NULL);
    if (*node == NULL)
        return;

    // Go recursive
    ll_node_destroy(&((*node)->next));

    untyped_destroy(&(*node)->value);
    free(*node);
    *node = NULL;
}

linked_list_t ll_new()
{
    linked_list_t ll = malloc(sizeof(struct linked_list));
    ll->head = ll_node_new();
    ll->size = 0;
    return ll;
}

void ll_insert(linked_list_t ll, untyped_t value)
{
    assert(ll != NULL);

    if (ll->head->value == NULL)
    {
        ll->head->value = value;
        ++ll->size;
        return;
    }

    ll_node_t new_node = ll_node_new();
    new_node->value = value;
    ll_node_t curr = ll->head;
    while (curr->next != NULL)
        curr = curr->next;

    curr->next = new_node;
    ++ll->size;
}

void ll_insert_at(linked_list_t ll, size_t idx, untyped_t value)
{
    assert(ll != NULL);
    assert(idx < ll->size);

    ll_node_t new_node = ll_node_new();
    new_node->value = value;

    ll_node_t *curr = &ll->head;
    ll_node_t prev = NULL;
    size_t i = 0;
    while (i < idx && (*curr)->next != NULL)
    {
        prev = *curr;
        curr = &(*curr)->next;
        ++i;
    }

    new_node->next = (*curr);
    *curr = new_node;
    if (prev)
        prev->next = new_node;
    ++ll->size;
}

void ll_assign(linked_list_t ll, size_t idx, untyped_t value)
{
    assert(ll != NULL);
    assert(idx < ll->size);

    ll_node_t curr = ll->head;
    size_t i = 0;
    while (i < idx && curr != NULL)
    {
        curr = curr->next;
        ++i;
    }

    untyped_destroy(&curr->value);
    curr->value = value;
}

ll_node_t ll_get_at(linked_list_t ll, size_t idx)
{
    assert(ll != NULL);
    assert(idx < ll->size);

    ll_node_t curr = ll->head;
    size_t i = 0;
    while (i < idx && curr != NULL)
    {
        curr = curr->next;
        ++i;
    }

    return curr;
}

ll_node_t ll_delete_at(linked_list_t ll, size_t idx)
{
    assert(ll != NULL);
    assert(idx < ll->size);

    size_t i = 0;
    ll_node_t *curr = &ll->head;
    while (i < idx && *curr != NULL)
    {
        curr = &(*curr)->next;
        ++i;
    }

    ll_node_t tmp = *curr;
    *curr = (*curr)->next;
    tmp->next = NULL;
    --ll->size;
    return tmp;
}

void ll_print(linked_list_t ll)
{
    assert(ll != NULL);
    ll_node_t curr = ll->head;
    if (curr == NULL)
        return;

    printf("[");
    while (curr != NULL)
    {
        ll_node_print(curr);
        curr = curr->next;
        printf("%s", curr ? ", " : "]\n");
    }
}

void ll_destroy(linked_list_t *ll)
{
    assert(ll != NULL);
    if (*ll == NULL)
        return;

    ll_node_destroy(&(*ll)->head);
    free(*ll);
    *ll = NULL;
}
