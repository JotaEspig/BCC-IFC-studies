package main

func InsertionSort[T number](arr []T) {
	length := len(arr)
	for i := 1; i < length; i++ {
		aux := i
		for aux-1 >= 0 && arr[aux-1] > arr[aux] {
			swap(&arr[aux-1], &arr[aux])
			aux--
		}
	}
}
