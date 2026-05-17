// Compile: go run init_functions.go
// Output:
//   first init ran
//   second init ran
//   main: env=production
package main

import "fmt"

var config map[string]string

// Multiple init functions run in source order, before main.
func init() {
	fmt.Println("first init ran")
	config = map[string]string{"env": "production"}
}

func init() {
	fmt.Println("second init ran")
}

func main() {
	fmt.Println("main: env=" + config["env"])
}
