package web

import (
	"encoding/json"
	"fmt"
	"labmobile/fuzzy"
	"net/http"
	"sort"
	"strings"
	"text/template"
)

var phones []*Phone

func indexFunc(w http.ResponseWriter, r *http.Request) {
	tl, _ := template.ParseFiles("pages/index.html")
	tl.Execute(w, nil)
}

func searchFunc(w http.ResponseWriter, r *http.Request) {
	query := r.PathValue("query")
	data := ParseData(query)

	// tworzenie zbiorów rozmytych
	fsetScreen := data.GetSet("screen")
	fsetBattery := data.GetSet("battery")
	fsetWeight := data.GetSet("weight")
	fsetRAM := data.GetSet("ram")
	fsetPrice := data.GetSet("price")
	fsetCamBack := data.GetSet("camback")
	fsetCamFront := data.GetSet("camfront")

	// obliczenie dopasowania rozmytego (value) dla wszystkich telefonów
	for _, phone := range phones {
		f1 := fsetScreen.Calculate(phone.Screen)
		f2 := fsetBattery.Calculate(phone.Battery)
		f3 := fsetWeight.Calculate(phone.Weight)
		f4 := fsetRAM.Calculate(phone.RAM)
		f5 := fsetPrice.Calculate(phone.PricePLN)
		f6 := fsetCamBack.Calculate(phone.CamBack)
		f7 := fsetCamFront.Calculate(phone.CamFront)
		phone.Value = fuzzy.Agregate(f1, f2, f3, f4, f5, f6, f7)
	}

	// posortowanie telefonów
	switch data.SortingMethod {
	case 1: // według dopasowania
		sort.Slice(phones, func(a, b int) bool {
			return phones[a].Value > phones[b].Value
		})
	case 2: // według ceny
		sort.Slice(phones, func(a, b int) bool {
			return phones[a].PricePLN > phones[b].PricePLN
		})
	case 3: // według nazwy telefonu
		sort.Slice(phones, func(a, b int) bool {
			nameA := strings.ToLower(strings.TrimSpace(phones[a].Company + " " + phones[a].Model))
			nameB := strings.ToLower(strings.TrimSpace(phones[b].Company + " " + phones[b].Model))
			if nameA == nameB {
				return phones[a].Value > phones[b].Value
			}
			return nameA < nameB
		})
	case 4: // dopasowanie 
		sort.Slice(phones, func(a, b int) bool {
			scoreA := 0.0
			scoreB := 0.0
			if phones[a].PricePLN > 0 {
				scoreA = 1000.0 * phones[a].Value / phones[a].PricePLN
			}
			if phones[b].PricePLN > 0 {
				scoreB = 1000.0 * phones[b].Value / phones[b].PricePLN
			}
			if scoreA == scoreB {
				return phones[a].Value > phones[b].Value
			}
			return scoreA > scoreB
		})
	}

	// zamiana wyników na JSON i zwrócenie
	phdata, err := json.Marshal(phones)
	if err != nil {
		http.Error(w, "json parse error", http.StatusInternalServerError)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	w.Write(phdata)
}

func StartServer() {
	phones = LoadData()
	fs := http.FileServer(http.Dir("./files"))
	http.Handle("/files/", http.StripPrefix("/files/", fs))
	http.HandleFunc("/", indexFunc)
	http.HandleFunc("/search/{query}", searchFunc)
	fmt.Println("Serwer startuje na: http://localhost:8090/")
	http.ListenAndServe("localhost:8090", nil)
}
