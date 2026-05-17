// Compile: go run type_switches.go
// Output:
//   int: 42
//   string of length 5
//   bool: true
//   nil value
//   unknown type []int
package main

import "fmt"

func describe(i any) string {
	switch v := i.(type) {
	case int:
		return fmt.Sprintf("int: %d", v)
	case string:
		return fmt.Sprintf("string of length %d", len(v))
	case bool:
		return fmt.Sprintf("bool: %t", v)
	case nil:
		return "nil value"
	default:
		return fmt.Sprintf("unknown type %T", v)
	}
}

func main() {
	for _, v := range []any{42, "hello", true, nil, []int{1, 2}} {
		fmt.Println(describe(v))
	}
}
