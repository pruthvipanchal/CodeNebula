// Compile: go run panic_recover.go
// Output:
//   10 / 2 = 5, err=<nil>
//   10 / 0 = 0, err=recovered: runtime error: integer divide by zero
//   program continues normally
package main

import "fmt"

func safeDivide(a, b int) (result int, err error) {
	defer func() {
		if r := recover(); r != nil {
			err = fmt.Errorf("recovered: %v", r)
		}
	}()
	result = a / b // panics when b == 0
	return result, nil
}

func main() {
	r1, err1 := safeDivide(10, 2)
	fmt.Printf("10 / 2 = %d, err=%v\n", r1, err1)

	r2, err2 := safeDivide(10, 0)
	fmt.Printf("10 / 0 = %d, err=%v\n", r2, err2)

	fmt.Println("program continues normally")
}
