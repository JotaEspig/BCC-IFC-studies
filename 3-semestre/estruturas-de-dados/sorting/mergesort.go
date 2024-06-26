package main

func recMergeSort[T number](arr []T) []T {
	length := len(arr)
	if length <= 1 {
		return arr
	}

	mid := length / 2
	arr1 := recMergeSort(arr[0:mid])
	arr2 := recMergeSort(arr[mid:length])
	aux := merge(arr1, arr2)
	return aux
}

func merge[T number](arr1 []T, arr2 []T) []T {
	len1 := len(arr1)
	len2 := len(arr2)
	aux := make([]T, len1+len2)
	i := 0
	j := 0
	for i < len1 && j < len2 {
		if arr2[j] > arr1[i] {
			aux[i+j] = arr1[i]
			i++
		} else {
			aux[i+j] = arr2[j]
			j++
		}
	}

	for i < len1 {
		aux[i+j] = arr1[i]
		i++
	}

	for j < len2 {
		aux[i+j] = arr2[j]
		j++
	}

	return aux
}

func MergeSort[T number](arr []T) {
	length := uint(len(arr))
	mid := length / 2
	arr1 := recMergeSort(arr[:mid])
	arr2 := recMergeSort(arr[mid:length])
	aux := merge(arr1, arr2)
	for i := range length {
		arr[i] = aux[i]
	}
}
