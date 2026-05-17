// Compile: go run math_pkg.go
// Output:
//   sqrt(144) = 12
//   pow(2,10) = 1024
//   max(3,7) = 7
//   abs(-4.5) = 4.5
//   hypot(3,4) = 5
//   random in range: true
package main

import (
	"fmt"
	"math"
	"math/rand/v2"
)

func main() {
	fmt.Println("sqrt(144) =", math.Sqrt(144))
	fmt.Println("pow(2,10) =", math.Pow(2, 10))
	fmt.Println("max(3,7) =", math.Max(3, 7))
	fmt.Println("abs(-4.5) =", math.Abs(-4.5))
	fmt.Println("hypot(3,4) =", math.Hypot(3, 4))

	r := rand.IntN(100) // [0, 100)
	fmt.Println("random in range:", r >= 0 && r < 100)
}
