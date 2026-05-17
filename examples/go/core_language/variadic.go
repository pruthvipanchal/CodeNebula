// Compile: go run variadic.go
// Output:
//   sum(1,2,3) = 6
//   sum() = 0
//   sum(nums...) = 15
package main

import "fmt"

func sum(nums ...int) int {
	total := 0
	for _, n := range nums {
		total += n
	}
	return total
}

func main() {
	fmt.Println("sum(1,2,3) =", sum(1, 2, 3))
	fmt.Println("sum() =", sum())

	nums := []int{4, 5, 6}
	fmt.Println("sum(nums...) =", sum(nums...)) // spread a slice
}
