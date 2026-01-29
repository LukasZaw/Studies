package main

import (
	"encoding/json"
	"html/template"
	"log"
	"net/http"
	"strconv"
)

type Item struct {
    ID    int     `json:"id"`
    Name  string  `json:"name"`
    Price float64 `json:"price"`
}

var items = []Item{
    {ID: 1, Name: "Apple", Price: 2.50},
    {ID: 2, Name: "Bread", Price: 5.20},
    {ID: 3, Name: "Milk", Price: 4.10},
}

// ParseFiles: ścieżki względem katalogu uruchomienia programu
var tpl = template.Must(template.ParseFiles(
    "templates/list.html",
    "templates/detail.html",
))

func main() {
    mux := http.NewServeMux()

    // JSON API
    mux.HandleFunc("/api/items", apiItemsHandler)

    // HTML views (templates)
    mux.HandleFunc("/items", htmlItemsHandler)

    log.Println("Listening on http://localhost:8080")
    log.Fatal(http.ListenAndServe(":8080", mux))
}

// GET /api/items
// GET /api/items?id=2
func apiItemsHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method != http.MethodGet {
        http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
        return
    }

    w.Header().Set("Content-Type", "application/json; charset=utf-8")

    idStr := r.URL.Query().Get("id")
    if idStr == "" {
        _ = json.NewEncoder(w).Encode(items)
        return
    }

    id, err := strconv.Atoi(idStr)
    if err != nil {
        http.Error(w, "id must be an integer", http.StatusBadRequest)
        return
    }

    item, ok := findItemByID(id)
    if !ok {
        http.Error(w, "item not found", http.StatusNotFound)
        return
    }

    _ = json.NewEncoder(w).Encode(item)
}

// GET /items
// GET /items?id=2
func htmlItemsHandler(w http.ResponseWriter, r *http.Request) {
    if r.Method != http.MethodGet {
        http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
        return
    }

    idStr := r.URL.Query().Get("id")
    w.Header().Set("Content-Type", "text/html; charset=utf-8")

    if idStr == "" {
        _ = tpl.ExecuteTemplate(w, "list.html", items)
        return
    }

    id, err := strconv.Atoi(idStr)
    if err != nil {
        http.Error(w, "id must be an integer", http.StatusBadRequest)
        return
    }

    item, ok := findItemByID(id)
    if !ok {
        http.Error(w, "item not found", http.StatusNotFound)
        return
    }

    _ = tpl.ExecuteTemplate(w, "detail.html", item)
}

func findItemByID(id int) (Item, bool) {
    for _, it := range items {
        if it.ID == id {
            return it, true
        }
    }
    return Item{}, false
}