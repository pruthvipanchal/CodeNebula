// Compile: go run defer.go
// Output:
//   opening resource
//   working...
//   closing resource  ← runs even on early return
package main

import "fmt"

type Resource struct{ name string }

func (r *Resource) Close() { fmt.Println("closing resource") }

func open(name string) *Resource {
	fmt.Println("opening resource")
	return &Resource{name: name}
}

func doWork() error {
	r := open("db-connection")
	defer r.Close() // guaranteed to run when doWork returns

	fmt.Println("working...")
	return nil
}

func main() {
	_ = doWork()
}
