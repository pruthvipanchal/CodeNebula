// Compile: go run control_flow.go
// Output:
//   err check: ok
//   countdown: 3 2 1
//   even: 0 2 4
//   status 200: OK
package main

import "fmt"

func doWork() error { return nil }

func main() {
	// if with initialization statement
	if err := doWork(); err != nil {
		fmt.Println("error:", err)
	} else {
		fmt.Println("err check: ok")
	}

	// for as while
	n := 3
	fmt.Print("countdown:")
	for n > 0 {
		fmt.Print(" ", n)
		n--
	}
	fmt.Println()

	// range over slice
	fmt.Print("even:")
	for _, v := range []int{0, 1, 2, 3, 4} {
		if v%2 != 0 {
			continue
		}
		fmt.Print(" ", v)
	}
	fmt.Println()

	// switch — no fall-through by default
	status := 200
	switch status {
	case 200:
		fmt.Println("status 200: OK")
	case 404:
		fmt.Println("status 404: Not Found")
	default:
		fmt.Println("status: Other")
	}
}
