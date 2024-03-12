package main

import "fmt"

func main() {
	fmt.Println("Matrix calculator")
	m1, _ := New([][]float32{{0.5, 0.2, 1}, {-2, 3, 7}})
	m2, _ := New([][]float32{{4, -4}, {10, -5}, {-1, -2}})

	m1.Print()
	m2.Print()

	m3, _ := m1.Multiply(m2)
	m3.Print()
	fmt.Println(m3.Determinant())
	m3.Inverse()
}
