// Compile: go run once.go
// Output:
//   initializing database (expensive)
//   instance id: 1
//   all 10 goroutines got the same instance: true
package main

import (
	"fmt"
	"sync"
)

type Database struct{ id int }

var (
	once     sync.Once
	instance *Database
)

func getDatabase() *Database {
	once.Do(func() {
		fmt.Println("initializing database (expensive)")
		instance = &Database{id: 1}
	})
	return instance
}

func main() {
	results := make([]*Database, 10)

	var wg sync.WaitGroup
	for i := 0; i < 10; i++ {
		wg.Add(1)
		go func(idx int) {
			defer wg.Done()
			results[idx] = getDatabase()
		}(i)
	}
	wg.Wait()

	fmt.Println("instance id:", instance.id)

	same := true
	for _, r := range results {
		if r != instance {
			same = false
		}
	}
	fmt.Println("all 10 goroutines got the same instance:", same)
}
