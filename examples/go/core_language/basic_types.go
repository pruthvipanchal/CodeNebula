// Compile: go run basic_types.go
// Output:
//   int: 100
//   uint32: 4294967295
//   float64: 3.141592653589793
//   byte: 255
//   rune: 128640 (🚀)
//   string: Hello, 世界
//   bool: true
package main

import "fmt"

func main() {
	var i int = 100
	var u uint32 = 4294967295
	var f float64 = 3.141592653589793
	var b byte = 255
	var r rune = '🚀'
	var s string = "Hello, 世界"
	var ok bool = true

	fmt.Println("int:", i)
	fmt.Println("uint32:", u)
	fmt.Println("float64:", f)
	fmt.Println("byte:", b)
	fmt.Printf("rune: %d (%c)\n", r, r)
	fmt.Println("string:", s)
	fmt.Println("bool:", ok)
}
