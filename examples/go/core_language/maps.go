// Compile: go run maps.go
// Output:
//   Alice: 95
//   Charlie present: false
//   after delete, has Bob: false
//   total entries: 1
package main

import "fmt"

func main() {
	scores := map[string]int{
		"Alice": 95,
		"Bob":   87,
	}

	fmt.Println("Alice:", scores["Alice"])

	// Comma-ok lookup — safe check for missing keys
	_, ok := scores["Charlie"]
	fmt.Println("Charlie present:", ok)

	delete(scores, "Bob")
	_, hasBob := scores["Bob"]
	fmt.Println("after delete, has Bob:", hasBob)

	fmt.Println("total entries:", len(scores))
}
