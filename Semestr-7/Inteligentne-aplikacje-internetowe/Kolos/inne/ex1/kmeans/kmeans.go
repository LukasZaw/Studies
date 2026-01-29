package kmeans

type kmeans struct {
	points   []point
	clusters []cluster
}

func NewKMeans(pts, cls, n int) *kmeans {
	p := make([]point, pts)
	for i := range p {
		p[i] = NewPointRandom(n)
	}
	c := make([]cluster, cls)
	for i := range c {
		c[i] = NewClusterRandom(n)
	}
	return &kmeans{
		points:   p,
		clusters: c,
	}
}

func (k *kmeans) Iterate() {
	for i := range k.clusters {
		k.clusters[i].reset()
	}
	for p := range k.points {
		cls := k.points[p].closestcluster(k.clusters)
		cls.addpoint(&k.points[p])
	}
	for i := range k.clusters {
		k.clusters[i].update()
	}
}
