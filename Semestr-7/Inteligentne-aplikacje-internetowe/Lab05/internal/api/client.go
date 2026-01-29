package api

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"

	"Lab05/internal/model"
)

const BaseURL = "http://172.16.15.101:8080/"

func GetUser(id int) (*model.User, error) {
	url := fmt.Sprintf("%s/user/%d", BaseURL, id)
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}

	var user model.User
	if err := json.Unmarshal(body, &user); err != nil {
		return nil, err
	}
	return &user, nil
}

func GetMovies() ([]model.Movie, error) {
	url := fmt.Sprintf("%s/movies/", BaseURL)
	resp, err := http.Get(url)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	body, err := io.ReadAll(resp.Body)
	if err != nil {
		return nil, err
	}

	var movies []model.Movie
	if err := json.Unmarshal(body, &movies); err != nil {
		return nil, err
	}
	return movies, nil
}

func GetUserCount() (int, error) {
	url := fmt.Sprintf("%s/usercount/", BaseURL)
	resp, err := http.Get(url)
	if err != nil {
		return 0, err
	}
	defer resp.Body.Close()

	var count int
	if err := json.NewDecoder(resp.Body).Decode(&count); err != nil {
		return 0, err
	}
	return count, nil
}
