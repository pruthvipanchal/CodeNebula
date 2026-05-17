// Compile: go run time_basics.go
// Output (durations vary):
//   formatted: 2024-01-15 10:30:00
//   one hour later is after now: true
//   elapsed under 1s: true
package main

import (
	"fmt"
	"time"
)

func main() {
	// Go's reference time layout: Mon Jan 2 15:04:05 MST 2006
	ref := time.Date(2024, 1, 15, 10, 30, 0, 0, time.UTC)
	fmt.Println("formatted:", ref.Format("2006-01-02 15:04:05"))

	now := time.Now()
	later := now.Add(time.Hour)
	fmt.Println("one hour later is after now:", later.After(now))

	// Measure elapsed time
	start := time.Now()
	time.Sleep(10 * time.Millisecond)
	elapsed := time.Since(start)
	fmt.Println("elapsed under 1s:", elapsed < time.Second)
}
