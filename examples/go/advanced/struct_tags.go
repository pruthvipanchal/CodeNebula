// Compile: go run struct_tags.go
// Output:
//   Name json tag: name
//   Name db tag: user_name
//   Name validate tag: required,min=2
//   xml tag present: false
//   JSON: {"id":1,"name":"Alice"}
package main

import (
	"encoding/json"
	"fmt"
	"reflect"
)

type User struct {
	ID    int    `json:"id" db:"user_id"`
	Name  string `json:"name" db:"user_name" validate:"required,min=2"`
	Email string `json:"email,omitempty" db:"email" validate:"email"`
}

func main() {
	t := reflect.TypeOf(User{})
	name, _ := t.FieldByName("Name")

	fmt.Println("Name json tag:", name.Tag.Get("json"))
	fmt.Println("Name db tag:", name.Tag.Get("db"))
	fmt.Println("Name validate tag:", name.Tag.Get("validate"))

	// Lookup distinguishes "absent" from "empty"
	_, ok := name.Tag.Lookup("xml")
	fmt.Println("xml tag present:", ok)

	// Tags drive json serialization — Email is empty so omitempty drops it
	data, _ := json.Marshal(User{ID: 1, Name: "Alice"})
	fmt.Println("JSON:", string(data))
}
