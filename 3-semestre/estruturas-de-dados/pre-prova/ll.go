package main

import "fmt"

type LinkedListNode struct {
	next  *LinkedListNode
	Value int
}

func NewLinkedListNode() *LinkedListNode {
	node := &LinkedListNode{}
	node.next = nil
	return node
}

type LinkedList struct {
	root *LinkedListNode
	size uint64
}

func NewLinkedList() *LinkedList {
	ll := &LinkedList{}
	ll.root = nil
	return ll
}

func (ll *LinkedList) InsertAt(value int, idx uint64) {
	if idx > ll.size {
		return
	}

	if ll.root == nil {
		ll.root = NewLinkedListNode()
		ll.root.Value = value
		ll.size++
		return
	}

	if idx == 0 {
		node := NewLinkedListNode()
		node.Value = value
		node.next = ll.root
		ll.root = node
		ll.size++
		return
	}
	var count uint64
	curr := ll.root
	var prev *LinkedListNode
	for count < idx {
		prev = curr
		curr = curr.next
		count++
	}
	prev.next = NewLinkedListNode()
	prev.next.Value = value
	prev.next.next = curr
	ll.size++
}

func (ll *LinkedList) Push_back(value int) {
	ll.InsertAt(value, ll.size)
}

func (ll *LinkedList) RemoveAt(idx uint64) {
	if idx >= ll.size {
		return
	} else if idx == 0 {
		ll.root = nil
		ll.size--
		return
	}

	var count uint64 = 0
	curr := ll.root
	var prev *LinkedListNode
	for count < idx {
		prev = curr
		curr = curr.next
		count++
	}
	prev.next = curr.next
	ll.size--
}

func (ll *LinkedList) At(idx uint64) *LinkedListNode {
	if idx >= ll.size {
		return nil
	}

	var count uint64 = 0
	curr := ll.root
	for count < idx {
		curr = curr.next
		count++
	}
	return curr
}

func (ll *LinkedList) Back() *LinkedListNode {
	return ll.At(ll.Size() - 1)
}

func (ll *LinkedList) Size() uint64 {
	return ll.size
}

func (ll *LinkedList) Print() {
	curr := ll.root
	for curr != nil {
		fmt.Printf("%d", curr.Value)
		curr = curr.next
		if curr != nil {
			fmt.Print(" ")
		}
	}
	fmt.Println()
}
