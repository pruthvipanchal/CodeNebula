// Compile: go run embedding.go
// Output:
//   Rex barks
//   Rex makes a sound
//   breed: Labrador
package main

import "fmt"

type Animal struct {
	Name string
}

func (a Animal) Speak() string { return a.Name + " makes a sound" }

type Dog struct {
	Animal // embedded — Dog promotes Animal's fields and methods
	Breed  string
}

// Dog overrides Speak
func (d Dog) Speak() string { return d.Name + " barks" }

func main() {
	d := Dog{Animal: Animal{Name: "Rex"}, Breed: "Labrador"}
	fmt.Println(d.Speak())        // overridden method
	fmt.Println(d.Animal.Speak()) // embedded type still reachable
	fmt.Println("breed:", d.Breed)
}
