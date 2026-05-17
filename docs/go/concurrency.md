# Go — Concurrency

## Goroutines

**Explanation**: A goroutine is a lightweight, cooperatively-scheduled function execution managed by the Go runtime. Starting one costs roughly 2–8 KB of stack (vs. ~1 MB for an OS thread) and the runtime multiplexes thousands of goroutines onto a small pool of OS threads. `go f()` starts `f` concurrently — no callbacks, no futures, just a keyword.

**Real-World Scenario**: A web server handles each HTTP request in its own goroutine. The Go HTTP server does this automatically — `http.ListenAndServe` spawns a goroutine per connection. At peak load you might have 10,000 concurrent goroutines; the runtime schedules them efficiently without 10,000 OS threads.

**Snippet**:
```go
package main

import (
    "fmt"
    "time"
)

func worker(id int) {
    fmt.Printf("Worker %d starting\n", id)
    time.Sleep(100 * time.Millisecond) // simulate work
    fmt.Printf("Worker %d done\n", id)
}

func main() {
    for i := 1; i <= 5; i++ {
        go worker(i) // launch concurrently
    }
    time.Sleep(500 * time.Millisecond) // wait for workers (use sync.WaitGroup in real code)
}
```

**Example**: [goroutines.go](../../examples/go/concurrency/goroutines.go)

---

## Channels

**Explanation**: Channels are typed, goroutine-safe communication pipes. `make(chan T)` creates an unbuffered channel — a send blocks until a receiver is ready, and vice versa. `make(chan T, n)` creates a buffered channel that holds up to `n` values without blocking. The rule: *Do not communicate by sharing memory; share memory by communicating.*

**Real-World Scenario**: A pipeline where a producer goroutine sends URLs to a channel, and a pool of consumer goroutines reads from it to fetch and process each URL concurrently — without any mutex or shared state.

**Snippet**:
```go
// Unbuffered channel — synchronizes sender and receiver
ch := make(chan int)
go func() { ch <- 42 }() // sender blocks until receiver is ready
val := <-ch              // receiver blocks until sender sends
fmt.Println(val)         // 42

// Buffered channel — sender only blocks when buffer is full
buf := make(chan string, 3)
buf <- "a"
buf <- "b"
buf <- "c"
// buf <- "d" would block here

// Close signals no more values; range drains the channel
close(buf)
for s := range buf {
    fmt.Println(s) // a, b, c
}
```

**Example**: [channels.go](../../examples/go/concurrency/channels.go)

---

## Select

**Explanation**: `select` waits on multiple channel operations simultaneously, executing the first one that is ready. If multiple are ready, it picks one at random. A `default` case makes `select` non-blocking. `select` is the primary tool for timeouts, cancellation, and fan-in patterns.

**Real-World Scenario**: An API gateway calls two backend services concurrently and uses `select` with a timeout channel: whichever responds first wins; if neither responds within 500ms, the timeout case fires and the gateway returns a 503.

**Snippet**:
```go
func fetchWithTimeout(url string, timeout time.Duration) (string, error) {
    resultCh := make(chan string, 1)
    go func() {
        resultCh <- fetch(url) // assume fetch returns string
    }()

    select {
    case result := <-resultCh:
        return result, nil
    case <-time.After(timeout):
        return "", fmt.Errorf("timeout after %v", timeout)
    }
}
```

**Example**: [select.go](../../examples/go/concurrency/select.go)

---

## sync.WaitGroup

**Explanation**: `sync.WaitGroup` coordinates a set of goroutines: `Add(n)` registers n tasks, each goroutine calls `Done()` when finished, and `Wait()` blocks until the count reaches zero. It is the standard way to launch a batch of goroutines and wait for all of them to complete before proceeding.

**Real-World Scenario**: Processing a batch of images in parallel — launch one goroutine per image with `wg.Add(1)` and `go process(img)`, then `wg.Wait()` before writing the results to disk. The main goroutine doesn't proceed until all images are done.

**Snippet**:
```go
import "sync"

func processAll(items []string) {
    var wg sync.WaitGroup

    for _, item := range items {
        wg.Add(1)
        go func(item string) {
            defer wg.Done()
            process(item)
        }(item) // pass item to avoid closure capture (pre-Go1.22)
    }

    wg.Wait() // blocks until all goroutines call Done
    fmt.Println("all done")
}
```

**Example**: [waitgroup.go](../../examples/go/concurrency/waitgroup.go)

---

## sync.Mutex and sync.RWMutex

**Explanation**: When goroutines share mutable state (instead of communicating via channels), a mutex serializes access. `sync.Mutex` provides exclusive locking (`Lock`/`Unlock`). `sync.RWMutex` allows multiple concurrent readers OR one exclusive writer — use it when reads vastly outnumber writes.

**Real-World Scenario**: A concurrent cache stores results of expensive API calls. Multiple goroutines read from the cache simultaneously (RLock), but when a cache miss triggers a fill, one goroutine holds the write lock (Lock) while others wait — preventing duplicate fetches and data races.

**Snippet**:
```go
type SafeCounter struct {
    mu    sync.Mutex
    count int
}

func (c *SafeCounter) Inc() {
    c.mu.Lock()
    defer c.mu.Unlock()
    c.count++
}

func (c *SafeCounter) Value() int {
    c.mu.Lock()
    defer c.mu.Unlock()
    return c.count
}

// RWMutex for read-heavy cache
type Cache struct {
    mu   sync.RWMutex
    data map[string]string
}

func (c *Cache) Get(key string) (string, bool) {
    c.mu.RLock()         // multiple readers allowed simultaneously
    defer c.mu.RUnlock()
    v, ok := c.data[key]
    return v, ok
}
```

**Example**: [mutex.go](../../examples/go/concurrency/mutex.go)

---

## context.Context

**Explanation**: The `context` package propagates deadlines, cancellation signals, and request-scoped values across goroutines and API boundaries. `context.WithTimeout` and `context.WithCancel` return a derived context and a cancel function. When the context is cancelled (or times out), all operations using it receive a `ctx.Done()` signal and should clean up and return.

**Real-World Scenario**: An HTTP handler creates a context with a 5-second deadline: `ctx, cancel := context.WithTimeout(r.Context(), 5*time.Second)`. It passes `ctx` to a database query and an external API call. If either takes longer than 5 seconds (or the client disconnects), both are cancelled automatically — no goroutine leaks.

**Snippet**:
```go
func fetchData(ctx context.Context, url string) ([]byte, error) {
    req, err := http.NewRequestWithContext(ctx, "GET", url, nil)
    if err != nil {
        return nil, err
    }
    resp, err := http.DefaultClient.Do(req)
    if err != nil {
        return nil, err // includes context.DeadlineExceeded or context.Canceled
    }
    defer resp.Body.Close()
    return io.ReadAll(resp.Body)
}

// Caller
ctx, cancel := context.WithTimeout(context.Background(), 3*time.Second)
defer cancel() // always cancel to release resources
data, err := fetchData(ctx, "https://api.example.com/data")
```

**Example**: [context.go](../../examples/go/concurrency/context.go)

---

## Worker Pools

**Explanation**: A worker pool limits concurrency: instead of launching one goroutine per task (which can overwhelm resources), a fixed number of worker goroutines read from a shared task channel. This pattern controls memory usage and prevents thundering herds when processing large batches.

**Real-World Scenario**: Sending 100,000 emails: launching 100,000 goroutines simultaneously would exhaust connection pool limits. A pool of 20 worker goroutines reads email tasks from a channel, staying within the connection limit while processing all emails.

**Snippet**:
```go
func workerPool(tasks []Task, numWorkers int) []Result {
    taskCh := make(chan Task, len(tasks))
    resultCh := make(chan Result, len(tasks))

    // Start fixed pool of workers
    var wg sync.WaitGroup
    for i := 0; i < numWorkers; i++ {
        wg.Add(1)
        go func() {
            defer wg.Done()
            for task := range taskCh {
                resultCh <- process(task)
            }
        }()
    }

    // Send all tasks
    for _, t := range tasks {
        taskCh <- t
    }
    close(taskCh) // signals workers: no more tasks

    // Wait for workers, then close results
    go func() { wg.Wait(); close(resultCh) }()

    var results []Result
    for r := range resultCh {
        results = append(results, r)
    }
    return results
}
```

**Example**: [worker_pool.go](../../examples/go/concurrency/worker_pool.go)

---

## sync/atomic

**Explanation**: The `sync/atomic` package provides lock-free, hardware-atomic operations on primitive types (`int32`, `int64`, `uint64`, `Pointer`, etc.). Atomic operations are faster than mutexes for simple counters or flags because they use CPU instructions (CAS, fetch-and-add) rather than OS-level locking.

**Real-World Scenario**: A metrics collector increments a request counter from thousands of goroutines. Using `atomic.AddInt64(&requests, 1)` is 3–10× faster than a mutex-protected increment and avoids contention.

**Snippet**:
```go
import "sync/atomic"

var requests atomic.Int64 // zero value is valid

func handleRequest() {
    requests.Add(1)
    // ... handle request
}

func stats() {
    fmt.Printf("Total requests: %d\n", requests.Load())
}

// Atomic compare-and-swap (CAS) — update only if current value matches expected
var flag atomic.Bool
if flag.CompareAndSwap(false, true) {
    fmt.Println("acquired flag")
}
```

**Example**: [atomic.go](../../examples/go/concurrency/atomic.go)

---

## Pipelines

**Explanation**: A pipeline is a series of stages connected by channels, where each stage receives values from upstream, transforms them, and sends to downstream. Pipelines make concurrent data processing composable and readable. `done` channels (or `context.Context`) propagate cancellation through the pipeline.

**Real-World Scenario**: An ETL pipeline: `readCSV` → `parseRows` → `validateRows` → `writeToDatabase`. Each stage runs in its own goroutine, stages communicate via channels, and the pipeline processes records as a stream without loading everything into memory.

**Snippet**:
```go
// Stage 1: generate integers
func generate(nums ...int) <-chan int {
    out := make(chan int)
    go func() {
        for _, n := range nums {
            out <- n
        }
        close(out)
    }()
    return out
}

// Stage 2: square each integer
func square(in <-chan int) <-chan int {
    out := make(chan int)
    go func() {
        for n := range in {
            out <- n * n
        }
        close(out)
    }()
    return out
}

// Wire stages together
func main() {
    for n := range square(generate(2, 3, 4)) {
        fmt.Println(n) // 4, 9, 16
    }
}
```

**Example**: [pipelines.go](../../examples/go/concurrency/pipelines.go)

---

## sync.Once

**Explanation**: `sync.Once` guarantees a function runs exactly once, no matter how many goroutines call it or how often. The first call to `once.Do(f)` runs `f`; every later call blocks until that first run completes, then returns immediately without re-running. It is the idiomatic, race-free way to do lazy one-time initialization.

**Real-World Scenario**: A package exposes a shared database connection pool. The pool is expensive to create, so it's built lazily on first use. Wrapping the construction in `sync.Once` ensures that even if 100 goroutines call `GetPool()` simultaneously at startup, the pool is created exactly once.

**Snippet**:
```go
import "sync"

var (
    once     sync.Once
    instance *Database
)

func GetDatabase() *Database {
    once.Do(func() {
        // Runs exactly once, even under concurrent calls
        instance = connectToDatabase()
    })
    return instance
}
```

**Example**: [once.go](../../examples/go/concurrency/once.go)

---

## sync.Pool

**Explanation**: `sync.Pool` is a cache of temporary objects that can be reused to relieve pressure on the garbage collector. `Get` returns an object (creating one via the `New` func if the pool is empty); `Put` returns it for reuse. The pool may drop its contents at any time — never store anything that must persist.

**Real-World Scenario**: A high-throughput JSON API allocates a `bytes.Buffer` per request to build the response. Under load that's thousands of short-lived allocations per second. A `sync.Pool` of buffers recycles them across requests, cutting GC pauses and allocation cost dramatically.

**Snippet**:
```go
import (
    "bytes"
    "sync"
)

var bufPool = sync.Pool{
    New: func() any { return new(bytes.Buffer) },
}

func handle() {
    buf := bufPool.Get().(*bytes.Buffer)
    buf.Reset()              // always reset reused objects
    defer bufPool.Put(buf)   // return it for the next caller

    buf.WriteString("response body")
    // ... use buf ...
}
```

**Example**: [pool.go](../../examples/go/concurrency/pool.go)

---

## Channel Direction

**Explanation**: A channel type can be restricted to send-only (`chan<- T`) or receive-only (`<-chan T`). A bidirectional `chan T` converts implicitly to either restricted form, but not the reverse. Declaring direction in function signatures documents intent and lets the compiler catch misuse — a producer can't accidentally read, a consumer can't accidentally write.

**Real-World Scenario**: In a producer/consumer pipeline, the `producer` function takes a `chan<- Job` (it may only send) and the `worker` function takes a `<-chan Job` (it may only receive). The restriction is enforced at compile time, making the data-flow direction obvious and tamper-proof.

**Snippet**:
```go
// Send-only parameter — function may only write
func produce(out chan<- int) {
    for i := 0; i < 3; i++ {
        out <- i
    }
    close(out)
}

// Receive-only parameter — function may only read
func consume(in <-chan int) {
    for v := range in {
        fmt.Println(v)
    }
}

ch := make(chan int)   // bidirectional
go produce(ch)         // passed as chan<- int
consume(ch)            // passed as <-chan int
```

**Example**: [channel_direction.go](../../examples/go/concurrency/channel_direction.go)

---

## The Race Detector

**Explanation**: A data race occurs when two goroutines access the same memory concurrently and at least one writes, with no synchronization. Go ships a built-in race detector enabled with the `-race` flag (`go run -race`, `go test -race`, `go build -race`). It instruments memory accesses and reports the conflicting goroutines, stacks, and addresses at runtime.

**Real-World Scenario**: A test passes locally but fails intermittently in CI. Running the test suite with `go test -race ./...` reveals that two goroutines mutate a shared map without a mutex — the detector pinpoints the exact lines, turning a heisenbug into a one-line fix (`sync.Mutex` or a channel).

**Snippet**:
```go
// This code has a data race — run with: go run -race race_detector.go
var counter int

func main() {
    var wg sync.WaitGroup
    for i := 0; i < 100; i++ {
        wg.Add(1)
        go func() {
            defer wg.Done()
            counter++ // RACE: unsynchronized write
        }()
    }
    wg.Wait()
}

// The fix: protect counter with sync.Mutex or use atomic.Int64.
// Always run tests with -race in CI to catch races early.
```

**Example**: [race_detector.go](../../examples/go/concurrency/race_detector.go)
