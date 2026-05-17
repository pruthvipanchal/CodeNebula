// Compile: go run channel_direction.go
// Output:
//   0
//   1
//   2
package main

import "fmt"

// Send-only parameter — may only write to the channel
func produce(out chan<- int) {
	for i := 0; i < 3; i++ {
		out <- i
	}
	close(out)
}

// Receive-only parameter — may only read from the channel
func consume(in <-chan int, done chan<- struct{}) {
	for v := range in {
		fmt.Println(v)
	}
	done <- struct{}{}
}

func main() {
	ch := make(chan int) // bidirectional
	done := make(chan struct{})

	go produce(ch)       // passed as chan<- int
	go consume(ch, done) // passed as <-chan int

	<-done
}
