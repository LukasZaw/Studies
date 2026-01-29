package main

import (
	"encoding/json"
	"fmt"
	"html/template"
	"log"
	"math"
	"net/http"
	"net/url"
	"strings"
)

type RowerElektryczny struct {
	Nazwa         string
	Zasieg        float64
	Maxpredkosc   float64
	Rozmiarkol    float64
	Ocena         float64
	Dopasowanie   float64
}

//zad 2
func roznica(obA, obB RowerElektryczny) float64 {
	czZasieg := math.Abs(obA.Zasieg-obB.Zasieg) / 200.0
	czMaxp := math.Abs(obA.Maxpredkosc-obB.Maxpredkosc) / 50.0
	czRkol := math.Abs(obA.Rozmiarkol-obB.Rozmiarkol) / 15.0
	return czZasieg + czMaxp + czRkol
}

// zad 3,4
var tpl = template.Must(template.ParseFiles(
    "templates/rowery.html",
	"templates/rower.html",
))


//zad 5
type Fuzzy struct {
	x, o float64
}

func (f *Fuzzy) U(x float64) float64 {
	return math.Exp(-(x-f.x)*(x-f.x) / f.o)
}

var fuz1, fuz2, fuz3 Fuzzy = Fuzzy{80.0, 15.0}, Fuzzy{40.0, 8.0}, Fuzzy{25.0, 8.0}

func Activation(zasieg, maxp, rkol float64) float64 {
	return fuz1.U(zasieg) * fuz2.U(maxp) * fuz3.U(rkol)
}


func main() {
	//zad 1
	rowery := []RowerElektryczny{
		{Nazwa: "Rower Speed", Zasieg: 80, Maxpredkosc: 41, Rozmiarkol: 25, Ocena: 8.2},
		{Nazwa: "Rower 2", Zasieg: 140, Maxpredkosc: 45, Rozmiarkol: 29, Ocena: 9.1},
		{Nazwa: "Eco rower", Zasieg: 60, Maxpredkosc: 20, Rozmiarkol: 24, Ocena: 7.4},
		{Nazwa: "Rower Trail", Zasieg: 190, Maxpredkosc: 35, Rozmiarkol: 27.5, Ocena: 9.0},
		{Nazwa: "Rower 5", Zasieg: 110, Maxpredkosc: 30, Rozmiarkol: 28, Ocena: 8.6},
	}
	fmt.Println("Dostępne rowery elektryczne:")
	for _, r := range rowery {
		fmt.Printf("- %s: Zasięg %.1f km, Max prędkość %.1f\n",r.Nazwa, r.Zasieg, r.Maxpredkosc)
	}

	// zad 2
	fmt.Println("Różnice między rowerami: ", roznica(rowery[0], rowery[1]))

	// zad 5
	var najlepszy RowerElektryczny
	bestScore := -1.0
	for i := range rowery {
		rowery[i].Dopasowanie = Activation(rowery[i].Zasieg, rowery[i].Maxpredkosc, rowery[i].Rozmiarkol)
	}
	for i := range rowery {
		if rowery[i].Dopasowanie > bestScore {
			
			bestScore = rowery[i].Dopasowanie
			najlepszy = rowery[i]
		}
	}

	fmt.Println("\nDopasowanie (Activation) dla każdego roweru:")
	for _, r := range rowery {
		fmt.Printf("- %s: %.10e\n", r.Nazwa, r.Dopasowanie)
	}

	fmt.Printf("\nNajlepiej dopasowany rower: %s dopasowanie = %.10e\n", najlepszy.Nazwa, najlepszy.Dopasowanie)

	// zad 6 - dwa najbardziej różne rowery wg funkcji roznica
	if len(rowery) >= 2 {
		maxDiff := -1.0
		var rA, rB RowerElektryczny
		for i := 0; i < len(rowery); i++ {
			for j := i + 1; j < len(rowery); j++ {
				diff := roznica(rowery[i], rowery[j])
				if diff > maxDiff {
					maxDiff = diff
					rA = rowery[i]
					rB = rowery[j]
				}
			}
		}
		fmt.Printf("\nNajbardziej różne rowery: %s i %s różnica = %.4f\n", rA.Nazwa, rB.Nazwa, maxDiff)
	}

	

	//zad 3
	http.HandleFunc("/rowery", func(w http.ResponseWriter, r *http.Request) {
		if err := tpl.ExecuteTemplate(w, "rowery.html", rowery); err != nil {
			http.Error(w, "Błąd serwera", http.StatusInternalServerError)
			return
		}
	})

	http.HandleFunc("/roweryjson", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json; charset=utf-8")
		if err := json.NewEncoder(w).Encode(rowery); err != nil {
			http.Error(w, "Błąd serwera", http.StatusInternalServerError)
			return
		}
	})

	//zad 4
	http.HandleFunc("/rower/", func(w http.ResponseWriter, r *http.Request) {
			namePart := strings.TrimPrefix(r.URL.Path, "/rower/")

			decoded, _ := url.PathUnescape(namePart)

			var found *RowerElektryczny
			for i := range rowery {
				if strings.EqualFold(rowery[i].Nazwa, decoded) {
					found = &rowery[i]
					break
				}
			}

			if found == nil {
				http.Error(w, "Rower nie znaleziony", http.StatusNotFound)
				return
			}

			tpl.ExecuteTemplate(w, "rower.html", found); 
			
		})

	// zad 4 JSON
	http.HandleFunc("/rowerjson/", func(w http.ResponseWriter, r *http.Request) {
        namePart := strings.TrimPrefix(r.URL.Path, "/rowerjson/")
        decoded, _ := url.PathUnescape(namePart)

        var found *RowerElektryczny
        for i := range rowery {
            if strings.EqualFold(rowery[i].Nazwa, decoded) {
                found = &rowery[i]
                break
            }
        }

        w.Header().Set("Content-Type", "application/json; charset=utf-8")
        if err := json.NewEncoder(w).Encode(found); err != nil {
            http.Error(w, "Błąd serwera", http.StatusInternalServerError)
            return
        }
    })

	fmt.Println("http://localhost:8080")
	log.Fatal(http.ListenAndServe(":8080", nil))
}
