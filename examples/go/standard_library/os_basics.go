// Compile: go run os_basics.go
// Output:
//   wrote and read: hello from os
//   PATH is set: true
//   args count >= 1: true
package main

import (
	"fmt"
	"os"
)

func main() {
	const path = "os_demo.txt"

	// Write then read a small file
	if err := os.WriteFile(path, []byte("hello from os"), 0644); err != nil {
		fmt.Println("write error:", err)
		return
	}
	defer os.Remove(path)

	data, err := os.ReadFile(path)
	if err != nil {
		fmt.Println("read error:", err)
		return
	}
	fmt.Println("wrote and read:", string(data))

	// Environment variables
	_, ok := os.LookupEnv("PATH")
	fmt.Println("PATH is set:", ok)

	fmt.Println("args count >= 1:", len(os.Args) >= 1)
}
