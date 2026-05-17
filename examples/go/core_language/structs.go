// Compile: go run structs.go
// Output:
//   distance: 5
//   scaled: {6 8}
package main

import (
	"fmt"
	"math"
)

type Point struct {
	X, Y float64
}

// Value receiver — reads state
func (p Point) Distance() float64 {
	return math.Sqrt(p.X*p.X + p.Y*p.Y)
}

// Pointer receiver — mutates state
func (p *Point) Scale(factor float64) {
	p.X *= factor
	p.Y *= factor
}

func main() {
	p := Point{X: 3, Y: 4}
	fmt.Printf("distance: %g\n", p.Distance())

	p.Scale(2)
	fmt.Printf("scaled: %v\n", p)
}
