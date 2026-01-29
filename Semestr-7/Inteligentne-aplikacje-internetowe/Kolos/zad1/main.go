package main

import "fmt"

type Book struct {
	Title string
	Price float64
}

type User struct {
    Name string
    Age  int
}

func Oldest(users []User) (User, bool) {
	if len(users) == 0 {
		return User{}, false
	}
	oldest := users[0]
	for _, u := range users[1:] {
		if u.Age > oldest.Age {
			oldest = u
		}
	}
	return oldest, true
}

func NewBook(title string, price float64) Book {
	return Book{Title: title, Price: price}
}

func (b Book) Discount(per float64) float64 {
	return b.Price * (1 - per/100)
}

func main() {
	book := NewBook("Go Programming", 50.0)
	discountedPrice := book.Discount(10)
	fmt.Printf("Discount: %.2f\n", discountedPrice)

	users := []User{
        {Name: "Ala", Age: 20},
        {Name: "Ela", Age: 28},
        {Name: "Jan", Age: 25},
    }

    u, ok := Oldest(users)
    if ok {
        fmt.Println("Oldest:", u.Name, u.Age)
    }
}