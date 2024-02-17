#ifndef UNTYPED_T
#define UNTYPED_T

#include <stdio.h>
#include <stdlib.h>

enum untyped_type
{
    INT,
    STR
};

typedef struct untyped
{
    void *value;
    enum untyped_type type;
} *untyped_t;

untyped_t untyped_new_int(int value);
untyped_t untyped_new_str(char *value);
int untyped_get_int(untyped_t untyped);
char *untyped_get_str(untyped_t untyped);
void untyped_print(untyped_t untyped);

//int main()
//{
//    bomba_t arr[10];
//    for (int i = 0; i < 10; ++i)
//    {
//        if (i % 2 == 0)
//        {
//            arr[i] = new_bomba_int(i);
//        }
//        else
//        {
//            arr[i] = new_bomba_str("fuck");
//        }
//    }
//    print(arr, 10);
//
//    return 0;
//}

#endif
