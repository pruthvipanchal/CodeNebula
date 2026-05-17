// Compile: go run interfaces.go
// Output:
//   36.6°C
//   -273.1°C
package main

import "fmt"

type Stringer interface {
	String() string
}

type Temperature struct {
	Celsius float64
}

func (t Temperature) String() string {
	return fmt.Sprintf("%.1f°C", t.Celsius)
}

func Print(s Stringer) {
	fmt.Println(s.String())
}

func main() {
	Print(Temperature{36.6})
	Print(Temperature{-273.15})
}
