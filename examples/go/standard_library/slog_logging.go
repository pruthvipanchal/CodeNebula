// Compile: go run slog_logging.go
// Output (JSON lines, time will vary):
//   {"time":"...","level":"INFO","msg":"server started","port":8080}
//   {"time":"...","level":"INFO","msg":"request","method":"GET","path":"/api"}
//   {"time":"...","level":"ERROR","msg":"failed","request_id":"req-1","error":"timeout"}
package main

import (
	"log/slog"
	"os"
)

func main() {
	logger := slog.New(slog.NewJSONHandler(os.Stdout, nil))

	logger.Info("server started", "port", 8080)
	logger.Info("request", "method", "GET", "path", "/api")

	// Logger with persistent attributes
	reqLogger := logger.With("request_id", "req-1")
	reqLogger.Error("failed", "error", "timeout")
}
