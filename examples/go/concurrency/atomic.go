// Compile: go run atomic.go
// Output:
//   total requests: 5000
//   flag acquired once: true
package main

import (
	"fmt"
	"sync"
	"sync/atomic"
)

func main() {
	var requests atomic.Int64

	var wg sync.WaitGroup
	for i := 0; i < 5000; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			requests.Add(1)
		}()
	}
	wg.Wait()
	fmt.Println("total requests:", requests.Load())

	// Compare-and-swap — only the first caller succeeds
	var flag atomic.Bool
	acquired := flag.CompareAndSwap(false, true)
	fmt.Println("flag acquired once:", acquired)
}
