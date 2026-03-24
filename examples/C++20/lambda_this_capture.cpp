// CodeNebula - C++20 Example: Lambda [*this] Capture
// Compile: g++ -std=c++20 -Wall -Wextra -o example lambda_this_capture.cpp

// Demonstrates capturing *this by value in lambdas. This copies the entire
// object into the lambda closure, making it safe to use even after the
// original object is destroyed.

#include <iostream>
#include <string>
#include <functional>
#include <vector>

// ------------------------------------------------------------------
// 1. Basic [*this] vs [this] capture
// ------------------------------------------------------------------
class Counter {
    int count_ = 0;
    std::string name_;

public:
    Counter(std::string name, int start)
        : count_(start), name_(std::move(name)) {}

    // Captures pointer to this - dangerous if object is destroyed
    auto get_ref_lambda() {
        return [this]() {
            return name_ + ": " + std::to_string(count_);
        };
    }

    // Captures a COPY of *this - safe even after object destruction
    auto get_copy_lambda() {
        return [*this]() {
            return name_ + ": " + std::to_string(count_);
        };
    }

    // [*this] capture with mutation (must be mutable)
    auto get_increment_lambda() {
        return [*this]() mutable {
            ++count_;
            return name_ + ": " + std::to_string(count_);
        };
    }

    void increment() { ++count_; }
    int count() const { return count_; }
};

// ------------------------------------------------------------------
// 2. [*this] in async-like scenarios
// ------------------------------------------------------------------
class Sensor {
    std::string id_;
    double reading_;

public:
    Sensor(std::string id, double reading)
        : id_(std::move(id)), reading_(reading) {}

    // Returns a callback that holds a copy of the sensor state
    auto snapshot_callback() {
        return [*this]() {
            std::cout << "  Sensor " << id_ << " snapshot: "
                      << reading_ << std::endl;
        };
    }

    void update(double val) { reading_ = val; }
};

// ------------------------------------------------------------------
// 3. Class with [*this] in method that returns stored lambdas
// ------------------------------------------------------------------
class Logger {
    std::string prefix_;
    int level_;

public:
    Logger(std::string prefix, int level)
        : prefix_(std::move(prefix)), level_(level) {}

    auto make_log_fn() const {
        return [*this](const std::string& msg) {
            if (level_ > 0)
                std::cout << "  [" << prefix_ << "] " << msg << std::endl;
        };
    }
};

int main()
{
    std::cout << "=== [*this] vs [this] ===" << std::endl;

    std::function<std::string()> copy_fn;
    {
        Counter c("Alpha", 10);
        copy_fn = c.get_copy_lambda();
        c.increment();
        c.increment();
        // copy_fn captured *this at count_=10, unaffected by increments
    }
    // Object c is destroyed here, but copy_fn is safe
    std::cout << "  Copy lambda (after destroy): " << copy_fn() << std::endl;

    std::cout << "\n=== Mutable [*this] ===" << std::endl;
    Counter c2("Beta", 0);
    auto inc_fn = c2.get_increment_lambda();
    std::cout << "  " << inc_fn() << std::endl;  // copy's count: 1
    std::cout << "  " << inc_fn() << std::endl;  // copy's count: 2
    std::cout << "  " << inc_fn() << std::endl;  // copy's count: 3
    std::cout << "  Original count: " << c2.count() << std::endl;  // still 0

    std::cout << "\n=== Snapshot Callbacks ===" << std::endl;
    Sensor temp("TEMP-01", 22.5);
    auto snap1 = temp.snapshot_callback();

    temp.update(25.0);
    auto snap2 = temp.snapshot_callback();

    temp.update(30.0);

    std::cout << "  After all updates:" << std::endl;
    snap1();  // Shows 22.5
    snap2();  // Shows 25.0

    std::cout << "\n=== Logger with [*this] ===" << std::endl;
    auto log_fn = Logger("APP", 1).make_log_fn();
    // Logger temporary is destroyed, but log_fn holds a copy
    log_fn("Server started");
    log_fn("Accepting connections");

    auto silent_fn = Logger("SILENT", 0).make_log_fn();
    silent_fn("This won't print");
    std::cout << "  (silent logger produced no output)" << std::endl;

    return 0;
}

/*
Expected output:

=== [*this] vs [this] ===
  Copy lambda (after destroy): Alpha: 10

=== Mutable [*this] ===
  Beta: 1
  Beta: 2
  Beta: 3
  Original count: 0

=== Snapshot Callbacks ===
  After all updates:
  Sensor TEMP-01 snapshot: 22.5
  Sensor TEMP-01 snapshot: 25

=== Logger with [*this] ===
  [APP] Server started
  [APP] Accepting connections
  (silent logger produced no output)
*/
