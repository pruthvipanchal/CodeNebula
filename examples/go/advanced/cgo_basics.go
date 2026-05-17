// Compile: go run cgo_basics.go   (requires a C compiler + CGO_ENABLED=1)
// Output:
//   C says: 42 doubled is 84
//
// CGo lets Go call C code. The C source lives in the comment block
// immediately above `import "C"` — there must be no blank line between
// the comment and the import.
package main

/*
#include <stdlib.h>

int double_it(int n) {
    return n * 2;
}
*/
import "C"
import "fmt"

func main() {
	n := C.int(42)
	doubled := C.double_it(n)
	fmt.Printf("C says: %d doubled is %d\n", int(n), int(doubled))
}
