// Compile: go run functions.go
// Output:
//   5 / 2 = 2.5
//   min=1 max=9
//   doubled: 8
package main

import "fmt"

func divide(a, b float64) (float64, error) {
	if b == 0 {
		return 0, fmt.Errorf("division by zero")
	}
	return a / b, nil
}

func minMax(nums []int) (min, max int) {
	min, max = nums[0], nums[0]
	for _, n := range nums[1:] {
		if n < min {
			min = n
		}
		if n > max {
			max = n
		}
	}
	return
}

func main() {
	result, err := divide(5, 2)
	if err != nil {
		fmt.Println("error:", err)
		return
	}
	fmt.Printf("5 / 2 = %.1f\n", result)

	min, max := minMax([]int{3, 1, 9, 4, 7})
	fmt.Printf("min=%d max=%d\n", min, max)

	double := func(x int) int { return x * 2 }
	fmt.Println("doubled:", double(4))
}
