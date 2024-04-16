// go run main.go
package main

/*
Concorrência usando "Channels" baseado em CSP (Communicating sequential processes)
*/

import (
	"fmt"
	"math"
	"sort"
	"sync"
)

func is_prime(num int) bool {
	if num == 0 || num == 1 {
		return false
	}

	for i := 2; i <= int(math.Sqrt(float64(num))); i++ {
		if num%i == 0 {
			return false
		}
	}
	return true
}

func concurrent_range_is_prime(wg *sync.WaitGroup, c chan int, start, end int) {
	defer wg.Done()
	for i := start; i < end; i++ {
		if is_prime(i) {
			c <- i
		}
	}
}

func main() {
	wg := &sync.WaitGroup{}
	c := make(chan int, 10000)
	for i := 1; i < 100; i++ {
		wg.Add(1)
		go concurrent_range_is_prime(wg, c, 100*(i-1), 100*i)
	}
	go func(wg *sync.WaitGroup, c chan int) {
		wg.Wait()
		close(c)
	}(wg, c)

	primes := []int{}
	for val := range c {
		primes = append(primes, val)
	}

	sort.Ints(primes)
	fmt.Println(primes)
}
