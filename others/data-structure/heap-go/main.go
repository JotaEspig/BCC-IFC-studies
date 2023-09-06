package main

import "fmt"

func main() {
	fmt.Println("Hey")
	root := NewHeapFromArray([]int{1, 3, 4, 7, 5, -1, 0})
	root.Print()
}
