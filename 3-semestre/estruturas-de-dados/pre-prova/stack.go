package main

type Stack struct {
	LinkedList
}

func NewStack() *Stack {
	stack := &Stack{}
	stack.root = nil
	return stack
}

func (s *Stack) Get() *LinkedListNode {
	return s.Back()
}

func (s *Stack) Add(value int) {
	s.Push_back(value)
}

func (s *Stack) Pop() {
	s.RemoveAt(s.size - 1)
}
