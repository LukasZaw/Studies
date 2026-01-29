package kmeans

import (
	"math"
	"math/rand"
)

type point struct {
	x []float64
}

func NewPointRandom(n int) point {
	x := make([]float64, n)
	for i := range x {
		x[i] = rand.Float64() * rand.Float64() * rand.Float64()
	}
	return point{x}
}

func (p *point) distance(o *point) float64 {
	dist := 0.0
	for i := range p.x {
		dist += (p.x[i] - o.x[i]) * (p.x[i] - o.x[i])
	}
	return math.Sqrt(dist)
}

func (p *point) closestcluster(c []cluster) *cluster {
	cls := &c[0]
	dst := c[0].center.distance(p)
	for i := 1; i < len(c); i++ {
		tmp := c[i].center.distance(p)
		if tmp < dst {
			dst = tmp
			cls = &c[i]
		}
	}
	return cls
}
