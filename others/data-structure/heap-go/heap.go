package main

import (
	"fmt"
)

type Heap struct {
	data   []int
	length int
}

func NewHeap(data []int) *Heap {
	h := &Heap{}
	h.length = len(data)
	h.data = make([]int, h.length)
	for idx, elem := range data {
		h.data[idx] = elem
	}
	h.Heapify(h.length)
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

func (h *Heap) LastNode(size int) int {
	return size - 1
}

func (h *Heap) Parent(idx int) int {
	return (idx - 1) / 2
}

func (h *Heap) IsLeaf(idx, size int) bool {
	return idx > (size/2) && idx < size
}

func (h *Heap) heapify(idx, size int) {
	if h.IsLeaf(idx, size) {
		return
	}

	largest := idx
	left := h.Left(idx)
	right := h.Right(idx)
	if left < size && h.data[left] > h.data[largest] {
		largest = left
	}
	if right < size && h.data[right] > h.data[largest] {
		largest = right
	}

	if largest != idx {
		h.data[largest], h.data[idx] = h.data[idx], h.data[largest]
		h.heapify(largest, size)
	}
}

func (h *Heap) Heapify(size int) {
	firstNonLeaf := h.Parent(h.LastNode(size))
	for i := firstNonLeaf; i >= 0; i-- {
		h.heapify(i, size)
	}
}

func (h *Heap) Insert(val int) {
	h.length++
	h.data = append(h.data, val)
	h.Heapify(h.length)
}

func (h *Heap) RemoveFirst() int {
	val := h.data[0]
	last := h.LastNode(h.length)
	h.data[0], h.data[last] = h.data[last], h.data[0]
	h.length--
	h.data = h.data[:last]
	// previously I was using h.Heapify, but it was damn slow compared to
	// h.heapify
	h.heapify(0, h.length)
	return val
}

func (h *Heap) Print(idx int) {
	for _, elem := range h.data {
		fmt.Printf("%d ", elem)
	}
	fmt.Println()
}

func HeapSortV1(data []int) []int {
	h := NewHeap(data)
	for i := h.length - 1; i > 0; i-- {
		h.data[0], h.data[i] = h.data[i], h.data[0]
		h.heapify(0, i)
	}
	return h.data
}

func HeapSortV2(data []int) []int {
	h := NewHeap(data)
	newData := make([]int, h.length)

	for i := h.length - 1; h.length != 0; i-- {
		newData[i] = h.RemoveFirst()
	}
	return newData
}
