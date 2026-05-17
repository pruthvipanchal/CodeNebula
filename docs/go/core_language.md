# Go — Core Language

## Variables and Type Inference

**Explanation**: Go is statically typed but uses type inference to eliminate boilerplate. The `:=` short declaration infers the type from the right-hand side at compile time. `var` declarations with explicit types are used at package level or when the zero value is intentional.

**Real-World Scenario**: In a web handler parsing a JSON body, you write `data := make(map[string]any)` rather than `var data map[string]interface{}` — same safety, less noise.

**Snippet**:
```go
package main

import "fmt"

func main() {
    x := 42            // int inferred
    name := "Go"       // string inferred
    ratio := 3.14      // float64 inferred
    active := true     // bool inferred

    var count int      // zero value: 0
    var label string   // zero value: ""

    fmt.Println(x, name, ratio, active, count, label)
}
```

**Example**: [variables.go](../../examples/go/core_language/variables.go)

---

## Basic Types

**Explanation**: Go has a small, fixed set of built-in types. Integer types are explicitly sized (`int8`, `int16`, `int32`, `int64`, `uint8` … `uint64`), plus `int` and `uint` which are platform-width (64-bit on 64-bit systems). `string` is an immutable sequence of bytes (UTF-8). `rune` is an alias for `int32`, representing a Unicode code point.

**Real-World Scenario**: When reading binary protocols (e.g., network packets), you use `uint16` or `uint32` for wire-format fields to exactly match the spec — no overflow surprises.

**Snippet**:
```go
var i int = 100
var u uint32 = 4294967295
var f float64 = 3.141592653589793
var b byte = 255        // alias for uint8
var r rune = '🚀'       // alias for int32, holds Unicode code point
var s string = "Hello, 世界"
var ok bool = true
```

**Example**: [basic_types.go](../../examples/go/core_language/basic_types.go)

---

## Functions

**Explanation**: Functions are first-class values in Go. They can return multiple values — idiomatic Go uses this for `(result, error)` pairs instead of exceptions. Functions can be assigned to variables, passed as arguments, and defined as closures capturing their surrounding scope.

**Real-World Scenario**: A database query function returns `(User, error)`. The caller handles the error inline: `user, err := db.Find(id); if err != nil { return err }`. No try/catch, no stack unwinding — explicit and predictable.

**Snippet**:
```go
// Multiple return values
func divide(a, b float64) (float64, error) {
    if b == 0 {
        return 0, fmt.Errorf("division by zero")
    }
    return a / b, nil
}

// Named return values (document what each value means)
func minMax(nums []int) (min, max int) {
    min, max = nums[0], nums[0]
    for _, n := range nums[1:] {
        if n < min { min = n }
        if n > max { max = n }
    }
    return // naked return
}

// Function as value
double := func(x int) int { return x * 2 }
```

**Example**: [functions.go](../../examples/go/core_language/functions.go)

---

## Control Flow

**Explanation**: Go has `if`, `for`, and `switch` — no `while`, no `do-while`, no `until`. `for` covers all looping: classic C-style, while-style, and range-based. `switch` does not fall through by default (no `break` needed); use `fallthrough` explicitly when required.

**Real-World Scenario**: `for range` over a channel is the standard way to consume a stream of results from a concurrent worker, blocking until the channel is closed.

**Snippet**:
```go
// if with initialization statement
if err := doWork(); err != nil {
    log.Fatal(err)
}

// for as while
for running {
    process()
}

// range over slice (index, value)
for i, v := range items {
    fmt.Println(i, v)
}

// switch — no fall-through by default
switch status {
case 200: fmt.Println("OK")
case 404: fmt.Println("Not Found")
default:  fmt.Println("Other")
}
```

**Example**: [control_flow.go](../../examples/go/core_language/control_flow.go)

---

## Structs

**Explanation**: Go uses structs for composite data types. There is no `class` keyword. Methods are defined outside the struct body using a receiver syntax. Structs are value types — assigning one copies it; use a pointer receiver when a method needs to mutate state or the struct is large.

**Real-World Scenario**: A `User` struct holds name, email, and created-at fields. Methods like `Validate()` and `String()` are attached via receivers, making the type implement interfaces implicitly.

**Snippet**:
```go
type Point struct {
    X, Y float64
}

// Value receiver — reads state
func (p Point) Distance() float64 {
    return math.Sqrt(p.X*p.X + p.Y*p.Y)
}

// Pointer receiver — mutates state
func (p *Point) Scale(factor float64) {
    p.X *= factor
    p.Y *= factor
}

p := Point{X: 3, Y: 4}
fmt.Println(p.Distance()) // 5
p.Scale(2)
fmt.Println(p)            // {6 8}
```

**Example**: [structs.go](../../examples/go/core_language/structs.go)

---

## Interfaces

**Explanation**: Interfaces in Go are satisfied implicitly — a type implements an interface simply by having the required methods, with no `implements` keyword. This enables loose coupling: packages define small interfaces, and any type that happens to match can be used. The most famous Go interface is `io.Reader` with its single `Read([]byte) (int, error)` method.

**Real-World Scenario**: A logging library accepts an `io.Writer` interface. You can pass `os.Stdout`, a `bytes.Buffer`, a file, a network connection, or your own custom writer — all without modifying the logging library.

**Snippet**:
```go
type Stringer interface {
    String() string
}

type Temperature struct {
    Celsius float64
}

// Temperature implicitly satisfies Stringer
func (t Temperature) String() string {
    return fmt.Sprintf("%.1f°C", t.Celsius)
}

func Print(s Stringer) {
    fmt.Println(s.String())
}

Print(Temperature{36.6}) // 36.6°C
```

**Example**: [interfaces.go](../../examples/go/core_language/interfaces.go)

---

## Pointers

**Explanation**: Go has pointers but no pointer arithmetic. A pointer holds the memory address of a value. Use `&` to take an address, `*` to dereference. Pointers are primarily used for: mutating a value through a function argument, sharing large structs without copying, and expressing optional values (nil pointer = absent).

**Real-World Scenario**: A configuration parser populates a struct via a pointer parameter: `func Parse(cfg *Config) error`. The caller allocates the struct and passes its address, and the parser fills it in place — no copy overhead.

**Snippet**:
```go
x := 10
p := &x       // p is *int, holds address of x
*p = 20       // dereference: x is now 20
fmt.Println(x) // 20

// nil pointer — optional value pattern
type Node struct {
    Value int
    Next  *Node // nil when there is no next node
}
```

**Example**: [pointers.go](../../examples/go/core_language/pointers.go)

---

## Arrays and Slices

**Explanation**: An array in Go has a fixed length that is part of its type: `[3]int` and `[4]int` are different types. In practice, arrays are rarely used directly — **slices** are the workhorse. A slice is a descriptor (pointer + length + capacity) over an underlying array. `make([]T, len, cap)` allocates one. `append` grows slices automatically.

**Real-World Scenario**: Reading lines from a file: `lines := make([]string, 0, 100)` preallocates capacity for 100 lines (avoids repeated reallocation as you append), then `lines = append(lines, line)` for each line read.

**Snippet**:
```go
// Array (fixed size, value type)
arr := [3]int{1, 2, 3}

// Slice (dynamic, reference type)
s := []int{10, 20, 30}
s = append(s, 40)

// Slice of slice
sub := s[1:3] // [20, 30] — shares underlying array

// make with capacity hint
buf := make([]byte, 0, 4096)
```

**Example**: [slices.go](../../examples/go/core_language/slices.go)

---

## Maps

**Explanation**: A `map[K]V` is Go's built-in hash map. Keys must be `comparable` (no slices, maps, or functions as keys). The zero value of a map is `nil` — attempting to write to a nil map panics. Always initialize with `make` or a literal. The two-value assignment `v, ok := m[key]` safely checks for key presence without panicking on missing keys.

**Real-World Scenario**: Counting word frequencies in a document: `counts := make(map[string]int)` then `counts[word]++` — the zero value of `int` (0) means missing keys auto-initialize correctly.

**Snippet**:
```go
// Literal initialization
scores := map[string]int{
    "Alice": 95,
    "Bob":   87,
}

// Safe lookup
score, ok := scores["Charlie"]
if !ok {
    fmt.Println("not found")
}

// Delete
delete(scores, "Bob")

// Iterate (order is random)
for name, s := range scores {
    fmt.Println(name, s)
}
```

**Example**: [maps.go](../../examples/go/core_language/maps.go)

---

## Error Handling

**Explanation**: Go uses explicit error return values instead of exceptions. The `error` interface has one method: `Error() string`. Functions signal failure by returning a non-nil error as their last return value. `fmt.Errorf("context: %w", err)` wraps errors with context; `errors.Is` and `errors.As` unwrap them for inspection.

**Real-World Scenario**: An HTTP client function returns `(Response, error)`. Each call site decides whether to log-and-continue, retry, or propagate the error up the stack — the decision is explicit at every layer, making error flows easy to audit in code review.

**Snippet**:
```go
import "errors"

var ErrNotFound = errors.New("not found")

func findUser(id int) (*User, error) {
    if id <= 0 {
        return nil, fmt.Errorf("findUser: invalid id %d", id)
    }
    user := db.Lookup(id)
    if user == nil {
        return nil, fmt.Errorf("findUser %d: %w", id, ErrNotFound)
    }
    return user, nil
}

// Caller
user, err := findUser(42)
if errors.Is(err, ErrNotFound) {
    // handle not-found specifically
}
```

**Example**: [error_handling.go](../../examples/go/core_language/error_handling.go)

---

## Defer

**Explanation**: `defer` schedules a function call to run when the surrounding function returns — regardless of whether it returns normally or via `panic`. Multiple defers execute in LIFO order. The primary use is resource cleanup: closing files, releasing locks, closing database connections.

**Real-World Scenario**: Opening a file and deferring its close immediately after the open check ensures the file is always closed, even if the function returns early due to an error ten lines later.

**Snippet**:
```go
func copyFile(src, dst string) error {
    in, err := os.Open(src)
    if err != nil {
        return err
    }
    defer in.Close() // guaranteed to run when copyFile returns

    out, err := os.Create(dst)
    if err != nil {
        return err
    }
    defer out.Close()

    _, err = io.Copy(out, in)
    return err
}
```

**Example**: [defer.go](../../examples/go/core_language/defer.go)

---

## Closures

**Explanation**: A closure is a function that captures variables from its enclosing scope by reference. In Go, closures are commonly used to create stateful function values, implement middleware, and build iterators. Since Go 1.22, range loop variables create fresh bindings per iteration, eliminating the classic closure-in-loop pitfall.

**Real-World Scenario**: A counter factory returns a closure that increments an internal counter each time it's called — useful for generating unique IDs in a request handler without shared global state.

**Snippet**:
```go
func makeCounter() func() int {
    n := 0
    return func() int {
        n++
        return n
    }
}

c := makeCounter()
fmt.Println(c()) // 1
fmt.Println(c()) // 2
fmt.Println(c()) // 3

// Each counter has independent state
d := makeCounter()
fmt.Println(d()) // 1
```

**Example**: [closures.go](../../examples/go/core_language/closures.go)

---

## Embedding

**Explanation**: Go's alternative to inheritance is struct embedding. Embedding a type promotes its methods to the outer struct, allowing composition-based reuse without the complexity of class hierarchies. The embedded type remains accessible by its type name if needed.

**Real-World Scenario**: A `Logger` struct embeds `io.Writer` and adds a prefix field. Any method on the embedded writer is promoted — `logger.Write(data)` delegates directly to the inner writer.

**Snippet**:
```go
type Animal struct {
    Name string
}
func (a Animal) Speak() string { return a.Name + " makes a sound" }

type Dog struct {
    Animal           // embedded — Dog inherits Speak
    Breed string
}
func (d Dog) Speak() string { return d.Name + " barks" } // override

d := Dog{Animal: Animal{Name: "Rex"}, Breed: "Labrador"}
fmt.Println(d.Speak())       // Rex barks
fmt.Println(d.Animal.Speak()) // Rex makes a sound
fmt.Println(d.Name)           // promoted field access
```

**Example**: [embedding.go](../../examples/go/core_language/embedding.go)
