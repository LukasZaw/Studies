package main

import (
	"fmt"
	"log"

	"Lab05/internal/api"
	"Lab05/internal/recommender"
)

func main() {
	user6, err := api.GetUser(6)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("Użytkownik: %s (ID: %d)\n", user6.Name, user6.Id)

 	// user7, err := api.GetUser(7)
    // if err != nil {
    //     log.Fatal(err)
    // }
    // diffTwo := recommender.Difference(*user6, *user7)
    // fmt.Printf("\nRóżnica między %s (ID:%d) a %s (ID:%d): %.4f\n", user6.Name, user6.Id, user7.Name, user7.Id, diffTwo)


	mostSimilar, diff, err := recommender.FindMostSimilar(*user6)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Printf("\nNajbardziej podobny użytkownik: %s (ID: %d)\n", mostSimilar.Name, mostSimilar.Id)
	fmt.Printf("Różnica: %.4f\n", diff)

	movies, _ := api.GetMovies()

	fmt.Printf("==== Wysoko ocenione %s:\n", mostSimilar.Name)
	for _, rate := range mostSimilar.Rates {
		if rate.Rate >= 9 {

			for _, m := range movies {
				if m.Id == rate.Movie {
					fmt.Printf("- %s | Ocena: %.1f | Gatunek: %s\n",
						m.Title, rate.Rate, m.Genre)
				}
			}
		}
	}
}
