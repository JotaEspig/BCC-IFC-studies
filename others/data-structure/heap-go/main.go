package main

import "fmt"

func main() {
	fmt.Println("Hey")
	root := NewHeap([]int{22, 15, 7, 2, 1})
	root.Heapify()
	root.Print(0)
	root.MyFunc()
	root.Print(0)
	root.MyFunc()
	root.Print(0)
	root.MyFunc()
	root.Print(0)
}
