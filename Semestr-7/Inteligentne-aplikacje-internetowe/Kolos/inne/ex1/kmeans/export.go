package kmeans

import "fmt"

type trace struct {
	X    []float64 `json:"x"`
	Y    []float64 `json:"y"`
	Z    []float64 `json:"z"`
	Mode string    `json:"mode"`
	Type string    `json:"type"`
	Name string    `json:"name"`
}

func (k *kmeans) Export() []trace {
	c := k.clusters
	traces := make([]trace, 0)
	for i := range c {
		x := []float64{}
		y := []float64{}
		z := []float64{}
		for p := range c[i].closest {
			x = append(x, c[i].closest[p].x[0])
			y = append(y, c[i].closest[p].x[1])
			z = append(z, c[i].closest[p].x[2])
		}
		traces = append(traces, trace{
			X:    x,
			Y:    y,
			Z:    z,
			Mode: "markers",
			Type: "scatter3d",
			Name: fmt.Sprintf("Grupa %d", i+1),
		})
	}
	return traces
}
