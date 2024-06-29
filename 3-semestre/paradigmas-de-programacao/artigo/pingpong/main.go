package main

import (
	"fmt"
	"time"
)

func ping(c chan string) {
	for {
		time.Sleep(1 * time.Second)
		c <- "ping"
		fmt.Println(<-c)
	}
}

func pong(c chan string) {
	for {
		fmt.Println(<-c)
		time.Sleep(1 * time.Second)
		c <- "pong"
	}
}

func main() {
	c := make(chan string)
	go ping(c)
	go pong(c)
	time.Sleep(10 * time.Second)
}
