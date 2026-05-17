// Compile: go run waitgroup.go
// Output (order varies):
//   processed item-1
//   processed item-2
//   processed item-3
//   all done
package main

import (
	"fmt"
	"sync"
)

func process(item string) {
	fmt.Println("processed", item)
}

func main() {
	items := []string{"item-1", "item-2", "item-3"}

	var wg sync.WaitGroup
	for _, item := range items {
		wg.Add(1)
		go func(item string) {
			defer wg.Done()
			process(item)
		}(item)
	}

	wg.Wait() // blocks until every goroutine calls Done
	fmt.Println("all done")
}
