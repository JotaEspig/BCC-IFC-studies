package main

import "fmt"

func main() {
	fmt.Println("Matrix calculator")
	m1, _ := New([][]float64{{0.5, 0.2, 1}, {-2, 3, 7}})
	m2, _ := New([][]float64{{4, -4}, {10, -5}, {-1, -2}})
	aux, _ := New([][]float64{{0, 31, 6.4}, {-3, 0, -8}, {1, 5, 0}})

	m1.Print()
	m2.Print()

	m3, _ := m1.Multiply(m2)
	m3.Print()
	fmt.Println(m3.Determinant())
	a, _ := m3.Inverse()
	a.Print()
	a, _ = aux.Inverse()
	a.Print()

	z, _ := New([][]float64{
		{0, -1, -2, 2, 1},
		{1, -1, 0, 1, 0},
		{1, 0, -4, 1, -1.0 / 2},
		{-1, -2, 0, -1, 0},
		{5, -20, -30, 15, 5.0 / 2},
	})
	z.Print()
	fmt.Println(z.Determinant())
	inv, err := z.Inverse()
	if err == nil {
		inv.Print()
	}

	ex, _ := New([][]float64{
		{0, -2, 2, 1},
		{1, -4, 1, -1.0 / 2},
		{-1, 0, -1, 0},
		{5, -30, 15, 5.0 / 2},
	})
	fmt.Println(ex.Determinant())
}
