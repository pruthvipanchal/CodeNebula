// Compile: go run interface_composition.go
// Output:
//   wrote 5 bytes
//   read back: hello
//   closed
package main

import (
	"bytes"
	"fmt"
	"io"
)

// Small interfaces compose into larger contracts
type Reader interface{ Read([]byte) (int, error) }
type Writer interface{ Write([]byte) (int, error) }
type Closer interface{ Close() error }

type ReadWriteCloser interface {
	Reader
	Writer
	Closer
}

// buffer satisfies ReadWriteCloser
type buffer struct {
	bytes.Buffer
}

func (b *buffer) Close() error {
	fmt.Println("closed")
	return nil
}

func useStream(rwc ReadWriteCloser) {
	n, _ := rwc.Write([]byte("hello"))
	fmt.Println("wrote", n, "bytes")

	data, _ := io.ReadAll(rwc)
	fmt.Println("read back:", string(data))

	rwc.Close()
}

func main() {
	useStream(&buffer{})
}
