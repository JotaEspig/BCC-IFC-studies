package main

import (
	"fmt"
	"goproxy/pkg/proxy"
)

func main() {
	fmt.Println("Hello, World!")
	p := proxy.NewProxy(8080)
	p.Run()
}
