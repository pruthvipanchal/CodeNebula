// Compile: go run flag_pkg.go
// With args: go run flag_pkg.go -port 9000 -verbose
// Output (with no args, defaults are used):
//   port=8080 verbose=false config=config.json
//   remaining args: []
package main

import (
	"flag"
	"fmt"
)

func main() {
	port := flag.Int("port", 8080, "server port")
	verbose := flag.Bool("verbose", false, "enable verbose logging")
	config := flag.String("config", "config.json", "config file path")

	flag.Parse()

	fmt.Printf("port=%d verbose=%t config=%s\n", *port, *verbose, *config)
	fmt.Println("remaining args:", flag.Args())
}
