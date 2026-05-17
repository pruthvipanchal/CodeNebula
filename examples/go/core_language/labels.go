// Compile: go run labels.go
// Output:
//   found 4 at [1][1]
//   goto loop: 0 1 2
package main

import "fmt"

func main() {
	grid := [][]int{{1, 2}, {3, 4}, {5, 6}}
	target := 4

	// Labeled break exits BOTH loops at once
Outer:
	for i, row := range grid {
		for j, v := range row {
			if v == target {
				fmt.Printf("found %d at [%d][%d]\n", v, i, j)
				break Outer
			}
		}
	}

	// goto jumps to a label in the same function
	fmt.Print("goto loop:")
	i := 0
loop:
	if i < 3 {
		fmt.Print(" ", i)
		i++
		goto loop
	}
	fmt.Println()
}
