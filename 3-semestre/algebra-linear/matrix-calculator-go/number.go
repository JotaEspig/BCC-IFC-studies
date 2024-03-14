package matrix

import "fmt"

type Fraction struct {
	Numerator, Denominator int64
}

func Frac(numerator, denominator int64) Fraction {
	return Fraction{numerator, denominator}
}

func (n Fraction) Neg() Fraction {
	return Fraction{-n.Numerator, -n.Denominator}
}

func (n Fraction) Add(other Fraction) Fraction {
	r := Fraction{}
	if n.Denominator == other.Denominator {
		r.Numerator = n.Numerator + other.Numerator
		r.Denominator = n.Denominator
	} else {
		r.Numerator = n.Numerator*other.Denominator + other.Numerator*n.Denominator
		r.Denominator = n.Denominator * other.Denominator
	}

	return r
}

func (n Fraction) Sub(other Fraction) Fraction {
	return n.Add(other.Neg())
}

func (n Fraction) Mult(other Fraction) Fraction {
	return n
}

func (n Fraction) String() string {
	if n.Denominator == 1 {
		return fmt.Sprintf("%d", n.Numerator)
	} else {
		return fmt.Sprintf("%d/%d", n.Numerator, n.Denominator)
	}
}
