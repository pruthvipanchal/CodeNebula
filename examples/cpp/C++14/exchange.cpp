// CodeNebula - C++14 Example: std::exchange
// Compile: g++ -std=c++14 -Wall -Wextra -o example exchange.cpp

// Demonstrates std::exchange which replaces a variable's value and returns
// the old value in one atomic-style operation. Real-world use: move
// constructors/assignment, state machines, linked list operations,
// and any "swap-and-return-old" pattern.

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <memory>

// ------------------------------------------------------------------
// 1. Using exchange in a move constructor (classic pattern)
// ------------------------------------------------------------------
class Buffer
{
    int* data_;
    std::size_t size_;

public:
    Buffer(std::size_t size)
        : data_(new int[size]), size_(size)
    {
        for (std::size_t i = 0; i < size; ++i)
            data_[i] = static_cast<int>(i * 10);
    }

    // Move constructor using std::exchange for clean resource transfer
    Buffer(Buffer&& other) noexcept
        : data_(std::exchange(other.data_, nullptr))
        , size_(std::exchange(other.size_, 0))
    {}

    ~Buffer() { delete[] data_; }

    void print() const
    {
        std::cout << "  Buffer[size=" << size_ << "]: ";
        if (data_)
        {
            for (std::size_t i = 0; i < size_; ++i)
                std::cout << data_[i] << " ";
        }
        else
        {
            std::cout << "(empty/moved-from)";
        }
        std::cout << std::endl;
    }
};

// ------------------------------------------------------------------
// 2. State machine using exchange
// ------------------------------------------------------------------
enum class State { Idle, Running, Paused, Stopped };

const char* state_name(State s)
{
    switch (s)
    {
        case State::Idle:    return "Idle";
        case State::Running: return "Running";
        case State::Paused:  return "Paused";
        case State::Stopped: return "Stopped";
    }
    return "Unknown";
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic exchange - swap and get old value
    // ------------------------------------------------------------------
    std::cout << "=== Basic std::exchange ===" << std::endl;
    int value = 42;
    int old = std::exchange(value, 100);
    std::cout << "  old value: " << old << std::endl;
    std::cout << "  new value: " << value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Exchange with strings
    // ------------------------------------------------------------------
    std::cout << "=== String Exchange ===" << std::endl;
    std::string name = "Alice";
    std::string prev = std::exchange(name, "Bob");
    std::cout << "  previous: " << prev << std::endl;
    std::cout << "  current : " << name << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Move constructor pattern
    // ------------------------------------------------------------------
    std::cout << "=== Move Constructor with exchange ===" << std::endl;
    Buffer original(5);
    std::cout << "  Before move:" << std::endl;
    original.print();

    Buffer moved(std::move(original));
    std::cout << "  After move (new):" << std::endl;
    moved.print();
    std::cout << "  After move (old):" << std::endl;
    original.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. State machine transitions
    // ------------------------------------------------------------------
    std::cout << "=== State Machine Transitions ===" << std::endl;
    State current = State::Idle;

    auto transition = [&current](State next) {
        State prev = std::exchange(current, next);
        std::cout << "  " << state_name(prev) << " -> "
                  << state_name(current) << std::endl;
    };

    transition(State::Running);
    transition(State::Paused);
    transition(State::Running);
    transition(State::Stopped);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Building a history / undo stack
    // ------------------------------------------------------------------
    std::cout << "=== Building History with exchange ===" << std::endl;
    std::vector<int> history;
    int counter = 0;

    for (int new_val : {10, 20, 30, 40})
    {
        int old_val = std::exchange(counter, new_val);
        history.push_back(old_val);
    }

    std::cout << "  Current: " << counter << std::endl;
    std::cout << "  History:";
    for (int h : history)
        std::cout << " " << h;
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== Basic std::exchange ===
  old value: 42
  new value: 100

=== String Exchange ===
  previous: Alice
  current : Bob

=== Move Constructor with exchange ===
  Before move:
  Buffer[size=5]: 0 10 20 30 40
  After move (new):
  Buffer[size=5]: 0 10 20 30 40
  After move (old):
  Buffer[size=0]: (empty/moved-from)

=== State Machine Transitions ===
  Idle -> Running
  Running -> Paused
  Paused -> Running
  Running -> Stopped

=== Building History with exchange ===
  Current: 40
  History: 0 10 20 30
*/
