#include "quicksort.h"

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}

void quick_sort(int *arr, int left, int right)
{
    if (left >= right)
        return;

    int leftI = left - 1;
    int rightI = right + 1;
    int pivot = arr[left + (right - left) / 2];
    while (1)
    {
        while (arr[++leftI] < pivot);
        while (arr[--rightI] > pivot);
        if (leftI >= rightI)
            break;
        swap(&arr[leftI], &arr[rightI]);
    }

    quick_sort(arr, left, rightI);
    quick_sort(arr, rightI + 1, right);
}
