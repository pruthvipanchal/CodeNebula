// Compile: go run slices.go
// Output:
//   array: [1 2 3]
//   slice: [10 20 30 40]
//   sub:   [20 30]
//   len=4 cap>=4
package main

import "fmt"

func main() {
	// Array — fixed size, value type
	arr := [3]int{1, 2, 3}
	fmt.Println("array:", arr)

	// Slice — dynamic, grows with append
	s := []int{10, 20, 30}
	s = append(s, 40)
	fmt.Println("slice:", s)

	// Slicing shares the underlying array
	sub := s[1:3]
	fmt.Println("sub:  ", sub)

	fmt.Printf("len=%d cap>=%d\n", len(s), cap(s))
}
