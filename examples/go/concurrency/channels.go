// Compile: go run channels.go
// Output:
//   received: 42
//   a
//   b
//   c
package main

import "fmt"

func main() {
	// Unbuffered channel — synchronizes sender and receiver
	ch := make(chan int)
	go func() { ch <- 42 }()
	fmt.Println("received:", <-ch)

	// Buffered channel — sender does not block until buffer full
	buf := make(chan string, 3)
	buf <- "a"
	buf <- "b"
	buf <- "c"

	close(buf)
	for s := range buf {
		fmt.Println(s)
	}
}
