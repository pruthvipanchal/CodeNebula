// Compile: go run named_types.go
// Output:
//   100C = 212F
//   0C = 32F
//   Byte alias holds: 255
package main

import "fmt"

// Distinct named types — not interchangeable without conversion
type Celsius float64
type Fahrenheit float64

func (c Celsius) ToF() Fahrenheit {
	return Fahrenheit(c*9/5 + 32)
}

// Type alias — Byte and uint8 are the SAME type
type Byte = uint8

func main() {
	var c Celsius = 100
	fmt.Printf("%gC = %gF\n", float64(c), float64(c.ToF()))

	c = 0
	fmt.Printf("%gC = %gF\n", float64(c), float64(c.ToF()))

	var b Byte = 255
	fmt.Println("Byte alias holds:", b)
}
