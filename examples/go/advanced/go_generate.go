// Compile: go run go_generate.go
// Output:
//   status 0 -> Active
//   status 1 -> Inactive
//   status 2 -> Pending
//
// `go generate` runs the //go:generate directives below. In a real
// project, `stringer` would emit a status_string.go file with an
// optimized String() method. Here String() is written by hand to keep
// the example self-contained and runnable.

//go:generate stringer -type=Status

package main

import "fmt"

type Status int

const (
	Active Status = iota
	Inactive
	Pending
)

func (s Status) String() string {
	return [...]string{"Active", "Inactive", "Pending"}[s]
}

func main() {
	for _, s := range []Status{Active, Inactive, Pending} {
		fmt.Printf("status %d -> %s\n", int(s), s)
	}
}
