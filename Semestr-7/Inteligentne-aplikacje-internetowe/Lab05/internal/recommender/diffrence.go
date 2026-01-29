package recommender

import (
	"Lab05/internal/model"
	"math"
)

func Difference(u1, u2 model.User) float64 {
	// mapy ocen
	m1 := make(map[int]float64)
	m2 := make(map[int]float64)

	for _, r := range u1.Rates {
		if r.Rate > 0 {
			m1[r.Movie] = r.Rate
		}
	}
	for _, r := range u2.Rates {
		if r.Rate > 0 {
			m2[r.Movie] = r.Rate
		}
	}

	var C float64
	var D float64
	var diffSum float64

	// Zbiór wszystkich filmów
	allMovies := make(map[int]bool)
	for movie := range m1 {
		allMovies[movie] = true
	}
	for movie := range m2 {
		allMovies[movie] = true
	}

	D = float64(len(allMovies))

	for movie, rate1 := range m1 {
		if rate2, ok := m2[movie]; ok {
			C++
			diffSum += math.Abs(rate1 - rate2)
		}
	}

	if C == 0 || D == 0 {
		return math.Inf(1)
	}

	A := C / D
	B := diffSum / C
	roznica := (0.5 + A) * B
	print(C)

	return roznica
}
