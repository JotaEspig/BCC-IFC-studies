#include "ll.h"
#include "untyped.h"

int main()
{
    linked_list_t ll = ll_new();
    
    untyped_t b = untyped_new_int(10);
    ll_insert(&ll, b);
    untyped_t c = untyped_new_str("FUck my ass");
    ll_insert(&ll, c);

    ll_print(ll);
}
