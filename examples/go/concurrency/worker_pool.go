// Compile: go run worker_pool.go
// Output:
//   sum of squares 1..9: 285
package main

import (
	"fmt"
	"sync"
)

func main() {
	const numWorkers = 3
	tasks := make(chan int, 9)
	results := make(chan int, 9)

	// Fixed pool of workers
	var wg sync.WaitGroup
	for i := 0; i < numWorkers; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for n := range tasks {
				results <- n * n
			}
		}()
	}

	// Submit work
	for n := 1; n <= 9; n++ {
		tasks <- n
	}
	close(tasks)

	// Close results once all workers finish
	go func() { wg.Wait(); close(results) }()

	sum := 0
	for r := range results {
		sum += r
	}
	fmt.Println("sum of squares 1..9:", sum)
}
