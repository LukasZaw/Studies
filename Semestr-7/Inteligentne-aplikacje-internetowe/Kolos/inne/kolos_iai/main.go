package main

import (
	"encoding/json"
	"fmt"
	"log"
	"math"
	"net/http"
	"strings"
	"text/template"
)

type RowerElektryczny struct {
	Nazwa       string
	Zasieg      float64
	Maxpredkosc float64
	Rozmiarkol  float64
	Ocena       float64
	Dopasowanie float64
}

func roznica(obA, obB RowerElektryczny) float64 {
	czZasieg := math.Abs(obA.Zasieg-obB.Zasieg) / 200.0
	czMaxp := math.Abs(obA.Maxpredkosc-obB.Maxpredkosc) / 50.0
	czRkol := math.Abs(obA.Rozmiarkol-obB.Rozmiarkol) / 15.0
	return czZasieg + czMaxp + czRkol
}

var tpl = template.Must(template.ParseFiles(
    "templates/rowery.html",
	"templates/rower.html",
))

func main() {
	//zad 1
	rowery := []RowerElektryczny{
		{Nazwa: "Rower1", Zasieg: 80, Maxpredkosc: 41, Rozmiarkol: 25, Ocena: 8.2},
		{Nazwa: "Rower2", Zasieg: 140, Maxpredkosc: 45, Rozmiarkol: 29, Ocena: 9.1},
		{Nazwa: "Eco rower", Zasieg: 60, Maxpredkosc: 20, Rozmiarkol: 24, Ocena: 7.4},
	}

	fmt.Println("Lista rowerów elektrycznych:")
	for _, rower := range rowery {
		fmt.Printf("Nazwa: %s, Zasięg: %.1f km, Max prędkość: %.1f km/h, Rozmiar koła: %.1f cali, Ocena: %.1f\n",
			rower.Nazwa, rower.Zasieg, rower.Maxpredkosc, rower.Rozmiarkol, rower.Ocena)
	}

	fmt.Println("Różnice między rowerami: ", roznica(rowery[0], rowery[1]))

	//zad 3
	http.HandleFunc("/rowery", func(w http.ResponseWriter, r *http.Request) {
		if err := tpl.ExecuteTemplate(w, "rowery.html", rowery); err != nil {
			http.Error(w, "Błąd serwera", http.StatusInternalServerError)
			return
		}
	})
	//json
	http.HandleFunc("/roweryjson", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json; charset=utf-8")
		if err := json.NewEncoder(w).Encode(rowery); err != nil {
			http.Error(w, "Błąd serwera", http.StatusInternalServerError)
			return
		}
	})

	//zad 4
	http.HandleFunc("/rower/", func(w http.ResponseWriter, r *http.Request) {
		name := strings.TrimPrefix(r.URL.Path, "/rower/")
		if name == "" {
			http.Error(w, "Brak nazwy roweru", http.StatusBadRequest)
			return
		}

		var found *RowerElektryczny
		for i := range rowery {
			if rowery[i].Nazwa == name {
				found = &rowery[i]
				break
			}
		}

		if err := tpl.ExecuteTemplate(w, "rower.html", found); err != nil {
			http.Error(w, "Błąd serwera", http.StatusInternalServerError)
			return
		}
	})

	//json
	http.HandleFunc("/rowerjson/", func(w http.ResponseWriter, r *http.Request) {
		name := strings.TrimPrefix(r.URL.Path, "/rower/")
		if name == "" {
			http.Error(w, "Brak nazwy roweru", http.StatusBadRequest)
			return
		}

		var found *RowerElektryczny
		for i := range rowery {
			if rowery[i].Nazwa == name {
				found = &rowery[i]
				break
			}
		}

		if found == nil {
			http.Error(w, "Nie znaleziono roweru", http.StatusNotFound)
			return
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