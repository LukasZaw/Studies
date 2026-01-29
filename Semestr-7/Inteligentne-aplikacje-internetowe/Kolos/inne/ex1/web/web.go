package web

import (
	"fmt"
	"net/http"
)

func Start() {
	fmt.Println("Serwer is starting at: http://localhost:8090/")
	http.HandleFunc("/", indexFunc)
	http.HandleFunc("/export/{pts}/{cls}", exportFunc)
	http.ListenAndServe("localhost:8090", nil)
}
