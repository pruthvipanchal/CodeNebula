// Compile: go run io_basics.go
// Output:
//   copied 13 bytes
//   read back: Hello, CodeNebula
//   limited: Hello
package main

import (
	"bytes"
	"fmt"
	"io"
	"strings"
)

func main() {
	// io.Copy streams from any Reader to any Writer
	src := strings.NewReader("Hello, CodeNebula")
	var dst bytes.Buffer
	n, _ := io.Copy(&dst, src)
	fmt.Println("copied", n, "bytes")
	fmt.Println("read back:", dst.String())

	// io.LimitReader caps how much is read
	limited := io.LimitReader(strings.NewReader("Hello, World"), 5)
	data, _ := io.ReadAll(limited)
	fmt.Println("limited:", string(data))
}
