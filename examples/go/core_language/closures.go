// Compile: go run closures.go
// Output:
//   c: 1 2 3
//   d: 1
package main

import "fmt"

func makeCounter() func() int {
	n := 0
	return func() int {
		n++
		return n
	}
}

func main() {
	c := makeCounter()
	fmt.Println("c:", c(), c(), c())

	// Independent state per closure
	d := makeCounter()
	fmt.Println("d:", d())
}
