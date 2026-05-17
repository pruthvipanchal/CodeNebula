// Compile: go run variables.go
// Output:
//   42 Go 3.14 true 0
package main

import "fmt"

func main() {
	x := 42
	name := "Go"
	ratio := 3.14
	active := true

	var count int    // zero value: 0
	var label string // zero value: ""

	fmt.Println(x, name, ratio, active, count)
	_ = label
}
