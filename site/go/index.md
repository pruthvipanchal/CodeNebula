---
title: "Go — Language Overview"
description: "Go concepts organized by topic — history, core language, concurrency, standard library, and advanced features."
---

# Go — Language Overview

Go (also known as Golang) is an open-source, statically typed, compiled language designed for simplicity, safety, and scalability. Created at Google in 2007 and open-sourced in 2009, Go has become the language of cloud-native infrastructure.

## Browse by Topic

<div class="go-topics-grid">
  <a href="./history" class="topic-card">
    <div class="topic-icon">📜</div>
    <div class="topic-label">History & Evolution</div>
    <div class="topic-desc">Origins at Google, Go 1.0, modules, generics, and modern Go</div>
  </a>
  <a href="./core" class="topic-card">
    <div class="topic-icon">🔧</div>
    <div class="topic-label">Core Language</div>
    <div class="topic-desc">Variables, types, functions, structs, interfaces, closures, and embedding</div>
  </a>
  <a href="./concurrency" class="topic-card">
    <div class="topic-icon">⚡</div>
    <div class="topic-label">Concurrency</div>
    <div class="topic-desc">Goroutines, channels, select, WaitGroup, Mutex, context, and pipelines</div>
  </a>
  <a href="./stdlib" class="topic-card">
    <div class="topic-icon">📦</div>
    <div class="topic-label">Standard Library</div>
    <div class="topic-desc">fmt, errors, io, os, net/http, encoding/json, bufio, slog, testing, and more</div>
  </a>
  <a href="./advanced" class="topic-card">
    <div class="topic-icon">🚀</div>
    <div class="topic-label">Advanced</div>
    <div class="topic-desc">Generics, reflection, interface composition, unsafe, CGo, PGO, and go:generate</div>
  </a>
</div>

## Why Go?

| Feature | Go's Approach |
|---------|--------------|
| Concurrency | Goroutines + channels — lightweight, built into the language |
| Error handling | Explicit `(value, error)` returns — no hidden exceptions |
| Compilation | Fast: large codebases compile in seconds |
| Deployment | Single static binary — no runtime dependencies |
| Formatting | `gofmt` — one canonical style, no debates |
| Tooling | `go test`, `go vet`, `go doc` — all built in |

## Navigation

| Topic | Description |
|-------|-------------|
| [📜 History & Evolution](/go/history) | Why Go was created, evolution, and adoption |
| [🔧 Core Language](/go/core) | The fundamental language features |
| [⚡ Concurrency](/go/concurrency) | Go's signature concurrency model |
| [📦 Standard Library](/go/stdlib) | Production-ready packages included with every install |
| [🚀 Advanced](/go/advanced) | Generics, reflection, CGo, and more |
