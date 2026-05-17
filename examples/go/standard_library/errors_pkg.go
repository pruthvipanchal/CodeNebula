// Compile: go run errors_pkg.go
// Output:
//   wrapped: user lookup: not found
//   errors.Is ErrNotFound: true
//   errors.As ValidationError, field: email
package main

import (
	"errors"
	"fmt"
)

var ErrNotFound = errors.New("not found")

type ValidationError struct {
	Field string
	Msg   string
}

func (e *ValidationError) Error() string {
	return fmt.Sprintf("validation: %s %s", e.Field, e.Msg)
}

func main() {
	err := fmt.Errorf("user lookup: %w", ErrNotFound)
	fmt.Println("wrapped:", err)
	fmt.Println("errors.Is ErrNotFound:", errors.Is(err, ErrNotFound))

	verr := fmt.Errorf("bad input: %w", &ValidationError{Field: "email", Msg: "required"})
	var ve *ValidationError
	if errors.As(verr, &ve) {
		fmt.Println("errors.As ValidationError, field:", ve.Field)
	}
}
