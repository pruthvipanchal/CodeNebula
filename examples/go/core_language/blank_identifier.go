// Compile: go run blank_identifier.go
// Output:
//   values: 10 20 30
//   wrote bytes, ignored count
//   MyWriter satisfies io.Writer at compile time
package main

import (
	"fmt"
	"io"
)

type MyWriter struct{}

func (MyWriter) Write(p []byte) (int, error) { return len(p), nil }

// Compile-time interface satisfaction check — discards the value
var _ io.Writer = (*MyWriter)(nil)

func main() {
	// Discard the index in a range loop
	for _, v := range []int{10, 20, 30} {
		fmt.Print(" ", v)
	}
	fmt.Println()
	fmt.Println("values: 10 20 30")

	// Discard one of multiple return values
	_, err := fmt.Fprint(io.Discard, "data")
	if err == nil {
		fmt.Println("wrote bytes, ignored count")
	}

	fmt.Println("MyWriter satisfies io.Writer at compile time")
}
