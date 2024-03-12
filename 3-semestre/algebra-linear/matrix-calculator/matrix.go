package main

import (
	"errors"
	"fmt"
)

type number interface {
	uint8 | uint16 | uint32 | uint64 | uint | int8 | int16 | int32 | int64 | int | float32 | float64
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

func New[T number](data [][]T) *Matrix[T] {
	r := uint16(len(data))
	if r == 0 {
		panic(errors.New("rows amound cannot be zero"))
	}

	c := uint16(len(data[0]))
	if c == 0 {
		panic(errors.New("rows amound cannot be zero"))
	}

	return &Matrix[T]{r, c, data}
}

func (m *Matrix[T]) Multiply(m2 *Matrix[T]) *Matrix[T] {
	if m.columns != m2.rows {
		errorMsg := fmt.Sprintf("Cannot multiply matrix: m.c == %d and m2.r == %d", m.columns, m2.rows)
		panic(errors.New(errorMsg))
	}

	result := NewWithoutData[T](m.rows, m2.columns)
	for i := range m.rows {
		for j := range m2.columns {
			for k := range m2.rows {
				result.data[i][j] += m.data[i][k] * m2.data[k][j]
			}
		}
	}

	return result
}

func (m Matrix[T]) Print() {
	fmt.Println(m.data)
}
