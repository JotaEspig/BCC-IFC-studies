package main

import "fmt"

func main() {
	// LinkedList
	fmt.Println("LinkedList")
	ll := NewLinkedList()
	fmt.Println("Adding")
	for i := range 10 {
		ll.Push_back(i)
		fmt.Printf("%d ", i)
	}
	fmt.Println()
	ll.RemoveAt(5)
	fmt.Println("After removing idx 5")
	ll.Print()

	// Stack
	fmt.Println()
	fmt.Println("Stack")
	s := NewStack()
	fmt.Println("Adding")
	for i := range 10 {
		s.Add(i)
		fmt.Printf("%d ", i)
	}
	fmt.Println()
	fmt.Println("Getting")
	for range 10 {
		fmt.Println(s.Back().Value)
		s.Pop()
	}

	// Queue
	fmt.Println()
	fmt.Println("Queue")
	q := NewQueue()
	fmt.Println("Adding")
	for i := range 10 {
		q.Add(i)
		fmt.Printf("%d ", i)
	}
	fmt.Println()
	fmt.Println("Getting")
	for range 10 {
		fmt.Println(q.Back().Value)
		q.Pop()
	}
}
