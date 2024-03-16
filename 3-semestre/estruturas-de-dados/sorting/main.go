package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	{
		fmt.Println("Bubble Sort")
		example := rand.Perm(10000)
		now := time.Now()
		BubbleSort(example)
		fmt.Printf("%vms\n", time.Now().Sub(now).Milliseconds())
	}
	{
		fmt.Println("Insertion Sort")
		example := rand.Perm(10000)
		now := time.Now()
		InsertionSort(example)
		fmt.Printf("%vms\n", time.Now().Sub(now).Milliseconds())
	}
	{
		fmt.Println("Merge Sort")
		example := rand.Perm(10000)
		now := time.Now()
		MergeSort(example)
		fmt.Printf("%vms\n", time.Now().Sub(now).Milliseconds())
	}
}
