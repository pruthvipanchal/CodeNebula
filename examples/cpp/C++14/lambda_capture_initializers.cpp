// CodeNebula - C++14 Example: Lambda Capture Initializers
// Compile: g++ -std=c++14 -Wall -Wextra -o example lambda_capture_initializers.cpp

// Demonstrates init captures (generalized lambda captures) in C++14. Allows
// creating new variables in the capture clause, including move captures.
// Real-world use: transferring ownership of unique_ptr into lambdas,
// capturing computed values, and creating self-contained closures.

#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic init capture - create a new variable in the capture
    // ------------------------------------------------------------------
    int x = 10;
    auto add_offset = [offset = x + 5](int value) {
        return value + offset;
    };

    std::cout << "=== Basic Init Capture ===" << std::endl;
    std::cout << "  x = " << x << ", offset = x + 5 = 15" << std::endl;
    std::cout << "  add_offset(100) : " << add_offset(100) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Move capture - transfer ownership of unique_ptr into lambda
    // ------------------------------------------------------------------
    auto ptr = std::make_unique<std::string>("Hello, C++14!");

    std::cout << "=== Move Capture with unique_ptr ===" << std::endl;
    std::cout << "  Before move: ptr is "
              << (ptr ? "valid" : "null") << std::endl;

    auto greet = [p = std::move(ptr)]() {
        std::cout << "  Inside lambda: " << *p << std::endl;
    };

    std::cout << "  After move:  ptr is "
              << (ptr ? "valid" : "null") << std::endl;
    greet();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Rename capture - capture under a different name
    // ------------------------------------------------------------------
    std::string name = "CodeNebula";
    auto print_project = [project_name = name]() {
        std::cout << "  Project: " << project_name << std::endl;
    };

    std::cout << "=== Renamed Capture ===" << std::endl;
    print_project();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Capture expression result directly
    // ------------------------------------------------------------------
    std::vector<int> data = {1, 2, 3, 4, 5};

    auto sum_above = [threshold = data.size() / 2](const std::vector<int>& v) {
        int sum = 0;
        for (auto val : v) {
            if (static_cast<std::size_t>(val) > threshold) sum += val;
        }
        return sum;
    };

    std::cout << "=== Capture Computed Expression ===" << std::endl;
    std::cout << "  threshold (size/2) = " << data.size() / 2 << std::endl;
    std::cout << "  sum of elements > threshold: " << sum_above(data) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Mutable init capture with counter (stateful lambda)
    // ------------------------------------------------------------------
    auto counter = [count = 0]() mutable {
        return ++count;
    };

    std::cout << "=== Mutable Init Capture (Counter) ===" << std::endl;
    std::cout << "  call 1: " << counter() << std::endl;
    std::cout << "  call 2: " << counter() << std::endl;
    std::cout << "  call 3: " << counter() << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Init Capture ===
  x = 10, offset = x + 5 = 15
  add_offset(100) : 115

=== Move Capture with unique_ptr ===
  Before move: ptr is valid
  Inside lambda: Hello, C++14!
  After move:  ptr is null

=== Renamed Capture ===
  Project: CodeNebula

=== Capture Computed Expression ===
  threshold (size/2) = 2
  sum of elements > threshold: 12

=== Mutable Init Capture (Counter) ===
  call 1: 1
  call 2: 2
  call 3: 3
*/
