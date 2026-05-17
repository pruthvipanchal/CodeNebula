// Compile: go run pipelines.go
// Output:
//   4
//   9
//   16
package main

import "fmt"

// Stage 1: emit numbers
func generate(nums ...int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for _, n := range nums {
			out <- n
		}
	}()
	return out
}

// Stage 2: square each number
func square(in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for n := range in {
			out <- n * n
		}
	}()
	return out
}

func main() {
	// Wire stages together: generate -> square
	for n := range square(generate(2, 3, 4)) {
		fmt.Println(n)
	}
}
