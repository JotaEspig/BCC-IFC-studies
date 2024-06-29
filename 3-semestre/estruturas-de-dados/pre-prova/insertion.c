#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define swap(a, b)                                                             \
  {                                                                            \
    int t = *a;                                                                \
    *a = *b;                                                                   \
    *b = t;                                                                    \
  }

void insertion_sort(int *arr, int n) {
  for (int i = 1; i < n; ++i) {
    int j = i - 1;
    while (arr[j + 1] < arr[j]) {
      swap(&arr[j + 1], &arr[j]);
      --j;
    }
  }
}

int partition(int *arr, int start, int end) {
  int pivot = arr[end - 1];
  int smaller = 0;
  for (int i = 0; i < end - 1; ++i) {
    if (arr[i] < pivot) {
      swap(&arr[i], &arr[smaller]);
      ++smaller;
    }
  }
  swap(&arr[smaller], &arr[end - 1]);
  return smaller;
}

void quicksort(int *arr, int start, int end) {
  if (end <= start + 1)
    return;

  int pi = partition(arr, start, end);
  quicksort(arr, start, pi);
  quicksort(arr, pi + 1, end);
}

int main() {
  srand(time(NULL));
  int arr[10];
  for (int i = 0; i < 10; ++i)
    arr[i] = rand() % 100;

  // print arr
  for (int i = 0; i < 10; ++i)
    printf("%d ", arr[i]);
  printf("\n");
  insertion_sort(arr, 10);
  // print

  // == QUICK ==
  for (int i = 0; i < 10; ++i)
    printf("%d ", arr[i]);
  printf("\n");

  for (int i = 0; i < 10; ++i)
    arr[i] = rand() % 100;

  // print arr
  for (int i = 0; i < 10; ++i)
    printf("%d ", arr[i]);
  printf("\n");
  quicksort(arr, 0, 10);
  // print

  for (int i = 0; i < 10; ++i)
    printf("%d ", arr[i]);
  printf("\n");
  return 0;
}
