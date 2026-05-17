// CodeNebula - C++17 Example: if/switch with Initializers
// Compile: g++ -std=c++17 -Wall -Wextra -o example if_switch_initializers.cpp

// Demonstrates C++17 init-statements in if and switch. The variable declared
// in the initializer is scoped to the entire if/else or switch block, reducing
// pollution of the enclosing scope.

#include <iostream>
#include <map>
#include <string>
#include <mutex>
#include <cstdlib>

int main()
{
    // ------------------------------------------------------------------
    // 1. if with initializer: map lookup
    // ------------------------------------------------------------------
    std::map<std::string, int> scores{{"Alice", 95}, {"Bob", 87}};

    std::cout << "=== if with initializer (map find) ===" << std::endl;
    if (auto it = scores.find("Alice"); it != scores.end()) {
        std::cout << "  Found: " << it->first << " = " << it->second << std::endl;
    } else {
        std::cout << "  Not found" << std::endl;
    }
    // 'it' is not accessible here -- limited to if/else scope

    if (auto it = scores.find("Charlie"); it != scores.end()) {
        std::cout << "  Found: " << it->first << " = " << it->second << std::endl;
    } else {
        std::cout << "  Charlie not found" << std::endl;
    }

    // ------------------------------------------------------------------
    // 2. if with initializer: mutex lock (pattern)
    // ------------------------------------------------------------------
    std::mutex mtx;
    int shared_data = 42;

    std::cout << "\n=== if with initializer (lock_guard) ===" << std::endl;
    if (std::lock_guard<std::mutex> lock(mtx); shared_data > 0) {
        std::cout << "  shared_data is positive: " << shared_data << std::endl;
    }
    // lock is released here when the if block ends

    // ------------------------------------------------------------------
    // 3. if with initializer: numeric check
    // ------------------------------------------------------------------
    std::cout << "\n=== if with initializer (computation) ===" << std::endl;
    for (int n : {-3, 0, 7, 15}) {
        if (auto doubled = n * 2; doubled > 10) {
            std::cout << "  n=" << n << ", doubled=" << doubled << " (> 10)" << std::endl;
        } else {
            std::cout << "  n=" << n << ", doubled=" << doubled << " (<= 10)" << std::endl;
        }
    }

    // ------------------------------------------------------------------
    // 4. switch with initializer
    // ------------------------------------------------------------------
    std::cout << "\n=== switch with initializer ===" << std::endl;
    for (int val : {0, 1, 2, 5}) {
        switch (auto category = val % 3; category) {
            case 0:
                std::cout << "  val=" << val << " -> category 0 (divisible by 3)" << std::endl;
                break;
            case 1:
                std::cout << "  val=" << val << " -> category 1 (remainder 1)" << std::endl;
                break;
            case 2:
                std::cout << "  val=" << val << " -> category 2 (remainder 2)" << std::endl;
                break;
        }
    }

    return 0;
}

/*
Expected output:

=== if with initializer (map find) ===
  Found: Alice = 95
  Charlie not found

=== if with initializer (lock_guard) ===
  shared_data is positive: 42

=== if with initializer (computation) ===
  n=-3, doubled=-6 (<= 10)
  n=0, doubled=0 (<= 10)
  n=7, doubled=14 (> 10)
  n=15, doubled=30 (> 10)

=== switch with initializer ===
  val=0 -> category 0 (divisible by 3)
  val=1 -> category 1 (remainder 1)
  val=2 -> category 2 (remainder 2)
  val=5 -> category 2 (remainder 2)
*/
