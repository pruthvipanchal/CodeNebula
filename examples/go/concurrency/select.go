// Compile: go run select.go
// Output:
//   got: fast result
package main

import (
	"fmt"
	"time"
)

func fetch(label string, delay time.Duration) <-chan string {
	ch := make(chan string, 1)
	go func() {
		time.Sleep(delay)
		ch <- label
	}()
	return ch
}

func main() {
	fast := fetch("fast result", 50*time.Millisecond)
	slow := fetch("slow result", 500*time.Millisecond)

	// select picks whichever channel is ready first
	select {
	case r := <-fast:
		fmt.Println("got:", r)
	case r := <-slow:
		fmt.Println("got:", r)
	case <-time.After(time.Second):
		fmt.Println("timeout")
	}
}
