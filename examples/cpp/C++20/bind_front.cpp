// CodeNebula - C++20 Example: std::bind_front
// Compile: g++ -std=c++20 -Wall -Wextra -o example bind_front.cpp

#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Free function
int add(int a, int b) {
    return a + b;
}

double multiply(double x, double y, double z) {
    return x * y * z;
}

// Class with member function
struct Logger {
    std::string prefix;

    void log(const std::string& level, const std::string& msg) const {
        std::cout << "[" << prefix << "] " << level << ": " << msg << '\n';
    }
};

int main() {
    // Bind the first argument of a binary function
    auto add_ten = std::bind_front(add, 10);
    std::cout << "add_ten(5):  " << add_ten(5) << '\n';
    std::cout << "add_ten(20): " << add_ten(20) << '\n';

    // Bind multiple leading arguments
    auto times_two_three = std::bind_front(multiply, 2.0, 3.0);
    std::cout << "\n2 * 3 * 4 = " << times_two_three(4.0) << '\n';
    std::cout << "2 * 3 * 5 = " << times_two_three(5.0) << '\n';

    // Bind member function with object
    Logger app_logger{"APP"};
    auto app_info = std::bind_front(&Logger::log, &app_logger, "INFO");
    auto app_error = std::bind_front(&Logger::log, &app_logger, "ERROR");

    app_info("Application started");
    app_info("Processing request");
    app_error("Connection timeout");

    // Use with standard algorithms
    std::vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto greater_than = std::bind_front(std::greater<int>{}, 5);

    // greater_than(x) means 5 > x, i.e., x < 5
    auto it = std::ranges::partition(nums, greater_than);
    std::cout << "\nPartitioned (< 5 first): ";
    for (int n : nums) std::cout << n << ' ';
    std::cout << '\n';

    // Compare with lambdas - bind_front is more concise
    auto add_hundred = std::bind_front(add, 100);
    std::vector<int> vals = {1, 2, 3, 4, 5};
    std::cout << "\nAdding 100: ";
    for (int v : vals) std::cout << add_hundred(v) << ' ';
    std::cout << '\n';

    // bind_front preserves noexcept and constexpr properties
    auto safe_add = std::bind_front([](int a, int b) noexcept { return a + b; }, 42);
    std::cout << "\nnoexcept safe_add(8): " << safe_add(8) << '\n';

    return 0;
}
