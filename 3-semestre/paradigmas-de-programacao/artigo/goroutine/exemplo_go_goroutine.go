package main

import (
	"fmt"
	"time"
)

func main() {
	go func() {
		fmt.Println("Ola da Goroutine!")
	}()

	fmt.Println("Ola da main!")
	time.Sleep(1 * time.Second)
}
