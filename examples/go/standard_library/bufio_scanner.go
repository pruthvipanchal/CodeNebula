// Compile: go run bufio_scanner.go
// Output:
//   line 1: alpha
//   line 2: beta
//   line 3: gamma
//   words: 4
package main

import (
	"bufio"
	"fmt"
	"strings"
)

func main() {
	input := "alpha\nbeta\ngamma"

	// Scan line by line
	scanner := bufio.NewScanner(strings.NewReader(input))
	lineNo := 0
	for scanner.Scan() {
		lineNo++
		fmt.Printf("line %d: %s\n", lineNo, scanner.Text())
	}

	// Custom split function — scan words
	ws := bufio.NewScanner(strings.NewReader("the quick brown fox"))
	ws.Split(bufio.ScanWords)
	count := 0
	for ws.Scan() {
		count++
	}
	fmt.Println("words:", count)
}
