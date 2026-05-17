// CodeNebula - C++17 Example: [[nodiscard]] Attribute
// Compile: g++ -std=c++17 -Wall -Wextra -o example nodiscard.cpp

// Demonstrates [[nodiscard]], which warns when a function's return value is
// discarded. Useful for error codes, factory functions, and any return value
// that should never be silently ignored.

#include <iostream>
#include <string>
#include <vector>

// ------------------------------------------------------------------
// 1. [[nodiscard]] on a free function returning an error code
// ------------------------------------------------------------------
enum class ErrorCode { Ok, NotFound, PermissionDenied };

[[nodiscard]] ErrorCode open_file(const std::string& name) {
    if (name.empty()) return ErrorCode::NotFound;
    // Simulate opening a file
    return ErrorCode::Ok;
}

// ------------------------------------------------------------------
// 2. [[nodiscard]] on a factory function
// ------------------------------------------------------------------
[[nodiscard]] std::vector<int> generate_sequence(int n) {
    std::vector<int> seq;
    for (int i = 1; i <= n; ++i) {
        seq.push_back(i * i);
    }
    return seq;
}

// ------------------------------------------------------------------
// 3. [[nodiscard]] on a class (all functions returning it warn)
// ------------------------------------------------------------------
struct [[nodiscard]] Result {
    bool success;
    std::string message;
};

Result process(int value) {
    if (value < 0) return {false, "negative input"};
    return {true, "processed " + std::to_string(value)};
}

// ------------------------------------------------------------------
// 4. [[nodiscard]] on a member function
// ------------------------------------------------------------------
class Calculator {
    double total_ = 0.0;
public:
    void add(double v) { total_ += v; }

    [[nodiscard]] double get_total() const { return total_; }

    [[nodiscard]] bool is_positive() const { return total_ > 0; }
};

int main()
{
    // 1. Error code -- using the return value (no warning)
    std::cout << "=== [[nodiscard]] error code ===" << std::endl;
    ErrorCode ec = open_file("data.txt");
    std::cout << "  open_file(\"data.txt\"): "
              << (ec == ErrorCode::Ok ? "Ok" : "Error") << std::endl;

    ec = open_file("");
    std::cout << "  open_file(\"\"): "
              << (ec == ErrorCode::NotFound ? "NotFound" : "Other") << std::endl;

    // NOTE: open_file("test.txt"); without capturing would produce a warning:
    //   warning: ignoring return value of function declared with 'nodiscard'

    // 2. Factory function
    std::cout << "\n=== [[nodiscard]] factory ===" << std::endl;
    auto seq = generate_sequence(5);
    std::cout << "  squares: ";
    for (int v : seq) std::cout << v << " ";
    std::cout << std::endl;

    // 3. [[nodiscard]] struct
    std::cout << "\n=== [[nodiscard]] struct ===" << std::endl;
    Result r = process(42);
    std::cout << "  process(42): " << r.message
              << " (success=" << std::boolalpha << r.success << ")" << std::endl;

    r = process(-1);
    std::cout << "  process(-1): " << r.message
              << " (success=" << r.success << ")" << std::endl;

    // 4. Member functions
    std::cout << "\n=== [[nodiscard]] member functions ===" << std::endl;
    Calculator calc;
    calc.add(10.5);
    calc.add(20.3);
    double total = calc.get_total();
    std::cout << "  total: " << total << std::endl;
    std::cout << "  positive: " << calc.is_positive() << std::endl;

    return 0;
}

/*
Expected output:

=== [[nodiscard]] error code ===
  open_file("data.txt"): Ok
  open_file(""): NotFound

=== [[nodiscard]] factory ===
  squares: 1 4 9 16 25

=== [[nodiscard]] struct ===
  process(42): processed 42 (success=true)
  process(-1): negative input (success=false)

=== [[nodiscard]] member functions ===
  total: 30.8
  positive: true
*/
