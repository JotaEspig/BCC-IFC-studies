package main

func BubbleSort[T number](arr []T) {
	length := len(arr)
	swaped := false
	for range length - 1 {
		for j := 0; j < length-1; j++ {
			if arr[j] > arr[j+1] {
				swap(&arr[j], &arr[j+1])
				swaped = true
			}
		}

		if !swaped {
			break
		}
	}
}
