// Compile: go run constants.go
// Output:
//   Pi: 3.14159
//   Wednesday is day 3
//   1 MB = 1048576 bytes
//   1 GB = 1073741824 bytes
package main

import "fmt"

const Pi = 3.14159

type Weekday int

const (
	Sunday Weekday = iota // 0
	Monday                // 1
	Tuesday               // 2
	Wednesday             // 3
)

// iota with a shift expression — byte-size units
const (
	_  = iota             // skip 0
	KB = 1 << (10 * iota) // 1 << 10
	MB                    // 1 << 20
	GB                    // 1 << 30
)

func main() {
	fmt.Println("Pi:", Pi)
	fmt.Println("Wednesday is day", int(Wednesday))
	fmt.Println("1 MB =", MB, "bytes")
	fmt.Println("1 GB =", GB, "bytes")
}
