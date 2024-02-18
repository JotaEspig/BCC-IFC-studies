#include <stdio.h>

#include "ll.h"
#include "untyped.h"
#include "utils.h"

int main()
{
    linked_list_t ll = ll_new();
    untyped_t b = untyped_new_int(42069);
    ll_insert(ll, move((void **)&b));
    printf("b = %p\n", b);

    untyped_t c = untyped_new_str("Bla");
    ll_insert(ll, move((void **)&c));
    printf("c = %p\n", c);

    untyped_t d = untyped_new_str("Bla 2");
    ll_insert(ll, move((void **)&d));
    printf("d = %p\n", d);

    untyped_t e = untyped_new_str("Bla 3");
    ll_insert(ll, move((void **)&e));
    printf("e = %p\n", e);

    ll_node_t deleted = ll_delete_at(ll, 3);
    ll_node_destroy(&deleted);

    for (int i = 0; i < 5; ++i)
        ll_insert(ll, untyped_new_int(i));

    int idx = 4;
    printf("\nGet at %d: ", idx);
    ll_node_print(ll_get_at(ll, idx));
    printf("\nAssign at %d\n", idx);
    ll_assign(ll, idx, untyped_new_int(10));
    printf("Get at %d: ", 10);
    ll_node_print(ll_get_at(ll, idx));
    printf("\n");
    ll_print(ll);

    ll_insert_at(ll, 0, untyped_new_str("Start"));
    ll_insert_at(ll, 1, untyped_new_str("Second"));
    ll_insert_at(ll, ll->size - 1, untyped_new_str("one before last"));

    ll_print(ll);

    ll_destroy(&ll);
}
