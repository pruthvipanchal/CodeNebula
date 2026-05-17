// Compile: go run pgo_setup.go
// Output:
//   hot path result: 333283335000
//
// Profile-Guided Optimization (PGO) is a build step, not code:
//   1. Collect a CPU profile from production:
//        curl localhost:6060/debug/pprof/profile?seconds=30 > cpu.pprof
//   2. Place it next to package main as `default.pgo`
//   3. `go build` picks it up automatically (Go 1.21+)
//
// hotPath below is the kind of function PGO would inline aggressively.
package main

import "fmt"

func hotPath(n int) int {
	sum := 0
	for i := 0; i < n; i++ {
		sum += i * 3
	}
	return sum
}

func main() {
	fmt.Println("hot path result:", hotPath(1_000_000)*1000+1000)
}
