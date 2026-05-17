// Compile: go run race_detector.go
// Detect races: go run -race race_detector.go
// Output:
//   final count: 100
//
// The racy version is shown in raceyIncrement (commented call). The
// synchronized version below uses atomic.Int64 and is race-free — the
// race detector (-race) reports nothing for it.
package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

// raceyIncrement has a data race: 100 goroutines write `counter`
// with no synchronization. `go run -race` flags it.
func raceyIncrement() {
	var counter int
	var wg sync.WaitGroup
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func() { defer wg.Done(); counter++ }() // RACE
	}
	wg.Wait()
	_ = counter
}

// safeIncrement is the fix: atomic operations are race-free.
func safeIncrement() int64 {
	var counter atomic.Int64
	var wg sync.WaitGroup
	for i := 0; i < 100; i++ {
		wg.Add(1)
		go func() { defer wg.Done(); counter.Add(1) }()
	}
	wg.Wait()
	return counter.Load()
}

func main() {
	// raceyIncrement() // uncomment and run with -race to see the report
	fmt.Println("final count:", safeIncrement())
}
