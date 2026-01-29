package main

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type ApiResponse struct {
	Message string `json:"message"`
	Name    string `json:"name"`
}

func main() {
	// HTML

	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/html; charset=utf-8")
		 name := r.URL.Query().Get("name")
        if name == "" {
            name = "World"
        }

        fmt.Fprintf(w, "<h1>Hello %s</h1>", name)
        fmt.Fprintln(w, "<p>To jest odpowiedź HTML.</p>")
        fmt.Fprintln(w, "<p>JSON: <a href='/api?name=Ala'>/api?name=Ala</a></p>")
	})

	http.HandleFunc("/api", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Set("Content-Type", "application/json; charset=utf-8")

        name := r.URL.Query().Get("name")
        if name == "" {
            name = "World"
        }

        resp := ApiResponse{
            Message: "Hello from JSON",
            Name:    name,
        }

        _ = json.NewEncoder(w).Encode(resp)
    })


	 fmt.Println("Start: http://localhost:8080")
    _ = http.ListenAndServe(":8080", nil)
}