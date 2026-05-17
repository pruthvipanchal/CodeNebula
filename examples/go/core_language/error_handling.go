// Compile: go run error_handling.go
// Output:
//   found: Alice
//   findUser -1: findUser: invalid id -1
//   is not-found: true
package main

import (
	"errors"
	"fmt"
)

var ErrNotFound = errors.New("not found")

type User struct{ Name string }

var store = map[int]*User{1: {Name: "Alice"}}

func findUser(id int) (*User, error) {
	if id <= 0 {
		return nil, fmt.Errorf("findUser: invalid id %d", id)
	}
	user, ok := store[id]
	if !ok {
		return nil, fmt.Errorf("findUser %d: %w", id, ErrNotFound)
	}
	return user, nil
}

func main() {
	user, err := findUser(1)
	if err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Println("found:", user.Name)
	}

	_, err = findUser(-1)
	fmt.Println(err)

	_, err = findUser(99)
	fmt.Println("is not-found:", errors.Is(err, ErrNotFound))
}
