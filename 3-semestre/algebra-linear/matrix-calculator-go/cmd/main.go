package main

import "fmt"
import "matrix"

func frac(n, d int64) matrix.Fraction {
	return matrix.Frac(n, d)
}

func main() {
	fmt.Println("matrix. calculator")

	data := [][]matrix.Fraction{
		{frac(0, 1), frac(-1, 1), frac(-2, 1), frac(2, 1), frac(1, 1)},
		{frac(1, 1), frac(-1, 1), frac(0, 1), frac(1, 1), frac(0, 1)},
		{frac(1, 1), frac(0, 1), frac(-4, 1), frac(1, 1), frac(-1, 2)},
		{frac(-1, 1), frac(-2, 1), frac(0, 1), frac(-1, 1), frac(0, 1)},
		{frac(5, 1), frac(-20, 1), frac(-30, 1), frac(15, 1), frac(5, 2)},
	}

	m, _ := matrix.New(data)
	m.Print()
	x, err := m.Determinant()
	fmt.Println(x, err)
}
