package kmeans

type cluster struct {
	center  point
	closest []*point
}

func NewClusterRandom(n int) cluster {
	return cluster{
		center:  NewPointRandom(n),
		closest: make([]*point, 0),
	}
}

func (c *cluster) reset() {
	c.closest = make([]*point, 0)
}

func (c *cluster) addpoint(p *point) {
	c.closest = append(c.closest, p)
}

func (c *cluster) update() {
	for i := range c.center.x {
		c.center.x[i] = 0.0
	}
	for p := range c.closest {
		for i := range c.closest[p].x {
			c.center.x[i] += c.closest[p].x[i]
		}
	}
	for i := range c.center.x {
		c.center.x[i] /= float64(len(c.closest))
	}
}
