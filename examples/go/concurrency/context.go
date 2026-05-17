// Compile: go run context.go
// Output:
//   fetching with 2s timeout...
//   (result or "context deadline exceeded")
package main

import (
	"context"
	"fmt"
	"io"
	"net/http"
	"time"
)

func fetchData(ctx context.Context, url string) (string, error) {
	req, err := http.NewRequestWithContext(ctx, "GET", url, nil)
	if err != nil {
		return "", err
	}
	resp, err := http.DefaultClient.Do(req)
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()
	body, _ := io.ReadAll(resp.Body)
	return fmt.Sprintf("status=%d bytes=%d", resp.StatusCode, len(body)), nil
}

func main() {
	fmt.Println("fetching with 2s timeout...")
	ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
	defer cancel()

	result, err := fetchData(ctx, "https://httpbin.org/get")
	if err != nil {
		fmt.Println("error:", err)
		return
	}
	fmt.Println(result)
}
