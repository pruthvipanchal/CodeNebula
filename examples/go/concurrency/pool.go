// Compile: go run pool.go
// Output:
//   built: [item-0 item-1 item-2]
//   built: [item-0 item-1 item-2]
//   buffers are reused from the pool
package main

import (
	"bytes"
	"fmt"
	"sync"
)

var bufPool = sync.Pool{
	New: func() any { return new(bytes.Buffer) },
}

func build() string {
	buf := bufPool.Get().(*bytes.Buffer)
	buf.Reset()            // always reset a reused object
	defer bufPool.Put(buf) // return it for the next caller

	for i := 0; i < 3; i++ {
		if i > 0 {
			buf.WriteString(" ")
		}
		fmt.Fprintf(buf, "item-%d", i)
	}
	return buf.String()
}

func main() {
	fmt.Println("built: [" + build() + "]")
	fmt.Println("built: [" + build() + "]")
	fmt.Println("buffers are reused from the pool")
}
