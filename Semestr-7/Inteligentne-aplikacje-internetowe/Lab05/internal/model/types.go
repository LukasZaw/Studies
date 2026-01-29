package model

type Rate struct {
	Movie int     `json:"movieid"`
	Rate  float64 `json:"rate"`
}

type User struct {
	Id    int    `json:"id"`
	Name  string `json:"name"`
	Rates []Rate `json:"rates"`
}

type Movie struct {
	Id       int    `json:"id"`
	Title    string `json:"title"`
	Oryginal string `json:"oryginal"`
	Year     int    `json:"year"`
	Genre    string `json:"genre"`
}
