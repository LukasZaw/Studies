package main

import (
	"fmt"
	"html/template"
	"log"
	"net/http"
	"strconv"
	"strings"

	"lab6/db"
	"lab6/dbase"
)

var beerTmpl = template.Must(template.New("beer").Parse(`
<!doctype html>
<html>
	<head><meta charset="utf-8"><title>Piwa</title></head>
	<body>
		<h1>{{.Beer.Name}}</h1>

		<h2>Losowe piwa z tej samej grupy (grpA)</h2>
		<ul>
			{{range .RelatedA}}
			<li><a href="/beer/{{.Id}}">{{.Name}}</a></li>
			{{end}}
		</ul>

		<h2>Losowe piwa z tej samej grupy (grpB)</h2>
		<ul style="background:#95a9c4">
			{{range .RelatedB}}
			<li><a href="/beer/{{.Id}}">{{.Name}} </a></li>
			{{end}}
		</ul>

	</body>
</html>
`))

func beerHandler(w http.ResponseWriter, r *http.Request) {
    // /beer/{id}
    idStr := strings.TrimPrefix(r.URL.Path, "/beer/")
    id, err := strconv.Atoi(idStr)
    if err != nil || id <= 0 {
        http.NotFound(w, r)
        return
    }

    beer := dbase.GetBeer(id)
    if beer == nil || beer.Id == 0 {
        http.NotFound(w, r)
        return
    }

    var grupaA int
    err = db.QueryRow("SELECT grupa FROM grpa WHERE id = ? LIMIT 1;", id).Scan(&grupaA)
    if err != nil {
        log.Println("brak grupy w grpa lub błąd:", err)
        grupaA = -1
    }

    var grupaB int
    err = db.QueryRow("SELECT grupa FROM grpb WHERE id = ? LIMIT 1;", id).Scan(&grupaB)
    if err != nil {
        log.Println("brak grupy w grpb lub błąd:", err)
        grupaB = -1
    }

    relatedA := []*dbase.Beer{}
    if grupaA != -1 {
        relatedA = dbase.GetBeersFromGroup(grupaA, 10)
    }

    relatedB := []*dbase.Beer{}
    if grupaB != -1 {
        relatedB = dbase.GetBeersFromGroupB(grupaB, 10)
    }

    data := struct {
        Beer     *dbase.Beer
        RelatedA []*dbase.Beer
        RelatedB []*dbase.Beer
    }{
        Beer:     beer,
        RelatedA: relatedA,
        RelatedB: relatedB,
    }

    if err := beerTmpl.Execute(w, data); err != nil {
        http.Error(w, "template error", http.StatusInternalServerError)
    }
}

func main() {
	// beers := dbase.GetBeersAll()
	// for i := range beers {
	// 	beer := beers[i]
	// 	fmt.Println(i, beer.Id, beer.Name, beer.Rateavg)
	// }

	// kmeans := kmeans.Kmeans(beers, 20)
	// for i := range kmeans {
	// 	cluster := kmeans[i]
	// 	fmt.Println("Klaster", cluster.Grupa)
	// 	fmt.Println(" Liczba piw w klastrze:", len(cluster.GetBeers()))
	

	// 	for _, beer := range cluster.GetBeers() {
	// 		_, err := db.Exec("INSERT INTO grpb VALUES(?, ?)", beer.Id, cluster.Grupa)
	// 		if err != nil {
	// 			fmt.Println("Błąd INSERT do grpb:", err)
	// 		}
	// 	}
	// }


    http.HandleFunc("/beer/", beerHandler)

    fmt.Println("Serwer uruchomiony na http://localhost:8080")
    log.Fatal(http.ListenAndServe(":8080", nil))
}
