#include "ll.h"
#include "untyped.h"

linked_list_t ll_new()
{
    linked_list_t ll = malloc(sizeof(struct linked_list_node));
    ll->next = 0;
    ll->value = 0;
    return ll;
}

linked_list_t ll_insert(linked_list_t *ll, untyped_t value)
{
    if (*ll == 0)
        return 0;

    linked_list_t new_node = ll_new();
    new_node->value = value;
    if ((*ll)->value == 0)
    {
        *ll = new_node;
        return *ll;
    }

    linked_list_t curr = *ll;
    while (curr->next != 0)
        curr = curr->next;

    curr->next = new_node;
    return *ll;
}

void ll_print(linked_list_t ll)
{
    linked_list_t curr = ll;
    while (curr != 0)
    {
        untyped_print(curr->value);
        curr = curr->next;
    }
}
