package main

import "fmt"

func main() {
	fmt.Println("Hey")
	list := []int{1, 15, 22, 7, 2}
	root := NewHeap(list)
	root.Print(0)
	sorted := HeapSort(list)
	fmt.Println(sorted)
}
