# Go — Standard Library

## fmt — Formatted I/O

**Explanation**: The `fmt` package implements formatted I/O. `fmt.Printf` writes formatted text to stdout; `fmt.Sprintf` returns it as a string. Go's format verbs: `%v` (default value), `%+v` (struct with field names), `%#v` (Go syntax), `%T` (type), `%d` (integer), `%s` (string), `%q` (quoted string), `%x` (hex), `%f` (float), `%p` (pointer).

**Real-World Scenario**: Logging a request: `log.Printf("method=%s path=%s status=%d latency=%v", r.Method, r.URL.Path, status, time.Since(start))` — structured key=value pairs with mixed verb types in one call.

**Snippet**:
```go
import "fmt"

type User struct{ Name string; Age int }
u := User{"Alice", 30}

fmt.Printf("%v\n",  u)   // {Alice 30}
fmt.Printf("%+v\n", u)   // {Name:Alice Age:30}
fmt.Printf("%#v\n", u)   // main.User{Name:"Alice", Age:30}
fmt.Printf("%T\n",  u)   // main.User

// Errorf wraps errors with context
err := fmt.Errorf("load user %d: %w", 42, ErrNotFound)

// Sscanf parses formatted input
var name string; var age int
fmt.Sscanf("Alice 30", "%s %d", &name, &age)
```

**Example**: [fmt_basics.go](../../examples/go/standard_library/fmt_basics.go)

---

## errors — Error Handling Utilities

**Explanation**: The `errors` package provides `errors.New` (create a sentinel error), `errors.Is` (check error identity through a chain of wrapped errors), and `errors.As` (extract a specific error type from a chain). Together with `fmt.Errorf("%w", err)`, they form Go's structured error handling system.

**Real-World Scenario**: A storage layer returns a typed `*NotFoundError`. A service layer wraps it with context: `fmt.Errorf("getUser: %w", storageErr)`. The HTTP handler unwraps with `errors.As(err, &notFound)` to decide whether to return 404 or 500.

**Snippet**:
```go
import "errors"

var ErrNotFound = errors.New("not found")

type ValidationError struct{ Field string; Msg string }
func (e *ValidationError) Error() string {
    return fmt.Sprintf("validation: %s %s", e.Field, e.Msg)
}

err := fmt.Errorf("user lookup: %w", ErrNotFound)

errors.Is(err, ErrNotFound) // true — unwraps chain

var ve *ValidationError
if errors.As(err, &ve) {
    fmt.Println("bad field:", ve.Field) // type-safe access
}
```

**Example**: [errors_pkg.go](../../examples/go/standard_library/errors_pkg.go)

---

## io — I/O Primitives

**Explanation**: The `io` package defines the fundamental I/O interfaces: `io.Reader` (`Read([]byte) (int, error)`), `io.Writer` (`Write([]byte) (int, error)`), `io.Closer`, `io.Seeker`, and their combinations (`io.ReadWriter`, `io.ReadCloser`, etc.). `io.Copy` streams from any Reader to any Writer. `io.ReadAll` reads everything into memory. `io.LimitReader` caps the bytes read.

**Real-World Scenario**: Proxying an HTTP response body to a file: `io.Copy(file, response.Body)` streams the data without loading it all into memory — critical for large file downloads.

**Snippet**:
```go
import "io"

// Stream from reader to writer
n, err := io.Copy(dst, src) // returns bytes copied

// Read everything (use only when size is bounded)
data, err := io.ReadAll(r)

// Limit reader to prevent oversized inputs
limited := io.LimitReader(r, 1<<20) // max 1 MB
data, err = io.ReadAll(limited)

// MultiWriter — write to multiple destinations simultaneously
multi := io.MultiWriter(file, os.Stdout)
fmt.Fprintln(multi, "goes to both")
```

**Example**: [io_basics.go](../../examples/go/standard_library/io_basics.go)

---

## os — Operating System Interface

**Explanation**: The `os` package provides OS-level operations: file I/O, environment variables, process control, and working directory. `os.Open` opens for reading; `os.Create` opens for writing (truncating). `os.ReadFile` and `os.WriteFile` are convenience wrappers for small files. `os.Args` holds command-line arguments; `os.Getenv` reads environment variables.

**Real-World Scenario**: Reading a config file at startup: `data, err := os.ReadFile("/etc/myapp/config.json")`. If `MYAPP_CONFIG` env var is set, use that path: `path := os.Getenv("MYAPP_CONFIG")`.

**Snippet**:
```go
import "os"

// Read entire small file
data, err := os.ReadFile("config.json")

// Write file (creates or truncates)
err = os.WriteFile("output.txt", []byte("hello\n"), 0644)

// Open for streaming large file
f, err := os.Open("large.bin")
if err != nil { log.Fatal(err) }
defer f.Close()

// Environment
home := os.Getenv("HOME")
port, ok := os.LookupEnv("PORT") // distinguish missing vs empty

// Exit with status code
os.Exit(1)
```

**Example**: [os_basics.go](../../examples/go/standard_library/os_basics.go)

---

## net/http — HTTP Client and Server

**Explanation**: `net/http` is a production-grade HTTP/1.1 and HTTP/2 library in the standard library. `http.ListenAndServe` starts a server; `http.HandleFunc` registers routes. The `http.Client` makes HTTP requests with full control over timeouts, redirects, and TLS. Always set timeouts on production clients — the zero-value `http.DefaultClient` has no timeouts.

**Real-World Scenario**: Microservices written in Go use `net/http` directly (no framework) for simple APIs. A service adds authentication middleware by wrapping `http.Handler` — the composition pattern means no magic, just function calls.

**Snippet**:
```go
// Server
http.HandleFunc("/health", func(w http.ResponseWriter, r *http.Request) {
    w.Header().Set("Content-Type", "application/json")
    w.WriteHeader(http.StatusOK)
    fmt.Fprintln(w, `{"status":"ok"}`)
})
log.Fatal(http.ListenAndServe(":8080", nil))

// Client with timeout (always set in production)
client := &http.Client{Timeout: 10 * time.Second}
resp, err := client.Get("https://api.example.com/users")
if err != nil { return err }
defer resp.Body.Close()
body, _ := io.ReadAll(resp.Body)
```

**Example**: [http_server.go](../../examples/go/standard_library/http_server.go)

---

## encoding/json — JSON Marshal/Unmarshal

**Explanation**: `encoding/json` serializes Go values to JSON (`json.Marshal`) and deserializes JSON to Go values (`json.Unmarshal`). Struct fields are controlled with `json:` struct tags: `json:"name"` sets the key name, `json:"name,omitempty"` omits zero values, `json:"-"` excludes a field. `json.NewEncoder`/`json.NewDecoder` stream JSON to/from an `io.Writer`/`io.Reader`.

**Real-World Scenario**: An API handler decodes a JSON request body into a struct, validates it, and encodes a response: `json.NewDecoder(r.Body).Decode(&req)` / `json.NewEncoder(w).Encode(resp)` — no buffering the whole body into memory.

**Snippet**:
```go
type Person struct {
    Name    string `json:"name"`
    Age     int    `json:"age"`
    Email   string `json:"email,omitempty"` // omit if empty
    Password string `json:"-"`              // never marshal
}

p := Person{Name: "Alice", Age: 30}
data, err := json.Marshal(p)
// {"name":"Alice","age":30}

var p2 Person
err = json.Unmarshal(data, &p2)

// Streaming decode from HTTP body
var req Request
if err := json.NewDecoder(r.Body).Decode(&req); err != nil {
    http.Error(w, "bad JSON", 400)
    return
}
```

**Example**: [json_encode.go](../../examples/go/standard_library/json_encode.go)

---

## bufio — Buffered I/O

**Explanation**: `bufio.Scanner` reads input line-by-line (or by custom split functions). `bufio.Reader` adds buffering to any `io.Reader`, reducing system calls. `bufio.Writer` buffers writes and flushes in larger chunks. Essential for performance when reading or writing many small pieces of data.

**Real-World Scenario**: Reading a 10 GB log file line by line: `bufio.Scanner` reads chunks (default 64KB) from the OS and splits on newlines, keeping only one line in memory at a time — far more efficient than `io.ReadAll`.

**Snippet**:
```go
import (
    "bufio"
    "os"
)

// Read a file line by line
f, _ := os.Open("large.log")
defer f.Close()

scanner := bufio.NewScanner(f)
for scanner.Scan() {
    line := scanner.Text()
    process(line)
}
if err := scanner.Err(); err != nil {
    log.Fatal(err)
}

// Buffered writer — flush at the end
bw := bufio.NewWriter(os.Stdout)
defer bw.Flush()
fmt.Fprintln(bw, "buffered output")
```

**Example**: [bufio_scanner.go](../../examples/go/standard_library/bufio_scanner.go)

---

## log/slog — Structured Logging (Go 1.21+)

**Explanation**: `log/slog`, added in Go 1.21, provides structured logging with key-value pairs. Logs can be emitted as human-readable text or machine-readable JSON. `slog.Info("message", "key", value)` is the idiomatic call. Custom handlers can route logs to any backend (stdout, file, observability platform).

**Real-World Scenario**: In production microservices, JSON logs are ingested by log aggregators (Datadog, Loki, Elasticsearch). `slog` with `JSONHandler` produces `{"time":"...","level":"INFO","msg":"request","method":"GET","path":"/api/users","latency_ms":42}` — indexable and filterable without custom parsing.

**Snippet**:
```go
import "log/slog"

// Default text handler (human readable)
slog.Info("server started", "port", 8080)
// time=2024-01-15T10:00:00Z level=INFO msg="server started" port=8080

// JSON handler for production
logger := slog.New(slog.NewJSONHandler(os.Stdout, nil))
logger.Info("request",
    "method", r.Method,
    "path", r.URL.Path,
    "status", 200,
    "latency_ms", latency.Milliseconds(),
)

// Logger with persistent attributes
reqLogger := logger.With("request_id", reqID, "user_id", userID)
reqLogger.Info("processing")
reqLogger.Error("failed", "error", err)
```

**Example**: [slog_logging.go](../../examples/go/standard_library/slog_logging.go)

---

## testing — Unit Tests and Benchmarks

**Explanation**: Go's built-in testing package requires no third-party dependencies. Test files end in `_test.go`, test functions start with `Test`, benchmark functions with `Benchmark`. `t.Fatal` / `t.Error` report failures. Table-driven tests (`t.Run`) group related cases. `go test ./...` runs all tests; `-bench=.` runs benchmarks; `-race` enables the race detector.

**Real-World Scenario**: Testing a JSON parser with table-driven tests: define a slice of `{input, expected, wantErr}` cases, loop over them with `t.Run(name, func(t *testing.T){...})`, and get one test name per case in the output — easy to identify which input failed.

**Snippet**:
```go
func TestAdd(t *testing.T) {
    cases := []struct{
        a, b, want int
    }{
        {1, 2, 3},
        {0, 0, 0},
        {-1, 1, 0},
    }
    for _, tc := range cases {
        t.Run(fmt.Sprintf("%d+%d", tc.a, tc.b), func(t *testing.T) {
            got := Add(tc.a, tc.b)
            if got != tc.want {
                t.Errorf("got %d, want %d", got, tc.want)
            }
        })
    }
}

func BenchmarkAdd(b *testing.B) {
    for i := 0; i < b.N; i++ {
        Add(i, i+1)
    }
}
```

**Example**: [testing_basics.go](../../examples/go/standard_library/testing_basics.go)

---

## strings and strconv — String Operations

**Explanation**: The `strings` package provides string manipulation: `strings.Contains`, `strings.HasPrefix`, `strings.Split`, `strings.Join`, `strings.TrimSpace`, `strings.Replace`, `strings.Builder` (efficient concatenation). The `strconv` package converts between strings and primitive types: `strconv.Atoi`, `strconv.Itoa`, `strconv.ParseFloat`, `strconv.FormatBool`.

**Real-World Scenario**: Parsing a CSV line: `strings.Split(line, ",")` splits into fields; `strconv.Atoi(fields[2])` converts the third field to an integer with error handling — no regex needed for simple cases.

**Snippet**:
```go
import (
    "strings"
    "strconv"
)

s := "  Hello, World!  "
fmt.Println(strings.TrimSpace(s))          // "Hello, World!"
fmt.Println(strings.ToLower(s))            // "  hello, world!  "
fmt.Println(strings.Contains(s, "World"))  // true
parts := strings.Split("a,b,c", ",")       // ["a","b","c"]
joined := strings.Join(parts, " | ")       // "a | b | c"

// Efficient concatenation
var b strings.Builder
for _, p := range parts {
    b.WriteString(p)
}

// strconv
n, err := strconv.Atoi("42")       // string → int
s2 := strconv.Itoa(n)              // int → string
f, err := strconv.ParseFloat("3.14", 64)
```

**Example**: [strings_strconv.go](../../examples/go/standard_library/strings_strconv.go)

---

## time — Time and Duration

**Explanation**: The `time` package represents moments (`time.Time`) and durations (`time.Duration`). Durations are `int64` nanoseconds with constants: `time.Second`, `time.Millisecond`, etc. `time.Now()` returns the current time. `time.Since(t)` returns elapsed duration. `time.After(d)` returns a channel that receives after duration — used for timeouts. `time.Parse` and `t.Format` use a reference time layout (`2006-01-02 15:04:05`).

**Real-World Scenario**: Measuring API latency: `start := time.Now()` before the call, `latency := time.Since(start)` after. Log `latency.Milliseconds()` to a metrics system.

**Snippet**:
```go
import "time"

now := time.Now()
fmt.Println(now.Format("2006-01-02 15:04:05")) // Go's reference time

// Duration arithmetic
deadline := now.Add(30 * time.Second)
remaining := time.Until(deadline)

// Measure elapsed time
start := time.Now()
doWork()
elapsed := time.Since(start)
fmt.Printf("took %v\n", elapsed) // took 1.234ms

// Ticker — periodic events
ticker := time.NewTicker(1 * time.Second)
defer ticker.Stop()
for t := range ticker.C {
    fmt.Println("tick at", t)
}
```

**Example**: [time_basics.go](../../examples/go/standard_library/time_basics.go)

---

## sort and slices — Sorting

**Explanation**: The `sort` package sorts slices and user-defined collections. `sort.Ints`, `sort.Strings`, and `sort.Float64s` handle the common cases; `sort.Slice` sorts any slice with a custom less-function. Since Go 1.21 the generic `slices` package adds `slices.Sort`, `slices.SortFunc`, and `slices.BinarySearch` — type-safe and usually preferred in modern code.

**Real-World Scenario**: An API returns a list of products that must be displayed cheapest-first, then alphabetically for ties. `slices.SortFunc(products, func(a, b Product) int { ... })` expresses the multi-key comparison in one place.

**Snippet**:
```go
import (
    "sort"
    "slices"
)

nums := []int{3, 1, 4, 1, 5, 9}
sort.Ints(nums)            // [1 1 3 4 5 9]

// Custom comparison with sort.Slice
people := []Person{{"Bob", 30}, {"Al", 25}}
sort.Slice(people, func(i, j int) bool {
    return people[i].Age < people[j].Age
})

// Modern generic API (Go 1.21+)
slices.Sort(nums)
slices.SortFunc(people, func(a, b Person) int {
    return a.Age - b.Age
})
```

**Example**: [sort_pkg.go](../../examples/go/standard_library/sort_pkg.go)

---

## regexp — Regular Expressions

**Explanation**: The `regexp` package implements RE2-syntax regular expressions — a syntax with no catastrophic backtracking, so match time is linear in the input. `regexp.MustCompile` compiles a pattern once at startup (panicking on a bad pattern); the compiled `*Regexp` is safe for concurrent use. Methods cover matching, finding, extracting submatches, and replacing.

**Real-World Scenario**: A log parser extracts the timestamp, level, and message from each line. A single compiled regex with named capture groups pulls all three fields out per line, far more robust than manual string splitting.

**Snippet**:
```go
import "regexp"

// Compile once, reuse everywhere (safe for concurrent use)
var emailRe = regexp.MustCompile(`[\w.]+@[\w.]+\.\w+`)

emailRe.MatchString("contact me@site.com") // true
emailRe.FindString("ping a@b.io now")      // "a@b.io"
emailRe.FindAllString(text, -1)            // all matches

// Submatches with capture groups
re := regexp.MustCompile(`(\d{4})-(\d{2})-(\d{2})`)
m := re.FindStringSubmatch("2024-01-15")
// m = ["2024-01-15" "2024" "01" "15"]

re.ReplaceAllString("a1b2c3", "")          // "abc"
```

**Example**: [regexp_pkg.go](../../examples/go/standard_library/regexp_pkg.go)

---

## math and math/rand — Numbers

**Explanation**: The `math` package provides floating-point constants (`math.Pi`, `math.MaxInt64`) and functions (`Sqrt`, `Pow`, `Floor`, `Abs`, `Min`, `Max`). The `math/rand` package generates pseudo-random numbers; `math/rand/v2` (Go 1.22+) modernizes the API with better defaults and no global seeding required. For security-sensitive randomness, use `crypto/rand` instead.

**Real-World Scenario**: A simulation needs to model dice rolls and compute geometric distances. `rand.IntN(6)+1` rolls a die; `math.Hypot(dx, dy)` computes the Euclidean distance between two points without overflow.

**Snippet**:
```go
import (
    "math"
    "math/rand/v2"
)

math.Sqrt(144)        // 12
math.Pow(2, 10)       // 1024
math.Max(3.0, 7.0)    // 7
math.Abs(-4.5)        // 4.5
math.Pi               // 3.141592653589793

// math/rand/v2 — no manual seeding needed
rand.IntN(100)        // random int in [0, 100)
rand.Float64()        // random float in [0.0, 1.0)
```

**Example**: [math_pkg.go](../../examples/go/standard_library/math_pkg.go)

---

## flag — Command-Line Flags

**Explanation**: The `flag` package parses command-line arguments into typed values. `flag.String`, `flag.Int`, and `flag.Bool` declare flags with a name, default, and usage string, returning a pointer. `flag.Parse()` populates them from `os.Args`. It auto-generates `-h`/`--help` output and reports unknown flags.

**Real-World Scenario**: A CLI tool needs `--port`, `--verbose`, and `--config` options. Declaring them with `flag` gives typed values, default fallbacks, and a usage message for free — no manual `os.Args` parsing.

**Snippet**:
```go
import "flag"

func main() {
    port := flag.Int("port", 8080, "server port")
    verbose := flag.Bool("verbose", false, "enable verbose logging")
    config := flag.String("config", "config.json", "config file path")

    flag.Parse()

    fmt.Printf("port=%d verbose=%t config=%s\n",
        *port, *verbose, *config)

    // Non-flag args (e.g. positional file names)
    fmt.Println("remaining args:", flag.Args())
}
// Run: go run main.go -port 9000 -verbose
```

**Example**: [flag_pkg.go](../../examples/go/standard_library/flag_pkg.go)

---

## path/filepath — File Paths

**Explanation**: The `path/filepath` package manipulates file paths using the operating system's separator (`/` on Unix, `\` on Windows) — making path code portable. `filepath.Join` builds paths safely, `filepath.Base`/`Dir`/`Ext` split them apart, and `filepath.Walk`/`WalkDir` traverse directory trees. Use `path` (not `filepath`) only for URL-style slash paths.

**Real-World Scenario**: A build tool must find every `.go` file under a project directory, on both developer macOS laptops and Linux CI runners. `filepath.WalkDir` recursively visits each entry, and `filepath.Ext` filters by extension — identical behavior on every OS.

**Snippet**:
```go
import "path/filepath"

p := filepath.Join("data", "logs", "app.log")
// "data/logs/app.log" on Unix, "data\logs\app.log" on Windows

filepath.Base(p)   // "app.log"
filepath.Dir(p)    // "data/logs"
filepath.Ext(p)    // ".log"

// Walk a directory tree
filepath.WalkDir("src", func(path string, d os.DirEntry, err error) error {
    if err != nil {
        return err
    }
    if !d.IsDir() && filepath.Ext(path) == ".go" {
        fmt.Println(path)
    }
    return nil
})
```

**Example**: [filepath_pkg.go](../../examples/go/standard_library/filepath_pkg.go)
