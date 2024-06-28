package main

type Queue struct {
	LinkedList
}

func NewQueue() *Queue {
	queue := &Queue{}
	queue.root = nil
	return queue
}

func (q *Queue) Get() *LinkedListNode {
	return q.Back()
}

func (q *Queue) Add(value int) {
	q.InsertAt(value, 0)
}

func (q *Queue) Pop() {
	q.RemoveAt(q.size - 1)
}
