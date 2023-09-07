package main

import (
	"fmt"
	"math"
)

type Heap struct {
	data   []int
	length int
}

func NewHeap(data []int) *Heap {
	h := &Heap{}
	for _, elem := range data {
		h.data = append(h.data, elem)
	}
	h.length = len(data)
	return h
}

func (h *Heap) Left(currentIdx int) int {
	newIdx := 2*currentIdx + 1
	return newIdx
}

func (h *Heap) Right(currentIdx int) int {
	newIdx := 2*currentIdx + 2
	return newIdx
}

func (h *Heap) LastNode() int {
	return h.length - 1
}

func (h *Heap) Parent(idx int) int {
	return (idx - 1) / 2
}

func (h *Heap) heapify(idx int) {
	if idx >= h.length {
		return
	}

	largest := idx
	left := h.Left(idx)
	right := h.Right(idx)
	if left < h.length && h.data[left] > h.data[largest] {
		largest = left
	}
	if right < h.length && h.data[right] > h.data[largest] {
		largest = right
	}

	if largest != idx {
		h.data[largest], h.data[idx] = h.data[idx], h.data[largest]
		h.heapify(largest)
	}
}

func (h *Heap) Heapify() {
	firstNonLeaf := h.Parent(h.LastNode())
	for i := firstNonLeaf; i >= 0; i-- {
		h.heapify(i)
	}
}

func countAlg(a int) int {
	sum := 0
	size := math.Log10(float64(a)) + 1
	for size > 0 {
		sum += a % 10
		a /= 10
		size--
	}
	return sum
}

func (h *Heap) MyFunc() {
	h.data[0] -= countAlg(h.data[0])
	h.heapify(0)
}

func (h *Heap) Print(idx int) {
	for _, elem := range h.data {
		fmt.Printf("%d ", elem)
	}
	fmt.Println()
}
