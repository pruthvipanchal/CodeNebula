// Compile: go run memory_model.go
// Output:
//   data is visible: loaded
//
// The channel close below establishes a happens-before edge: the write
// to `data` is guaranteed visible to the goroutine that receives from
// the channel. Without that synchronization the read could see "".
package main

import "fmt"

var data string

func main() {
	done := make(chan struct{})

	go func() {
		data = "loaded"
		close(done) // send/close happens-before the receive
	}()

	<-done // after this, data's write is guaranteed visible
	fmt.Println("data is visible:", data)
}
