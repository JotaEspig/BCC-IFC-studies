package main

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan string)
	go func() {
		fmt.Println("Ola! Eu sou uma Goroutine!")
		fmt.Printf("Mensagem recebida: %s\n", <-ch)
	}()

	time.Sleep(2 * time.Second)
	ch <- "Ola da main"
	time.Sleep(2 * time.Second)
}
