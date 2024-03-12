package main

import (
	"errors"
	"fmt"
	"math"
)

type number interface {
	int8 | int16 | int32 | int64 | int | float32 | float64
}

type Matrix[T number] struct {
	rows    uint16
	columns uint16
	data    [][]T
}

func NewWithoutData[T number](r uint16, c uint16) *Matrix[T] {
	result := &Matrix[T]{}
	result.rows = r
	result.columns = c
	result.data = make([][]T, r)
	for i := range r {
		result.data[i] = make([]T, c)
	}
	return result
}

func New[T number](data [][]T) (*Matrix[T], error) {
	r := uint16(len(data))
	if r == 0 {
		return nil, errors.New("rows amound cannot be zero")
	}

	c := uint16(len(data[0]))
	if c == 0 {
		return nil, errors.New("rows amound cannot be zero")
	}

	return &Matrix[T]{r, c, data}, nil
}

func (m *Matrix[T]) MultiplyByScalar(num T) (*Matrix[T], error) {
	result, err := New(m.data)
	if err != nil {
		return nil, err
	}

	for i := range m.rows {
		for j := range m.columns {
			result.data[i][j] *= num
		}
	}
	return result, nil
}

func (m *Matrix[T]) Multiply(m2 *Matrix[T]) (*Matrix[T], error) {
	if m.columns != m2.rows {
		errorMsg := fmt.Sprintf("Cannot multiply matrix: m.c == %d and m2.r == %d", m.columns, m2.rows)
		return nil, errors.New(errorMsg)
	}

	result := NewWithoutData[T](m.rows, m2.columns)
	for i := range m.rows {
		for j := range m2.columns {
			for k := range m2.rows {
				result.data[i][j] += m.data[i][k] * m2.data[k][j]
			}
		}
	}

	return result, nil
}

func (m *Matrix[T]) Determinant() (T, error) {
	if m.rows-m.columns != 0 {
		return 0, errors.New("You cannot get a determinant from non-square matrix")
	}
	if m.rows == 1 && m.columns == 1 {
		return m.data[0][0], nil
	}

	var result T
	// It uses Laplace at first row every time
	row := uint16(0)
	for j := range m.columns {
		cofactor, err := m.Cofactor(row, j)
		if err != nil {
			return 0, err
		}
		det, err := cofactor.Determinant()
		if err != nil {
			return 0, err
		}

		result += m.data[row][j] * T(math.Pow(-1, float64(j))) * det
	}
	return result, nil
}

func (m *Matrix[T]) Cofactor(r, c uint16) (*Matrix[T], error) {
	if r >= m.rows || c >= m.columns {
		return nil, errors.New("Invalid cofactor matrix")
	}

	result := NewWithoutData[T](m.rows-1, m.columns-1)
	if result.rows == 0 || result.columns == 0 {
		return nil, errors.New("Invalid cofactor matrix")
	}

	var count1, count2 int
	for i := range m.rows {
		if i == r {
			continue
		}

		for j := range m.columns {
			if j == c {
				continue
			}

			result.data[count1][count2] = m.data[i][j]
			count2++
		}

		count2 = 0
		count1++
	}

	return result, nil
}

func (m *Matrix[T]) Inverse() (*Matrix[T], error) {
	if det, _ := m.Determinant(); det == 0 {
		return nil, errors.New("matrix: cannot get inverse, determinant == 0")
	}

	// Build matrix for Gauss-Jordan / Row reduction method
	aux := NewWithoutData[T](m.rows, m.columns*2)
	for i := range aux.rows {
		for j := range aux.columns {
			if j >= m.columns {
				if j-m.columns == i {
					aux.data[i][j] = 1
				}
			} else {
				aux.data[i][j] = m.data[i][j]
			}
		}
	}

	return aux.gaussJordan()
}

// TODO finish
func (m *Matrix[T]) gaussJordan() (*Matrix[T], error) {
	for col := range m.columns / 2 {
		// set pivot to one
		if m.data[col][col] == 0 {
			err := errors.New("Invalid gauss jordan: determinant == 0")
			for row := range m.rows {
				if m.data[row][col] != 0 {
					m.AddMultipliedRow(col, row, T(math.Pow(float64(m.data[row][col]), -1)))
					err = nil
					break
				}
			}

			if err != nil {
				return nil, err
			}

		} else {
			m.MultiplyRow(col, T(math.Pow(float64(m.data[col][col]), -1)))
		}

		for row := range m.rows {
			if col == row {
				continue
			}

			m.AddMultipliedRow(row, col, -1*m.data[row][col])
		}
	}

	result := NewWithoutData[T](m.rows, m.columns/2)
	colAux := 0
	for row := range m.rows {
		for col := m.columns / 2; col < m.columns; col++ {
			result.data[row][colAux] = m.data[row][col]
			colAux++
		}
		colAux = 0
	}
	return result, nil
}

// ----- Elementary operations -----

func (m *Matrix[T]) SwapLines(r1, r2 uint16) error {
	return nil
}

func (m *Matrix[T]) MultiplyRow(row uint16, num T) error {
	if row >= m.rows {
		return errors.New("invalid dest our source in MultiplyRow")
	}

	for j := range m.columns {
		m.data[row][j] = m.data[row][j] * num
	}

	return nil
}

func (m *Matrix[T]) AddMultipliedRow(dest, source uint16, num T) error {
	if dest >= m.rows || source >= m.rows {
		return errors.New("invalid dest our source in AddMultipliedRow")
	}

	for j := range m.columns {
		m.data[dest][j] += m.data[source][j] * num
	}
	return nil
}

func (m Matrix[T]) Print() {
	if m.rows == 0 {
		return
	}

	fmt.Println("[-")
	for i := range m.rows {
		fmt.Printf("%v,\n", m.data[i])
	}
	fmt.Println("-]")
}
