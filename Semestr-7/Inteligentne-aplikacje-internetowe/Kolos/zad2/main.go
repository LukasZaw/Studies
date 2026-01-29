package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"time"
)

type Message struct {
	Message string `json:"text"`
	Time string `json:"time"`
}

type CreateUserRequest struct {
	Name string `json:"name"`
	Age  int    `json:"age"`
}

type User struct {
	ID   int    `json:"id"`
	Name string `json:"name"`
	Age  int    `json:"age"`
}

func main1() {
	mux := http.NewServeMux()

	//simple message endpoint
	mux.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
		if r.Method != http.MethodGet {
            http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
            return
        }
        w.Header().Set("Content-Type", "text/plain; charset=utf-8")
        fmt.Fprintln(w, "OK")
	})

	


	//hello endpoint
	mux.HandleFunc("/api/hello", func(w http.ResponseWriter, r *http.Request) {
        if r.Method != http.MethodGet {
            http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
            return
        }

        // Query param: /api/hello?name=Ania
        name := r.URL.Query().Get("name")
        if name == "" {
            name = "world"
        }

        resp := Message{
            Message: "Hello, " + name,
            Time:    time.Now().Format(time.RFC3339),
        }

        w.Header().Set("Content-Type", "application/json; charset=utf-8")
        json.NewEncoder(w).Encode(resp)
    })

	//post json
	mux.HandleFunc("/api/users", func(w http.ResponseWriter, r *http.Request) {
        if r.Method != http.MethodPost {
            http.Error(w, "method not allowed", http.StatusMethodNotAllowed)
            return
        }

        var req CreateUserRequest
        if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
            http.Error(w, "invalid json", http.StatusBadRequest)
            return
        }
        if req.Name == "" || req.Age <= 0 {
            http.Error(w, "invalid input", http.StatusBadRequest)
            return
        }

        // Na kolokwium często wystarczy „na sztywno”/w pamięci:
        created := User{
            ID:   1,
            Name: req.Name,
            Age:  req.Age,
        }

        w.Header().Set("Content-Type", "application/json; charset=utf-8")
        w.WriteHeader(http.StatusCreated)
        json.NewEncoder(w).Encode(created)
    })


	//Start server
	addr := ":8080"
    log.Printf("Listening on http://localhost%s", addr)
    http.ListenAndServe(addr, logRequests(mux))
}



func logRequests(next http.Handler) http.Handler {
    return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
        start := time.Now()
        next.ServeHTTP(w, r)
        log.Printf("%s %s (%s)", r.Method, r.URL.Path, time.Since(start))
    })
}