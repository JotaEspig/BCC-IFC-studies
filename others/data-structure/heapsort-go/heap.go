package main

import "fmt"

type HeapNode struct {
	data        int
	left, right *HeapNode
}

func NewHeapNode(data int) *HeapNode {
	node := &HeapNode{}
	node.data = data
	return node
}

func newHeapFromArrayRecursive(arr []int, i, n int) *HeapNode {
	if i >= n {
		return nil
	}

	node := NewHeapNode(arr[i])
	node.left = newHeapFromArrayRecursive(arr, 2*i+1, n)
	node.right = newHeapFromArrayRecursive(arr, 2*i+2, n)
	return node
}

func NewHeapFromArray(arr []int) *HeapNode {
	length := len(arr)
	if length == 0 {
		return nil
	}

	node := newHeapFromArrayRecursive(arr, 0, length)
	return node
}

func (h *HeapNode) Heapify() {
}

func (h *HeapNode) Print(i ...int) {
	if len(i) == 0 {
		i = append(i, 0)
	}
	fmt.Printf("%d: ", i[0])
	fmt.Println(h.data)

	i = []int{i[0] + 1}
	if h.left != nil {
		h.left.Print(i...)
	}
	if h.right != nil {
		h.right.Print(i...)
	}
}
