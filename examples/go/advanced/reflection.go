// Compile: go run reflection.go
// Output:
//   Field: Host  Tag: host  Value: localhost
//   Field: Port  Tag: port  Value: 8080
package main

import (
	"fmt"
	"reflect"
)

type Config struct {
	Host string `json:"host"`
	Port int    `json:"port"`
}

func printFields(v any) {
	rv := reflect.ValueOf(v)
	rt := reflect.TypeOf(v)

	if rv.Kind() == reflect.Ptr {
		rv = rv.Elem()
		rt = rt.Elem()
	}

	for i := 0; i < rv.NumField(); i++ {
		field := rt.Field(i)
		value := rv.Field(i)
		tag := field.Tag.Get("json")
		fmt.Printf("Field: %s  Tag: %s  Value: %v\n", field.Name, tag, value)
	}
}

func main() {
	printFields(Config{Host: "localhost", Port: 8080})
}
