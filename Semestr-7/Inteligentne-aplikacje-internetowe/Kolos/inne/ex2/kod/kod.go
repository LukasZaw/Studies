package kod

import "math"

type Aparat struct {
	Nazwa              string  `json:"nazwa"`
	Liczba_megapikseli float64 `json:"liczba_megapikseli"`
	Rozmiar_matrycy    float64 `json:"rozmiar_matrycy"`
	Zoom_optyczny      float64 `json:"zoom_optyczny"`
}

var aparat = []Aparat{
		{
			Nazwa: "Canon EOS 5D Mark IV",
			Liczba_megapikseli: 30.4,
			Rozmiar_matrycy: 36.0,
			Zoom_optyczny: 1.0,
		},
		{
			Nazwa: "Nikon D850",
			Liczba_megapikseli: 45.7,
			Rozmiar_matrycy: 35.9,
			Zoom_optyczny: 1.0,
		},
	}


func Roznica(b *Aparat , a *Aparat) float64 {
	var suma float64 = 0.0
	suma += math.Abs(a.Liczba_megapikseli - b.Liczba_megapikseli)
	suma += math.Abs(a.Rozmiar_matrycy - b.Rozmiar_matrycy)
	suma += math.Abs(a.Zoom_optyczny - b.Zoom_optyczny)
	return suma
}


func ListaApartow() []Aparat {
	return aparat
}

func ListaApartowBiID(id int) *Aparat {
	return &aparat[id]
}

