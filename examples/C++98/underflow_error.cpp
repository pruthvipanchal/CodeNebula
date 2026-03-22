// CodeNebula - C++98 Example: std::underflow_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example underflow_error.cpp

#include <iostream>
#include <stdexcept>
#include <limits>

// Simulate underflow detection for floating-point results
double safe_divide_small(double num, double denom) {
    double result = num / denom;
    // Check if result is smaller than the smallest representable positive double
    if (result != 0.0 && result < std::numeric_limits<double>::min() &&
        result > -std::numeric_limits<double>::min()) {
        throw std::underflow_error("result too small to represent accurately");
    }
    return result;
}

// Stack that throws underflow when popping from empty
class IntStack {
    int data_[100];
    int top_;
public:
    IntStack() : top_(0) {}
    void push(int val) { data_[top_++] = val; }
    int pop() {
        if (top_ == 0) throw std::underflow_error("stack is empty");
        return data_[--top_];
    }
    bool empty() const { return top_ == 0; }
};

int main() {
    // Stack underflow
    IntStack s;
    s.push(10);
    s.push(20);

    try {
        std::cout << "Pop: " << s.pop() << std::endl;
        std::cout << "Pop: " << s.pop() << std::endl;
        std::cout << "Pop: " << s.pop() << std::endl; // throws
    } catch (const std::underflow_error& e) {
        std::cout << "Underflow: " << e.what() << std::endl;
    }

    // Floating-point underflow
    try {
        double tiny = std::numeric_limits<double>::min();
        double result = safe_divide_small(tiny, 1e20);
        std::cout << "Tiny result: " << result << std::endl;
    } catch (const std::underflow_error& e) {
        std::cout << "Underflow: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// Pop: 20
// Pop: 10
// Underflow: stack is empty
// Underflow: result too small to represent accurately
