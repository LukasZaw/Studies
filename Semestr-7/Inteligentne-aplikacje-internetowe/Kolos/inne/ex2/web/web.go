package web

import (
	"encoding/json"
	"fmt"
	"html/template"
	"kolos/kod"
	"net/http"
	"strconv"
)

func AparatList(w http.ResponseWriter, r *http.Request) {
	// Pobranie danych
	data := kod.ListaApartow()

	// Parsowanie szablonu
	tmpl, err := template.ParseFiles("pages/aparat.html")
	if err != nil {
		http.Error(w, "Błąd szablonu", http.StatusInternalServerError)
		return
	}
	// Wysłanie danych do HTML
	tmpl.Execute(w, data)
}

func AparatByID(w http.ResponseWriter, r *http.Request)  {
	id := r.URL.Path[len("/aparat1/"):]
	index, _ := strconv.Atoi(id)
	data := kod.ListaApartowBiID(index) 
	json.NewEncoder(w).Encode(data) 

}

func StartServer() {
	http.HandleFunc("/aparat", AparatList)
	http.HandleFunc("/aparat1/", AparatByID)
	fmt.Println("Serwer: http://localhost:8080")
	http.ListenAndServe(":8080", nil)
}