// Compile: go run pointers.go
// Output:
//   before: 10
//   after:  20
//   list: 1 -> 2 -> 3 -> nil
package main

import "fmt"

type Node struct {
	Value int
	Next  *Node
}

func main() {
	x := 10
	p := &x // p is *int, holds address of x
	fmt.Println("before:", x)
	*p = 20 // dereference and assign
	fmt.Println("after: ", x)

	// nil pointer terminates a linked list
	list := &Node{Value: 1, Next: &Node{Value: 2, Next: &Node{Value: 3}}}
	fmt.Print("list: ")
	for n := list; n != nil; n = n.Next {
		fmt.Printf("%d -> ", n.Value)
	}
	fmt.Println("nil")
}
