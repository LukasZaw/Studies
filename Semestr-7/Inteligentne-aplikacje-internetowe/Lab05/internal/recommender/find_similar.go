package recommender

import (
	"Lab05/internal/api"
	"Lab05/internal/model"
	"fmt"
	"math"
)

func FindMostSimilar(userRef model.User) (*model.User, float64, error) {
	userCount, err := api.GetUserCount()
	if err != nil {
		return nil, 0, fmt.Errorf("błąd pobierania liczby użytkowników: %v", err)
	}

	var bestUser *model.User
	minDiff := math.Inf(1)

	for id := 0; id < userCount; id++ {
		if id == userRef.Id {
			continue
		}

		otherUser, err := api.GetUser(id)
		if err != nil {
			fmt.Printf(" Błąd pobierania użytkownika %d: %v\n", id, err)
			continue
		}

		diff := Difference(userRef, *otherUser)
		fmt.Printf("Użytkownik %d – różnica: %.4f\n", otherUser.Id, diff)

		if diff < minDiff {
			minDiff = diff
			bestUser = otherUser
		}
	}

	if bestUser == nil {
		return nil, 0, fmt.Errorf("nie znaleziono podobnych użytkowników")
	}

	return bestUser, minDiff, nil
}
