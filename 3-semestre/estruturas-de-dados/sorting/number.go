package main

type number interface {
	uint | uint8 | uint16 | uint32 | uint64 | int | int8 | int16 | int32 | int64 | float32 | float64
}

func swap[T number](a, b *T) {
	aux := *a
	*a = *b
	*b = aux
}
