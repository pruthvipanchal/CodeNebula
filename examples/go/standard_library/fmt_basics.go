// Compile: go run fmt_basics.go
// Output:
//   {Alice 30}
//   {Name:Alice Age:30}
//   main.User{Name:"Alice", Age:30}
//   main.User
//   parsed: Bob 25
package main

import "fmt"

type User struct {
	Name string
	Age  int
}

func main() {
	u := User{"Alice", 30}

	fmt.Printf("%v\n", u)  // default
	fmt.Printf("%+v\n", u) // field names
	fmt.Printf("%#v\n", u) // Go syntax
	fmt.Printf("%T\n", u)  // type

	// Sscanf parses formatted input
	var name string
	var age int
	fmt.Sscanf("Bob 25", "%s %d", &name, &age)
	fmt.Printf("parsed: %s %d\n", name, age)
}
