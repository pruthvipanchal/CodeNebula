// Compile: go run unsafe_basics.go
// Output:
//   Point size: 8 bytes
//   Point align: 4 bytes
//   zero-copy string: hello
package main

import (
	"fmt"
	"unsafe"
)

type Point struct {
	X, Y float32
}

// bytesToString converts without copying (read-only use only).
func bytesToString(b []byte) string {
	if len(b) == 0 {
		return ""
	}
	return unsafe.String(&b[0], len(b))
}

func main() {
	p := Point{1.0, 2.0}
	fmt.Println("Point size:", unsafe.Sizeof(p), "bytes")
	fmt.Println("Point align:", unsafe.Alignof(p), "bytes")

	b := []byte("hello")
	fmt.Println("zero-copy string:", bytesToString(b))
}
