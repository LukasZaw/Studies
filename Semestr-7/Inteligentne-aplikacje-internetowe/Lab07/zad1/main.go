package main

import (
	"fmt"
	"math"
)

type FSET interface {
	Calculate(x float64) float64
}

type FuzzySetGauss struct {
	x, o float64
}

func (f *FuzzySetGauss) Calculate(x float64) float64 {
	return math.Exp(-(f.x-x)*(f.x-x) / (2.0 * f.o * f.o))
}

type FuzzySetRect struct {
	a, b, c, d float64
}

func (f *FuzzySetRect) Calculate(x float64) float64 {
	if x < f.a || x > f.d {
		return 0.0
	}
	if x >= f.b && x <= f.c {
		return 1.0
	}
	if x < f.b {
		return (x - f.a) / (f.b - f.a)
	}
	return (f.d - x) / (f.d - f.c)
}

func Aggregate(sets []FSET, x float64) float64 {
	t := 1.0
	for _, s := range sets {
		t *= s.Calculate(x)
	}
	return t
}

func scanNearHalf(name string, set FSET, step, eps float64) {
	fmt.Printf("%s: bliskie 0.5 \n", name)
	found := 0
	for x := 0.0; x <= 1.0+1e-12; x += step {
		v := set.Calculate(x)
		if math.Abs(v-0.5) <= eps {
			fmt.Printf("  x=%.2f -> %.4f\n", x, v)
			found++
		}
	}
	if found == 0 {
		fmt.Println("brak trafien")
	}
	fmt.Println()
}

func scanNearHalfAgg(name string, sets []FSET, step, eps float64) {
	fmt.Printf("%s:  blisko 0.5 \n", name)
	found := 0
	for x := 0.0; x <= 1.0+1e-12; x += step {
		v := Aggregate(sets, x)
		if math.Abs(v-0.5) <= eps {
			fmt.Printf("  x=%.2f -> %.4f\n", x, v)
			found++
		}
	}
	if found == 0 {
		fmt.Println("brak trafien")
	}
	fmt.Println()
}

func main() {
	frect := FuzzySetRect{0.1, 0.3, 0.5, 0.8}
	fgaus := FuzzySetGauss{0.4, 0.2}

	step := 0.01
	eps := 0.05

	scanNearHalf("FuzzySetRect", &frect, step, eps)
	scanNearHalf("FuzzySetGauss", &fgaus, step, eps)


	sets := []FSET{&frect, &fgaus}
	scanNearHalfAgg("Rect Gauss", sets, step, eps)

	// przyklady
	x := 0.4
	fmt.Printf("Przykład: x=%.3f, iloczyn=%.3f\n",
		x,
		Aggregate(sets, x),
	)
}
