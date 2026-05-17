// Compile: go run sort_pkg.go
// Output:
//   sorted ints: [1 1 3 4 5 9]
//   by age: [{Al 25} {Bob 30}]
//   slices.Sort: [1 1 3 4 5 9]
package main

import (
	"fmt"
	"slices"
	"sort"
)

type Person struct {
	Name string
	Age  int
}

func main() {
	nums := []int{3, 1, 4, 1, 5, 9}
	sort.Ints(nums)
	fmt.Println("sorted ints:", nums)

	people := []Person{{"Bob", 30}, {"Al", 25}}
	sort.Slice(people, func(i, j int) bool {
		return people[i].Age < people[j].Age
	})
	fmt.Println("by age:", people)

	// Modern generic API (Go 1.21+)
	more := []int{9, 5, 1, 4, 1, 3}
	slices.Sort(more)
	fmt.Println("slices.Sort:", more)
}
