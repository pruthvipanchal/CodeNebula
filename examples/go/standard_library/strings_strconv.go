// Compile: go run strings_strconv.go
// Output:
//   trimmed: Hello, World!
//   contains World: true
//   split: [a b c]
//   joined: a | b | c
//   built: abc
//   atoi: 42
//   float: 3.14
package main

import (
	"fmt"
	"strconv"
	"strings"
)

func main() {
	s := "  Hello, World!  "
	fmt.Println("trimmed:", strings.TrimSpace(s))
	fmt.Println("contains World:", strings.Contains(s, "World"))

	parts := strings.Split("a,b,c", ",")
	fmt.Println("split:", parts)
	fmt.Println("joined:", strings.Join(parts, " | "))

	var b strings.Builder
	for _, p := range parts {
		b.WriteString(p)
	}
	fmt.Println("built:", b.String())

	n, _ := strconv.Atoi("42")
	fmt.Println("atoi:", n)

	f, _ := strconv.ParseFloat("3.14", 64)
	fmt.Println("float:", f)
}
