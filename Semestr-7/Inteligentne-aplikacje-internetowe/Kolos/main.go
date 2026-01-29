package main

import (
	"encoding/json"
	"fmt"
	"html/template"
	"math"
	"net/http"
	"sort"
	"strconv"
)

// --- CZĘŚĆ 1: Struktury i Podstawy ---

// Zadanie 1: Utwórz strukturę Aparat
// Zadanie 6: Dodaj pole na ocenę użytkownika
type Aparat struct {
	Nazwa          string  `json:"nazwa"`
	Megapiksele    float64 `json:"megapiksele"`
	RozmiarMatrycy float64 `json:"rozmiar_matrycy"`
	ZoomOptyczny   float64 `json:"zoom_optyczny"`
	Ocena          float64 `json:"ocena"` // Pole dodane w ramach Zadania 6
}

// Globalny slice przechowujący aparaty (baza danych w pamięci)
var aparaty []Aparat

func init() {
	// Zadanie 1: Utwórz slice zawierający 5 obiektów
	aparaty = []Aparat{
		{"Canon EOS", 24.1, 22.3, 1.0, 4.5},
		{"Nikon D3500", 24.2, 23.5, 1.0, 4.7},
		{"Sony Alpha", 33.0, 35.0, 1.0, 4.9},
		{"Compact Zoom", 16.0, 6.2, 20.0, 3.5},
		{"Super Zoom", 20.0, 6.2, 50.0, 4.0},
	}
}

// Zadanie 2: Funkcja zwracająca różnicę między dwoma aparatami
// Wzór zinterpretowany z treści: 50*|diff_mega| + 10*|diff_mat| + 10*|diff_zoom|
func obliczRoznice(apA, apB Aparat) float64 {
	diffMega := math.Abs(apA.Megapiksele - apB.Megapiksele)
	diffMat := math.Abs(apA.RozmiarMatrycy - apB.RozmiarMatrycy)
	diffZoom := math.Abs(apA.ZoomOptyczny - apB.ZoomOptyczny)

	return 50*diffMega + 10*diffMat + 10*diffZoom
}

// --- CZĘŚĆ 3: Sztuczna Inteligencja (logika rozmyta i k-NN) ---
// Umieszczam to tutaj, aby struktury były widoczne dla main()

// Kod dostarczony w treści zadania
type fuzzy struct {
	x, o float64
}

// Zadanie 5: Metoda calc.
// UWAGA: W treści zadania podano wzór Exp((x-f.x)^2 / f.o).
// Dla f.o > 0 funkcja ta rośnie do nieskończoności. Aby była to funkcja przynależności (zbiór rozmyty, dzwonowa),
// powinna mieć minus w wykładniku: Exp(-(...)). Dodałem minus, aby zadanie miało sens matematyczny.
func (f *fuzzy) calc(x float64) float64 {
	return math.Exp(-((x - f.x) * (x - f.x) / f.o))
}

// Definicje zbiorów rozmytych z zadania
var f1, f2, f3 = fuzzy{15, 8}, fuzzy{3, 6}, fuzzy{10, 10}

// Zadanie 5 cd.: Znalezienie aparatu z największą aktywacją
func znajdzNajlepszyFuzzy(lista []Aparat) (Aparat, float64) {
	var bestAparat Aparat
	maxAktywacja := -1.0

	for _, ap := range lista {
		// Aktywacja policzona jako iloczyn trzech wartości rozmytych
		act1 := f1.calc(ap.Megapiksele)
		act2 := f2.calc(ap.RozmiarMatrycy)
		act3 := f3.calc(ap.ZoomOptyczny)

		totalActivation := act1 * act2 * act3

		if totalActivation > maxAktywacja {
			maxAktywacja = totalActivation
			bestAparat = ap
		}
	}
	return bestAparat, maxAktywacja
}

// Zadanie 6: Aproksymacja oceny metodą k-NN (k-Najbliższych Sąsiadów)
func przewidzOceneKNN(cel Aparat, k int, baza []Aparat) float64 {
	// Struktura pomocnicza do sortowania
	type neighbour struct {
		dist  float64
		ocena float64
	}

	neighbours := make([]neighbour, len(baza))

	// 1. Oblicz odległości do wszystkich znanych aparatów
	for i, ap := range baza {
		dist := obliczRoznice(cel, ap) // Wykorzystujemy funkcję z Zadania 2 jako metrykę odległości
		neighbours[i] = neighbour{dist: dist, ocena: ap.Ocena}
	}

	// 2. Posortuj rosnąco po odległości
	sort.Slice(neighbours, func(i, j int) bool {
		return neighbours[i].dist < neighbours[j].dist
	})

	// 3. Wyciągnij średnią z k najbliższych
	if k > len(neighbours) {
		k = len(neighbours)
	}

	sumaOcen := 0.0
	for i := 0; i < k; i++ {
		sumaOcen += neighbours[i].ocena
	}

	return sumaOcen / float64(k)
}

// --- CZĘŚĆ 2: Serwer HTTP ---

// Zadanie 3: Wyświetlanie listy aparatów (HTML)
func handleList(w http.ResponseWriter, r *http.Request) {
	// Prosty szablon HTML wbudowany w kod
	const tpl = `
	<!DOCTYPE html>
	<html>
	<head><title>Lista Aparatów</title></head>
	<body>
		<h1>Dostępne Aparaty</h1>
		<ul>
			{{range $index, $element := .}}
				<li>
					<strong>{{$element.Nazwa}}</strong> 
					(MP: {{$element.Megapiksele}}, Matryca: {{$element.RozmiarMatrycy}}, Zoom: {{$element.ZoomOptyczny}}, Ocena: {{$element.Ocena}})
					- <a href="/aparat?id={{$index}}">Szczegóły JSON</a>
				</li>
			{{end}}
		</ul>
	</body>
	</html>`

	t, err := template.New("webpage").Parse(tpl)
	if err != nil {
		http.Error(w, "Błąd szablonu", http.StatusInternalServerError)
		return
	}

	t.Execute(w, aparaty)
}

// Zadanie 4: Zwracanie informacji o aparacie (JSON) po indeksie
func handleAparat(w http.ResponseWriter, r *http.Request) {
	// Pobierz parametr "id" z adresu URL (np. /aparat?id=1)
	ids, ok := r.URL.Query()["id"]

	if !ok || len(ids[0]) < 1 {
		http.Error(w, "Brak parametru id", http.StatusBadRequest)
		return
	}

	index, err := strconv.Atoi(ids[0])
	if err != nil || index < 0 || index >= len(aparaty) {
		http.Error(w, "Niepoprawny indeks", http.StatusBadRequest)
		return
	}

	// Ustaw nagłówek JSON
	w.Header().Set("Content-Type", "application/json")

	// Zwróć obiekt w formacie JSON
	json.NewEncoder(w).Encode(aparaty[index])
}

func main() {
	fmt.Println("Start aplikacji...")

	// --- DEMO ZADANIA 5 (Fuzzy) ---
	fmt.Println("--- Zadanie 5: Fuzzy Logic ---")
	bestFuzzy, score := znajdzNajlepszyFuzzy(aparaty)
	fmt.Printf("Aparat z największą aktywacją: %s (Wynik: %.5f)\n", bestFuzzy.Nazwa, score)

	// --- DEMO ZADANIA 6 (k-NN) ---
	fmt.Println("\n--- Zadanie 6: Aproksymacja oceny (k-NN) ---")
	// Tworzymy nowy aparat bez oceny
	nowyAparat := Aparat{Nazwa: "Test Cam", Megapiksele: 25.0, RozmiarMatrycy: 24.0, ZoomOptyczny: 1.2}
	przewidzianaOcena := przewidzOceneKNN(nowyAparat, 3, aparaty) // k=3
	fmt.Printf("Dla aparatu %s (25MP, 24mm, 1.2x) przewidziana ocena to: %.2f\n", nowyAparat.Nazwa, przewidzianaOcena)

	// --- SERWER HTTP ---
	fmt.Println("\n--- Start serwera HTTP na porcie 8080 ---")
	fmt.Println("Wejdź na: http://localhost:8080/")

	http.HandleFunc("/", handleList)         // Zadanie 3
	http.HandleFunc("/aparat", handleAparat) // Zadanie 4

	// Uruchomienie serwera (blokuje działanie programu)
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		fmt.Println("Błąd serwera:", err)
	}
}
