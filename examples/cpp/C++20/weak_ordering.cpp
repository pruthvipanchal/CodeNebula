// CodeNebula - C++20 Example: Weak Ordering
// Compile: g++ -std=c++20 -Wall -Wextra -o example weak_ordering.cpp

// Demonstrates std::weak_ordering: values are equivalent but not necessarily
// equal (e.g., case-insensitive string comparison, priority without identity).

#include <iostream>
#include <compare>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// ------------------------------------------------------------------
// 1. Case-insensitive string wrapper
// ------------------------------------------------------------------
struct CIString {
    std::string value;

    std::weak_ordering operator<=>(const CIString& other) const {
        auto to_lower = [](const std::string& s) {
            std::string result = s;
            for (auto& c : result) c = static_cast<char>(std::tolower(c));
            return result;
        };
        std::string a = to_lower(value);
        std::string b = to_lower(other.value);
        if (a < b) return std::weak_ordering::less;
        if (a > b) return std::weak_ordering::greater;
        return std::weak_ordering::equivalent;
    }

    bool operator==(const CIString& other) const {
        return (*this <=> other) == 0;
    }
};

// ------------------------------------------------------------------
// 2. Priority-based comparison (weak ordering by rank)
// ------------------------------------------------------------------
struct Task {
    std::string name;
    int priority;  // lower = more urgent

    // Two tasks with same priority are equivalent but not identical
    std::weak_ordering operator<=>(const Task& other) const {
        return priority <=> other.priority;
    }

    bool operator==(const Task& other) const {
        return priority == other.priority;
    }
};

// ------------------------------------------------------------------
// 3. Checking weak_ordering result values
// ------------------------------------------------------------------
void describe_weak(std::weak_ordering ord, const char* expr) {
    std::cout << "  " << expr << " is ";
    if (ord == std::weak_ordering::less) std::cout << "less";
    else if (ord == std::weak_ordering::equivalent) std::cout << "equivalent";
    else if (ord == std::weak_ordering::greater) std::cout << "greater";
    std::cout << std::endl;
}

int main()
{
    std::cout << "=== Case-Insensitive Comparison ===" << std::endl;
    CIString a{"Hello"}, b{"hello"}, c{"World"}, d{"HELLO"};

    std::cout << "  'Hello' == 'hello'? " << (a == b) << std::endl;
    std::cout << "  'Hello' == 'HELLO'? " << (a == d) << std::endl;
    std::cout << "  'Hello' < 'World'?  " << (a < c) << std::endl;
    describe_weak(a <=> b, "'Hello' <=> 'hello'");
    describe_weak(a <=> c, "'Hello' <=> 'World'");

    std::cout << "\n=== Sorting Case-Insensitive ===" << std::endl;
    std::vector<CIString> words = {
        {"Banana"}, {"apple"}, {"CHERRY"}, {"date"}, {"Apple"}
    };
    std::sort(words.begin(), words.end());
    for (const auto& w : words)
        std::cout << "  " << w.value << std::endl;

    std::cout << "\n=== Task Priority (Weak Ordering) ===" << std::endl;
    std::vector<Task> tasks = {
        {"Write docs", 3},
        {"Fix bug", 1},
        {"Code review", 2},
        {"Deploy", 1},
        {"Refactor", 3}
    };
    std::sort(tasks.begin(), tasks.end());
    for (const auto& t : tasks) {
        std::cout << "  [P" << t.priority << "] " << t.name << std::endl;
    }

    std::cout << "\n  'Fix bug' == 'Deploy'? (same priority) "
              << (tasks[0] == tasks[1]) << std::endl;

    std::cout << "\n=== weak_ordering Has No 'equal' ===" << std::endl;
    // weak_ordering only has: less, equivalent, greater (no "equal")
    std::cout << "  less < 0?       " << (std::weak_ordering::less < 0) << std::endl;
    std::cout << "  equivalent == 0? " << (std::weak_ordering::equivalent == 0) << std::endl;
    std::cout << "  greater > 0?    " << (std::weak_ordering::greater > 0) << std::endl;

    std::cout << "\n=== Conversion ===" << std::endl;
    std::weak_ordering wo = std::weak_ordering::less;
    std::partial_ordering po = wo;  // implicit conversion ok
    std::cout << "  weak->partial (< 0)? " << (po < 0) << std::endl;
    // std::strong_ordering so = wo;  // ERROR: cannot convert weak to strong

    return 0;
}

/*
Expected output:

=== Case-Insensitive Comparison ===
  'Hello' == 'hello'? 1
  'Hello' == 'HELLO'? 1
  'Hello' < 'World'?  1
  'Hello' <=> 'hello' is equivalent
  'Hello' <=> 'World' is less

=== Sorting Case-Insensitive ===
  apple
  Apple
  Banana
  CHERRY
  date

=== Task Priority (Weak Ordering) ===
  [P1] Fix bug
  [P1] Deploy
  [P2] Code review
  [P3] Write docs
  [P3] Refactor

  'Fix bug' == 'Deploy'? (same priority) 1

=== weak_ordering Has No 'equal' ===
  less < 0?       1
  equivalent == 0? 1
  greater > 0?    1

=== Conversion ===
  weak->partial (< 0)? 1
*/
