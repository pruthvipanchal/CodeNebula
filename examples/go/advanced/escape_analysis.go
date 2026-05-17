// Compile: go run escape_analysis.go
// Inspect decisions: go build -gcflags='-m' escape_analysis.go
// Output:
//   sumLocal = 6
//   counter = 7
//   adder: 1 3 6
//
// sumLocal's array stays on the stack. newCounter's int and adder's sum
// escape to the heap because their lifetimes outlive the function.
package main

import "fmt"

// Does not escape — the array lives on the stack.
func sumLocal() int {
	x := [3]int{1, 2, 3}
	return x[0] + x[1] + x[2]
}

// Escapes — &n is returned, so n moves to the heap.
func newCounter() *int {
	n := 0
	return &n
}

// Escapes — sum is captured by a closure that outlives adder.
func adder() func(int) int {
	sum := 0
	return func(x int) int { sum += x; return sum }
}

func main() {
	fmt.Println("sumLocal =", sumLocal())

	c := newCounter()
	*c = 7
	fmt.Println("counter =", *c)

	add := adder()
	fmt.Println("adder:", add(1), add(2), add(3))
}
