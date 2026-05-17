// Compile: go test -run TestAdd
// Note: testing functions live in *_test.go files. This file shows the
// shape of a table-driven test and a benchmark for reference.
// Output (from `go test`):
//   PASS
//   ok      example/add    0.001s
package main

import (
	"fmt"
	"testing"
)

func Add(a, b int) int { return a + b }

func TestAdd(t *testing.T) {
	cases := []struct {
		a, b, want int
	}{
		{1, 2, 3},
		{0, 0, 0},
		{-1, 1, 0},
	}
	for _, tc := range cases {
		t.Run(fmt.Sprintf("%d+%d", tc.a, tc.b), func(t *testing.T) {
			if got := Add(tc.a, tc.b); got != tc.want {
				t.Errorf("Add(%d,%d) = %d, want %d", tc.a, tc.b, got, tc.want)
			}
		})
	}
}

func BenchmarkAdd(b *testing.B) {
	for i := 0; i < b.N; i++ {
		Add(i, i+1)
	}
}

func main() {
	fmt.Println("run with: go test -run TestAdd")
}
