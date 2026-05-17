// Compile: go run regexp_pkg.go
// Output:
//   match: true
//   found: a@b.io
//   submatch date parts: [2024-01-15 2024 01 15]
//   digits removed: abc
package main

import (
	"fmt"
	"regexp"
)

// Compile once — safe for concurrent reuse
var emailRe = regexp.MustCompile(`[\w.]+@[\w.]+\.\w+`)

func main() {
	fmt.Println("match:", emailRe.MatchString("contact me@site.com"))
	fmt.Println("found:", emailRe.FindString("ping a@b.io now"))

	dateRe := regexp.MustCompile(`(\d{4})-(\d{2})-(\d{2})`)
	m := dateRe.FindStringSubmatch("2024-01-15")
	fmt.Println("submatch date parts:", m)

	digitRe := regexp.MustCompile(`\d`)
	fmt.Println("digits removed:", digitRe.ReplaceAllString("a1b2c3", ""))
}
