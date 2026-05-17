# Go — Advanced

## Generics (Type Parameters)

**Explanation**: Generics, introduced in Go 1.18, allow functions and types to be parameterized over types. Type parameters are declared in square brackets: `func Map[T, U any](s []T, f func(T) U) []U`. Interface constraints specify what operations are valid on type parameters — `comparable` for equality, `constraints.Ordered` for comparison. The `any` constraint accepts any type.

**Real-World Scenario**: A generic `Filter` function works on slices of any type without code duplication: `Filter(users, func(u User) bool { return u.Active })` — same logic for `[]User`, `[]Order`, `[]Product` without writing three separate functions.

**Snippet**:
```go
// Generic function
func Map[T, U any](s []T, f func(T) U) []U {
    result := make([]U, len(s))
    for i, v := range s {
        result[i] = f(v)
    }
    return result
}

func Filter[T any](s []T, pred func(T) bool) []T {
    var out []T
    for _, v := range s {
        if pred(v) { out = append(out, v) }
    }
    return out
}

// Generic type
type Stack[T any] struct{ items []T }
func (s *Stack[T]) Push(v T) { s.items = append(s.items, v) }
func (s *Stack[T]) Pop() (T, bool) {
    if len(s.items) == 0 { var zero T; return zero, false }
    v := s.items[len(s.items)-1]
    s.items = s.items[:len(s.items)-1]
    return v, true
}
```

**Example**: [generics.go](../../examples/go/advanced/generics.go)

---

## Reflection

**Explanation**: The `reflect` package allows inspecting and manipulating values at runtime without compile-time type knowledge. `reflect.TypeOf(v)` returns the type; `reflect.ValueOf(v)` returns the value. Reflection is used in serialization libraries (encoding/json), ORMs, dependency injection frameworks, and test utilities. It is slower than direct code — use it when compile-time polymorphism (interfaces or generics) is not sufficient.

**Real-World Scenario**: A struct validator iterates over fields using reflection, checking `validate:` struct tags: `required`, `min`, `max`. This lets one validation function work for any struct type without code generation.

**Snippet**:
```go
import "reflect"

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
        fmt.Printf("Field: %s, Tag: %s, Value: %v\n",
            field.Name, tag, value)
    }
}

type Config struct {
    Host string `json:"host"`
    Port int    `json:"port"`
}
printFields(Config{"localhost", 8080})
```

**Example**: [reflection.go](../../examples/go/advanced/reflection.go)

---

## Interface Composition

**Explanation**: Go interfaces can embed other interfaces, building larger contracts from smaller ones. The standard library uses this heavily: `io.ReadWriter` embeds both `io.Reader` and `io.Writer`; `io.ReadWriteCloser` adds `io.Closer`. This compositional approach lets you accept exactly the capabilities you need — nothing more, nothing less.

**Real-World Scenario**: A compression library accepts `io.ReadWriter` — it needs both read and write on the same stream. A network conn (`net.Conn`) satisfies this; so does a `bytes.Buffer`. No inheritance hierarchy required.

**Snippet**:
```go
type Reader interface { Read([]byte) (int, error) }
type Writer interface { Write([]byte) (int, error) }
type Closer interface { Close() error }

// Composed interfaces
type ReadWriter interface {
    Reader
    Writer
}
type ReadWriteCloser interface {
    Reader
    Writer
    Closer
}

// Accept minimum required capability
func compress(rw io.ReadWriter) error {
    // reads uncompressed, writes compressed to the same conn
}

// Custom composed interface for a specific domain
type Repository interface {
    Querier
    Mutator
    io.Closer
}
```

**Example**: [interface_composition.go](../../examples/go/advanced/interface_composition.go)

---

## Build Tags and Conditional Compilation

**Explanation**: Build tags (also called build constraints) control which files are included in a build. The `//go:build` directive at the top of a file specifies conditions: OS (`linux`, `windows`, `darwin`), architecture (`amd64`, `arm64`), Go version (`go1.21`), or custom tags. This enables platform-specific implementations without `#ifdef`.

**Real-World Scenario**: A file system watcher has separate implementations per OS: `watcher_linux.go` uses `inotify`, `watcher_darwin.go` uses `kqueue`, `watcher_windows.go` uses `ReadDirectoryChangesW`. Go selects the right file based on `GOOS` automatically.

**Snippet**:
```go
// File: signal_unix.go
//go:build linux || darwin || freebsd

package main

import (
    "os/signal"
    "syscall"
)

func listenForSignals() {
    ch := make(chan os.Signal, 1)
    signal.Notify(ch, syscall.SIGTERM, syscall.SIGINT)
    <-ch
}

// File: signal_windows.go
//go:build windows

package main

func listenForSignals() {
    // Windows-specific implementation
}

// Custom tags: go build -tags integration
//go:build integration
```

**Example**: [build_tags.go](../../examples/go/advanced/build_tags.go)

---

## unsafe Package

**Explanation**: The `unsafe` package bypasses Go's type system and memory safety guarantees. `unsafe.Pointer` converts between any pointer types. `unsafe.Sizeof` returns a type's size in bytes. It is used in performance-critical code (zero-copy string↔bytes conversion), CGo interop, and implementing low-level data structures. Incorrect use causes memory corruption — use only when absolutely necessary.

**Real-World Scenario**: High-performance JSON parsers (like `jsoniter`) use `unsafe.Pointer` to convert `[]byte` to `string` without copying — a safe operation when the string is not mutated, avoiding allocation in the hot path.

**Snippet**:
```go
import "unsafe"

// Zero-copy []byte to string conversion (read-only use only)
func bytesToString(b []byte) string {
    return *(*string)(unsafe.Pointer(&b))
}

// Inspect struct layout
type Point struct{ X, Y float32 }
p := Point{1.0, 2.0}
fmt.Println(unsafe.Sizeof(p))   // 8 bytes
fmt.Println(unsafe.Alignof(p))  // 4 bytes

// Access struct fields by offset
xPtr := (*float32)(unsafe.Pointer(&p))
yPtr := (*float32)(unsafe.Pointer(uintptr(unsafe.Pointer(&p)) + 4))
fmt.Println(*xPtr, *yPtr) // 1 2
```

**Example**: [unsafe_basics.go](../../examples/go/advanced/unsafe_basics.go)

---

## CGo — Calling C from Go

**Explanation**: CGo lets Go packages call C code and be called from C. Import `"C"` (a pseudo-package) to access C types and functions. CGo compiles the C code in comments above `import "C"` and links it. CGo crossings (Go→C, C→Go) are expensive — batch calls when possible. CGo disables some Go optimizations and complicates cross-compilation.

**Real-World Scenario**: Wrapping a high-performance C library (e.g., a hardware crypto accelerator or a legacy C database engine) for use in Go services — CGo provides the bridge without rewriting the C library.

**Snippet**:
```go
package main

/*
#include <stdlib.h>
#include <string.h>

char* repeat(const char* s, int n) {
    int len = strlen(s);
    char* result = malloc(len * n + 1);
    for (int i = 0; i < n; i++) {
        memcpy(result + i * len, s, len);
    }
    result[len * n] = '\0';
    return result;
}
*/
import "C"
import "unsafe"

func Repeat(s string, n int) string {
    cs := C.CString(s)
    defer C.free(unsafe.Pointer(cs))
    result := C.repeat(cs, C.int(n))
    defer C.free(unsafe.Pointer(result))
    return C.GoString(result)
}
```

**Example**: [cgo_basics.go](../../examples/go/advanced/cgo_basics.go)

---

## Profile-Guided Optimization (PGO)

**Explanation**: Introduced in Go 1.20 and enabled by default in 1.21, PGO optimizes compiled code based on a production CPU profile. Provide a `default.pgo` file alongside your `main` package, and `go build` automatically applies inlining and other optimizations to hot paths — typically yielding 2–10% throughput improvements with zero code changes.

**Real-World Scenario**: After profiling a high-traffic API server, you collect a `cpu.pprof` profile during peak load, rename it to `default.pgo`, commit it to the repo, and rebuild. Future releases automatically optimize the same hot paths without any manual annotation.

**Snippet**:
```bash
# Step 1: collect a CPU profile in production
curl -s http://localhost:6060/debug/pprof/profile?seconds=30 > cpu.pprof

# Step 2: copy to default.pgo in the main package directory
cp cpu.pprof cmd/server/default.pgo

# Step 3: rebuild — PGO is applied automatically
go build ./cmd/server

# Step 4: verify PGO was used
go build -pgo=auto -v ./cmd/server 2>&1 | grep pgo
```

**Example**: [pgo_setup.go](../../examples/go/advanced/pgo_setup.go)

---

## go:generate — Code Generation

**Explanation**: `//go:generate command args` is a directive that `go generate` executes. It runs arbitrary commands — typically to generate code from schemas, mocks, stringer implementations, or protobuf definitions. The generated files are committed to the repo and regenerated when the source changes. Common tools: `stringer`, `mockgen`, `protoc-gen-go`, `sqlc`.

**Real-World Scenario**: An enum type `Status` with values `Active`, `Inactive`, `Pending` needs a `String()` method for logging. Instead of writing it manually, `//go:generate stringer -type=Status` generates `status_string.go` automatically — update the enum, re-run `go generate`, done.

**Snippet**:
```go
//go:generate stringer -type=Status
//go:generate mockgen -source=service.go -destination=mock_service.go

package main

type Status int

const (
    Active Status = iota
    Inactive
    Pending
)

// After go:generate runs, a status_string.go file is created with:
// func (s Status) String() string { return [Active Inactive Pending][s] }

func main() {
    s := Active
    fmt.Println(s) // Active  (uses generated String() method)
}
```

**Example**: [go_generate.go](../../examples/go/advanced/go_generate.go)

---

## The Go Memory Model

**Explanation**: The Go Memory Model specifies when a write by one goroutine is guaranteed to be visible to a read in another. The core rule: if you do not synchronize, you have no guarantee. Synchronization is established by channels (a send happens-before the corresponding receive completes), by mutexes (an `Unlock` happens-before a later `Lock`), by `sync.Once`, and by `sync/atomic`. The model exists so the compiler and CPU are free to reorder unsynchronized operations for speed.

**Real-World Scenario**: A goroutine sets a `ready` boolean and another goroutine spins waiting for it. Without synchronization the waiting goroutine may *never* observe the write — the compiler can hoist the read out of the loop, or the CPU can cache a stale value. Using a channel or `atomic.Bool` establishes the happens-before edge that makes the write visible.

**Snippet**:
```go
// BROKEN — data race, no happens-before relationship
var ready bool
var data string
func setup() { data = "loaded"; ready = true }   // writes may be reordered
func wait()  { for !ready {}; print(data) }       // may see "" or never exit

// CORRECT — the channel send/receive synchronizes both writes
var done = make(chan struct{})
func setupOK() {
    data = "loaded"
    close(done) // send happens-before receive
}
func waitOK() {
    <-done       // after this, data's write is guaranteed visible
    print(data)  // always "loaded"
}
```

**Example**: [memory_model.go](../../examples/go/advanced/memory_model.go)

---

## Escape Analysis

**Explanation**: Escape analysis is a compile-time pass that decides whether a value lives on the stack (cheap, freed automatically when the function returns) or escapes to the heap (managed by the garbage collector). A value escapes when its lifetime outlives the function — typically when its address is returned, stored in a longer-lived structure, or captured by a closure that outlives the call. `go build -gcflags='-m'` prints each decision.

**Real-World Scenario**: A hot function allocates a small struct per call. Profiling shows GC pressure. Running with `-gcflags='-m'` reveals the struct "escapes to heap" because its pointer is returned. Refactoring to return the struct by value (not by pointer) keeps it on the stack and eliminates the allocation.

**Snippet**:
```go
// Inspect with: go build -gcflags='-m' escape_analysis.go

// Does NOT escape — value stays on the stack
func sumLocal() int {
    x := [3]int{1, 2, 3} // "does not escape"
    return x[0] + x[1] + x[2]
}

// ESCAPES — the pointer outlives the function, so n moves to the heap
func newCounter() *int {
    n := 0    // "moved to heap: n"
    return &n
}

// ESCAPES — captured by a returned closure
func adder() func(int) int {
    sum := 0           // "moved to heap: sum"
    return func(x int) int { sum += x; return sum }
}
```

**Example**: [escape_analysis.go](../../examples/go/advanced/escape_analysis.go)

---

## Struct Tags in Depth

**Explanation**: A struct tag is a raw string literal after a field, holding metadata read at runtime via reflection. By convention it's a space-separated list of `key:"value"` pairs — `json`, `xml`, `db`, `validate`, and others each claim a key. Libraries call `reflect.StructField.Tag.Get("key")` to read their slice. Tags are the backbone of Go's declarative serialization and validation.

**Real-World Scenario**: One `User` struct is persisted to a SQL database, serialized to a JSON API response, and validated on input. Three tag keys on each field — `db:"user_name"`, `json:"name"`, `validate:"required,min=2"` — let three independent libraries each map the field correctly, without three separate struct definitions.

**Snippet**:
```go
type User struct {
    ID    int    `json:"id" db:"user_id"`
    Name  string `json:"name" db:"user_name" validate:"required,min=2"`
    Email string `json:"email,omitempty" db:"email" validate:"email"`
    pass  string `json:"-"` // unexported + ignored by json
}

// Reading tags via reflection
t := reflect.TypeOf(User{})
field, _ := t.FieldByName("Name")
field.Tag.Get("json")     // "name"
field.Tag.Get("db")       // "user_name"
field.Tag.Get("validate") // "required,min=2"

// Lookup distinguishes "absent" from "empty"
value, ok := field.Tag.Lookup("xml") // "", false
```

**Example**: [struct_tags.go](../../examples/go/advanced/struct_tags.go)
