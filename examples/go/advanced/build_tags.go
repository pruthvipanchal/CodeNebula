// Compile: go run build_tags.go
// Output (value depends on your OS):
//   running on: <linux|darwin|windows>
//   build tag form shown in comments below
//
// Build tags select which files compile. A file starting with:
//
//   //go:build linux || darwin
//
// is only included when GOOS matches. Custom tags work too:
//
//   //go:build integration      → go build -tags integration
//
// At runtime, the portable alternative is the `runtime` package.
package main

import (
	"fmt"
	"runtime"
)

func main() {
	fmt.Println("running on:", runtime.GOOS)
	fmt.Println("architecture:", runtime.GOARCH)
}
