// Compile: go run json_encode.go
// Output:
//   encoded: {"name":"Alice","age":30}
//   decoded: Alice (30)
//   with omitempty: {"name":"Bob","age":0}
package main

import (
	"encoding/json"
	"fmt"
)

type Person struct {
	Name     string `json:"name"`
	Age      int    `json:"age"`
	Email    string `json:"email,omitempty"`
	Password string `json:"-"`
}

func main() {
	p := Person{Name: "Alice", Age: 30, Password: "secret"}

	data, err := json.Marshal(p)
	if err != nil {
		panic(err)
	}
	fmt.Println("encoded:", string(data))

	var p2 Person
	if err := json.Unmarshal(data, &p2); err != nil {
		panic(err)
	}
	fmt.Printf("decoded: %s (%d)\n", p2.Name, p2.Age)
	fmt.Println("password hidden:", p2.Password == "")

	// omitempty: Age is zero, Email is empty — only name included
	p3 := Person{Name: "Bob"}
	data3, _ := json.Marshal(p3)
	fmt.Println("with omitempty:", string(data3))
}
