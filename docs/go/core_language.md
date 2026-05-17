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

---

## Constants and iota

**Explanation**: Constants are immutable values fixed at compile time, declared with `const`. The `iota` identifier is a constant generator that starts at 0 within a `const` block and increments by one for each line — it is the idiomatic way to create enumerated values. Untyped constants in Go have arbitrary precision and adapt to whatever type the context requires.

**Real-World Scenario**: Defining a set of log levels (`Debug`, `Info`, `Warn`, `Error`) — `iota` assigns 0, 1, 2, 3 automatically, so inserting a new level later renumbers everything without manual edits.

**Snippet**:
```go
const Pi = 3.14159 // untyped constant

type Weekday int

const (
    Sunday Weekday = iota // 0
    Monday                // 1
    Tuesday               // 2
    Wednesday             // 3
)

// iota with expressions — byte-size units
const (
    _  = iota             // skip 0
    KB = 1 << (10 * iota) // 1 << 10
    MB                    // 1 << 20
    GB                    // 1 << 30
)
```

**Example**: [constants.go](../../examples/go/core_language/constants.go)

---

## Type Assertions

**Explanation**: A type assertion extracts the concrete value stored inside an interface. `v, ok := i.(T)` is the safe two-value form — `ok` is `false` instead of panicking when the assertion fails. The single-value form `v := i.(T)` panics on mismatch, so reserve it for cases where the type is guaranteed.

**Real-World Scenario**: A function accepts `error` and wants special handling for a specific error type. A type assertion `if ne, ok := err.(*net.OpError); ok` checks whether the error is a network operation error and, if so, reads its fields.

**Snippet**:
```go
var i any = "hello"

// Safe form — never panics
s, ok := i.(string)
fmt.Println(s, ok) // hello true

n, ok := i.(int)
fmt.Println(n, ok) // 0 false

// Unsafe form — panics if i does not hold a string
s = i.(string)
```

**Example**: [type_assertions.go](../../examples/go/core_language/type_assertions.go)

---

## Type Switches

**Explanation**: A type switch is a control structure that branches on the dynamic type of an interface value. The special syntax `switch v := i.(type)` binds `v` to the concrete value in each case, with the right static type. It is the idiomatic way to handle a value that may be one of several types.

**Real-World Scenario**: A JSON decoder unmarshals arbitrary data into `any`. A type switch dispatches on whether each value is a `string`, `float64`, `bool`, `map[string]any`, or `[]any` — building a typed structure from untyped input.

**Snippet**:
```go
func describe(i any) string {
    switch v := i.(type) {
    case int:
        return fmt.Sprintf("int: %d", v)
    case string:
        return fmt.Sprintf("string of length %d", len(v))
    case bool:
        return fmt.Sprintf("bool: %t", v)
    case nil:
        return "nil value"
    default:
        return fmt.Sprintf("unknown type %T", v)
    }
}
```

**Example**: [type_switches.go](../../examples/go/core_language/type_switches.go)

---

## Variadic Functions

**Explanation**: A variadic function accepts a variable number of trailing arguments of the same type, declared with `...T`. Inside the function the parameter is a slice `[]T`. An existing slice can be passed to a variadic parameter with the spread operator `slice...`.

**Real-World Scenario**: `fmt.Printf` and `append` are variadic. A custom `logf(format string, args ...any)` wrapper forwards its variadic args straight into `fmt.Sprintf(format, args...)` — adding a timestamp or prefix without changing the call signature users expect.

**Snippet**:
```go
func sum(nums ...int) int {
    total := 0
    for _, n := range nums {
        total += n
    }
    return total
}

sum(1, 2, 3)        // 6 — pass individual args
sum()               // 0 — zero args is valid

nums := []int{4, 5, 6}
sum(nums...)        // 15 — spread an existing slice
```

**Example**: [variadic.go](../../examples/go/core_language/variadic.go)

---

## Named Types and Type Definitions

**Explanation**: `type Celsius float64` creates a new named type distinct from its underlying type — values are not interchangeable without an explicit conversion, which prevents whole classes of unit-mixing bugs. A *type alias* `type Byte = uint8` (with `=`) is different: it creates no new type, just another name. Named types can carry their own methods.

**Real-World Scenario**: A measurement library defines `type Celsius float64` and `type Fahrenheit float64`. Because they are distinct types, the compiler rejects accidentally passing a `Fahrenheit` where a `Celsius` is expected — the bug is caught at compile time, not in production.

**Snippet**:
```go
type Celsius float64
type Fahrenheit float64

func (c Celsius) ToF() Fahrenheit {
    return Fahrenheit(c*9/5 + 32)
}

var c Celsius = 100
var f Fahrenheit = c.ToF() // 212

// var bad Fahrenheit = c   // compile error: cannot use c (Celsius) as Fahrenheit

type Byte = uint8 // alias — Byte and uint8 are the SAME type
```

**Example**: [named_types.go](../../examples/go/core_language/named_types.go)

---

## init Functions

**Explanation**: `init` is a special function that runs automatically before `main`, after all package-level variables are initialized. A package (or even a single file) may declare multiple `init` functions; they run in the order they appear. `init` takes no arguments and returns nothing — it cannot be called directly.

**Real-World Scenario**: A database driver package registers itself with `database/sql` in an `init` function. Importing the driver for its side effect (`import _ "github.com/lib/pq"`) triggers `init`, which calls `sql.Register` — the program never references the package by name.

**Snippet**:
```go
var config map[string]string

func init() {
    // Runs once, before main, after package vars are set
    config = map[string]string{
        "env":  "production",
        "tier": "backend",
    }
}

func main() {
    fmt.Println(config["env"]) // production — already populated
}
```

**Example**: [init_functions.go](../../examples/go/core_language/init_functions.go)

---

## The Blank Identifier

**Explanation**: The blank identifier `_` is a write-only placeholder that discards a value. Go requires every declared variable and import to be used; `_` satisfies that rule when a value is intentionally unwanted — an unused return value, an unwanted range index, or an import needed only for its side effects.

**Real-World Scenario**: A function returns `(value, error)` but a particular call site cannot fail and only needs the value: `data, _ := json.Marshal(v)`. The blank identifier also enforces interface satisfaction at compile time: `var _ io.Reader = (*MyType)(nil)`.

**Snippet**:
```go
// Discard the index, keep the value
for _, v := range items {
    fmt.Println(v)
}

// Discard one of multiple returns
_, err := fmt.Println("hi")

// Import for side effects only (runs the package's init)
import _ "github.com/lib/pq"

// Compile-time interface check
var _ io.Writer = (*MyWriter)(nil)
```

**Example**: [blank_identifier.go](../../examples/go/core_language/blank_identifier.go)

---

## Panic and Recover

**Explanation**: `panic` stops normal execution and begins unwinding the stack, running deferred functions along the way. `recover`, called inside a deferred function, stops the unwinding and returns the panic value — letting a program regain control. Go's convention is to use errors for expected failures and reserve `panic` for truly unrecoverable situations (programmer bugs, impossible states).

**Real-World Scenario**: An HTTP server wraps each request handler in a deferred `recover`. If a handler panics (e.g. a nil-pointer dereference), `recover` catches it, logs the stack, and returns a 500 response — one bad request doesn't crash the whole server.

**Snippet**:
```go
func safeDivide(a, b int) (result int, err error) {
    defer func() {
        if r := recover(); r != nil {
            err = fmt.Errorf("recovered: %v", r)
        }
    }()
    result = a / b // panics if b == 0
    return result, nil
}

r, err := safeDivide(10, 0)
fmt.Println(r, err) // 0 recovered: runtime error: integer divide by zero
```

**Example**: [panic_recover.go](../../examples/go/core_language/panic_recover.go)

---

## Labels and goto

**Explanation**: Go supports statement labels used with `break`, `continue`, and `goto`. A labeled `break` or `continue` targets an *outer* loop — the cleanest way to exit a nested loop. `goto` jumps to a label within the same function; it is rarely used but occasionally clarifies error-cleanup paths or generated code.

**Real-World Scenario**: Searching a 2D grid for a value — once found, a labeled `break Outer` exits both the inner and outer loops at once, avoiding a flag variable checked after every inner iteration.

**Snippet**:
```go
grid := [][]int{{1, 2}, {3, 4}, {5, 6}}
target := 4

Outer:
for i, row := range grid {
    for j, v := range row {
        if v == target {
            fmt.Printf("found at [%d][%d]\n", i, j)
            break Outer // exits BOTH loops
        }
    }
}

// goto — jump to a label in the same function
i := 0
loop:
if i < 3 {
    fmt.Println(i)
    i++
    goto loop
}
```

**Example**: [labels.go](../../examples/go/core_language/labels.go)
