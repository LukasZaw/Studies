package main

import (
	"bufio"
	"fmt"
	"io"
	"os"
)

var x int = 10
var s string = "tekst"
var y = 20

var a [3]int = [3]int{1, 2, 3}

func add(a int, b int) int {
    return a + b
}

func div(a, b int) (int, bool) {
    if b == 0 {
        return 0, false
    }
    return a / b, true
}

type User struct {
    Name string
    Age  int
}

func (u User) IsAdult() bool {
    return u.Age >= 18
}
func (u *User) Birthday() { u.Age++ }

type Stringer interface {
    String() string
}
type Person struct{ Name string }
func (p Person) String() string { return p.Name }

func readIntsSimple(path string) ([]int, int, error) {
    f, err := os.Open(path)
    if err != nil {
        return nil, 0, err
    }
    defer f.Close()

    in := bufio.NewReader(f)

    var nums []int
    sum := 0

    for {
        var n int
        _, err := fmt.Fscan(in, &n)
        if err == io.EOF {
            break
        }
        if err != nil {
            return nil, 0, err
        }
        nums = append(nums, n)
        sum += n
    }

    return nums, sum, nil
}

func main() {
    fmt.Println("Hello, Go!")
	fmt.Println(add(2,y))

	result, ok := div(10, 2)
	if ok {
		fmt.Println("Result:", result)
	} else {
		fmt.Println("Division by zero!")
	}
	s := []int{1, 2, 3}
	s = append(s, 4)
	sub := s[1:3]
	fmt.Println(len(s))
	fmt.Printf("%d\n", cap(s))
	fmt.Println(s, sub)
	ss := make([]int, 0, 10)
	fmt.Println(ss)

	//mapy
	m := map[string]int{"a": 1}
	m["b"] = 2

	v, ok := m["b"]
	if ok {
		fmt.Println(v)
	} else {
		fmt.Println("Key not found")
	}

	//struktury i metody
	user := User{Name: "Alice", Age: 20}
	if user.IsAdult() {
		fmt.Println(user.Name, "is an adult.")
	} else {
		fmt.Println(user.Name, "is not an adult.")
	}
	user.Birthday()
	fmt.Println("After birthday, age is:", user.Age)

	//interfejsy
	var str Stringer = Person{Name: "Bob"}
	fmt.Println("Person name:", str.String())

	//wskaźniki
	num := 42
	ptr := &num
	fmt.Println("Value:", *ptr)
	*ptr = 100
	fmt.Println("Updated Value:", num)

	//error handling
	file, err := os.Open("nonexistent.txt")
	if err != nil {
		fmt.Println("Error opening file:", err)
	} else {
		defer file.Close()
		fmt.Println("File opened successfully")
	}

	//file reading
	nums, sum, err := readIntsSimple("numbers.txt")
    if err != nil {
        fmt.Println("Błąd:", err)
        return
    }
    fmt.Println("Wczytane:", nums)
    fmt.Println("Suma:", sum)
}