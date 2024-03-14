package matrix

import (
	"errors"
	"fmt"
	"math"
)

type Matrix struct {
	rows    uint16
	columns uint16
	data    [][]Fraction
}

func NewWithoutData(r uint16, c uint16) *Matrix {
	result := &Matrix{}
	result.rows = r
	result.columns = c
	result.data = make([][]Fraction, r)
	for i := range r {
		result.data[i] = make([]Fraction, c)
		for j := range c {
			result.data[i][j] = Frac(0, 1)
		}
	}
	return result
}

func New(data [][]Fraction) (*Matrix, error) {
	r := uint16(len(data))
	if r == 0 {
		return nil, errors.New("rows amound cannot be zero")
	}

	c := uint16(len(data[0]))
	if c == 0 {
		return nil, errors.New("rows amound cannot be zero")
	}

	return &Matrix{r, c, data}, nil
}

func (m *Matrix) MultiplyByScalar(num Fraction) (*Matrix, error) {
	result, err := New(m.data)
	if err != nil {
		return nil, err
	}

	for i := range m.rows {
		for j := range m.columns {
			result.data[i][j] = result.data[i][j].Mult(num)
		}
	}
	return result, nil
}

func (m *Matrix) Multiply(m2 *Matrix) (*Matrix, error) {
	if m.columns != m2.rows {
		errorMsg := fmt.Sprintf("Cannot multiply matrix: m.c == %d and m2.r == %d", m.columns, m2.rows)
		return nil, errors.New(errorMsg)
	}

	result := NewWithoutData(m.rows, m2.columns)
	for i := range m.rows {
		for j := range m2.columns {
			for k := range m2.rows {
				result.data[i][j] = result.data[i][j].Add(m.data[i][k].Mult(m2.data[k][j]))
			}
		}
	}

	return result, nil
}

func (m *Matrix) Determinant() (Fraction, error) {
	if m.rows-m.columns != 0 {
		return Frac(0, 1), errors.New("You cannot get a determinant from non-square matrix")
	}
	if m.rows == 1 && m.columns == 1 {
		return m.data[0][0], nil
	}

	result := Frac(0, 1)
	// It uses Laplace at first row every time
	row := uint16(0)
	for j := range m.columns {
		cofactor, err := m.Cofactor(row, j)
		if err != nil {
			return Frac(0, 1), err
		}
		det, err := cofactor.Determinant()
		if err != nil {
			return Frac(0, 1), err
		}

		minus := int64(math.Pow(-1, float64(j)))
		result = result.Add(
			m.data[row][j].Mult(det).Mult(Frac(minus, 1)),
		)
	}
	return result, nil
}

func (m *Matrix) Cofactor(r, c uint16) (*Matrix, error) {
	if r >= m.rows || c >= m.columns {
		return nil, errors.New("Invalid cofactor matrix")
	}

	result := NewWithoutData(m.rows-1, m.columns-1)
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

func (m *Matrix) Inverse() (*Matrix, error) {
	if det, _ := m.Determinant(); det == Frac(0, 1) {
		return nil, errors.New("matrix: cannot get inverse, determinant == 0")
	}

	// Build matrix for Gauss-Jordan / Row reduction method
	aux := NewWithoutData(m.rows, m.columns*2)
	for i := range aux.rows {
		for j := range aux.columns {
			if j >= m.columns {
				if j-m.columns == i {
					aux.data[i][j] = Frac(1, 1)
				}
			} else {
				aux.data[i][j] = m.data[i][j]
			}
		}
	}

	return aux.gaussJordan()
}

// TODO finish
func (m *Matrix) gaussJordan() (*Matrix, error) {
	for col := range m.columns / 2 {
		// set pivot to one
		if m.data[col][col] == Frac(0, 1) {
			err := errors.New("Invalid gauss jordan: determinant == 0")
			for row := range m.rows {
				if m.data[row][col] != Frac(0, 1) {
					m.AddMultipliedRow(col, row,
						Frac(m.data[row][col].Denominator, m.data[row][col].Numerator))
					err = nil
					break
				}
			}

			if err != nil {
				return nil, err
			}

		} else {
			m.MultiplyRow(col, Frac(m.data[col][col].Denominator, m.data[col][col].Numerator))
		}

		for row := range m.rows {
			if col == row {
				continue
			}

			m.AddMultipliedRow(row, col, m.data[row][col].Neg())
		}
	}

	result := NewWithoutData(m.rows, m.columns/2)
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

func (m *Matrix) SwapLines(r1, r2 uint16) error {
	return nil
}

func (m *Matrix) MultiplyRow(row uint16, num Fraction) error {
	if row >= m.rows {
		return errors.New("invalid dest our source in MultiplyRow")
	}

	for j := range m.columns {
		m.data[row][j] = m.data[row][j].Mult(num)
	}

	return nil
}

func (m *Matrix) AddMultipliedRow(dest, source uint16, num Fraction) error {
	if dest >= m.rows || source >= m.rows {
		return errors.New("invalid dest our source in AddMultipliedRow")
	}

	for j := range m.columns {
		m.data[dest][j] = m.data[dest][j].Add(
			m.data[source][j].Mult(num),
		)
	}
	return nil
}

func (m Matrix) Print() {
	if m.rows == 0 {
		return
	}

	fmt.Println("[-")
	for i := range m.rows {
		for j := range m.columns {
			fmt.Printf("%s, ", m.data[i][j].String())
		}
		fmt.Println()
	}
	fmt.Println("-]")
}
