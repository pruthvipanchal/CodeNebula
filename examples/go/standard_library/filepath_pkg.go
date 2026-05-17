// Compile: go run filepath_pkg.go
// Output (separators are OS-specific):
//   joined: data/logs/app.log
//   base: app.log
//   dir:  data/logs
//   ext:  .log
//   cleaned: a/c
package main

import (
	"fmt"
	"path/filepath"
)

func main() {
	p := filepath.Join("data", "logs", "app.log")
	fmt.Println("joined:", filepath.ToSlash(p))

	fmt.Println("base:", filepath.Base(p))
	fmt.Println("dir: ", filepath.ToSlash(filepath.Dir(p)))
	fmt.Println("ext: ", filepath.Ext(p))

	// Clean resolves . and .. segments
	fmt.Println("cleaned:", filepath.ToSlash(filepath.Clean("a/b/../c")))
}
