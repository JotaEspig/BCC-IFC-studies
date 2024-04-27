// go run main.go
package main

import "fmt"

func main() {
	maxi := 10
outer:
	for i := 1; i < maxi; i++ {
		for j := i; j < maxi; j++ {
			if i%j == 0 {
				continue
			} else if j%i == 0 {
				continue outer
			}
			fmt.Println(i, j)
		}
	}
}
