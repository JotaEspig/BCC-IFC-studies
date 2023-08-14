package main

import (
	"fmt"
	"gosh/pkg/shell"
)

func main() {
	fmt.Println("Hello World")
	shell.NewShell().Run()
}
