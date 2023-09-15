package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	fmt.Println("Hey")
	length := 100000
	list := make([]int, length)
	for i := 0; i < length; i++ {
		list[i] = rand.Int() % length
	}
	fmt.Println("append done")
	fmt.Println("Now heapsort")

	var media float32 = 0.0
	amount := 100
	for i := 0; i < amount; i++ {
		now := time.Now()
		_ = HeapSortV1(list)
		media += float32(time.Now().Sub(now).Milliseconds())
	}
	media /= float32(amount)
	fmt.Printf("media V1: %.3fms\n", media)

	media = 0
	for i := 0; i < amount; i++ {
		now := time.Now()
		_ = HeapSortV2(list)
		media += float32(time.Now().Sub(now).Milliseconds())
	}
	media /= float32(amount)
	fmt.Printf("media V2: %.3fms\n", media)
}
