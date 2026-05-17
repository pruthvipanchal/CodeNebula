// Compile: go run type_assertions.go
// Output:
//   string value: hello (ok=true)
//   int assertion ok: false
//   recovered from a failed assertion
package main

import "fmt"

func main() {
	var i any = "hello"

	// Safe two-value form — never panics
	s, ok := i.(string)
	fmt.Printf("string value: %s (ok=%t)\n", s, ok)

	_, ok = i.(int)
	fmt.Printf("int assertion ok: %t\n", ok)

	// Single-value form panics on mismatch — recover to keep running
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("recovered from a failed assertion")
		}
	}()
	_ = i.(int) // panics: interface conversion
}
