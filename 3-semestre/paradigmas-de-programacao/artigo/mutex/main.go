package main

import (
	"fmt"
	"sort"
	"sync"
	"time"
)

type SafeStruct struct {
	sync.Mutex // Embedding a mutex into the struct
	nums       []int
}

func NewSafeStruct() *SafeStruct {
	return &SafeStruct{nums: make([]int, 0)}
}

func (s *SafeStruct) AddNum(num int) {
	s.Lock()
	defer s.Unlock() // the same as calling s.Unlock() at the end of function
	s.nums = append(s.nums, num)
}

func main() {
	s := NewSafeStruct()
	for i := range 100 {
		go s.AddNum(i)
	}
	time.Sleep(1 * time.Second)

	s.Lock()
	sort.Ints(s.nums)
	fmt.Println(s.nums)
	s.Unlock()
}
