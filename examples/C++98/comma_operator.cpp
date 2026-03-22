// CodeNebula - C++98 Example: Comma Operator
// Compile: g++ -std=c++98 -Wall -Wextra -o example comma_operator.cpp

// The comma operator (,) evaluates its left operand, discards the result,
// then evaluates and returns its right operand. It guarantees left-to-right
// evaluation order. Common uses include:
//   - Multiple expressions in for-loop init/update
//   - Compact expression sequences
//   - Overloading for custom types (rare)
//
// Note: Commas in function arguments, initializer lists, and variable
// declarations are separators, NOT comma operators.

#include <iostream>
#include <cmath>

// ------------------------------------------------------------------
// Helper: demonstrates that comma returns the rightmost value
// ------------------------------------------------------------------
int sideEffect(int x, const char* label) {
    std::cout << "  sideEffect(" << label << "): " << x << std::endl;
    return x;
}

// ------------------------------------------------------------------
// Overloading the comma operator (rare but possible)
// ------------------------------------------------------------------
class Builder {
private:
    int values[10];
    int count;

public:
    Builder() : count(0) {
        for (int i = 0; i < 10; ++i) values[i] = 0;
    }

    // Overloaded comma operator to chain value additions
    Builder& operator,(int val) {
        if (count < 10) {
            values[count++] = val;
        }
        return *this;
    }

    void print() const {
        std::cout << "  Builder [";
        for (int i = 0; i < count; ++i) {
            std::cout << values[i];
            if (i < count - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

int main() {
    std::cout << "=== C++98 Comma Operator ===" << std::endl;

    // --- 1. Basic comma operator: evaluates left, returns right ---
    std::cout << "\n--- 1. Basic comma operator ---" << std::endl;
    int result;

    result = (1, 2, 3);
    std::cout << "(1, 2, 3) = " << result << std::endl;
    // Expected: 3 (returns the rightmost value)

    result = (10 + 5, 20 + 3, 30 + 1);
    std::cout << "(10+5, 20+3, 30+1) = " << result << std::endl;
    // Expected: 31

    // --- 2. Side effects are all executed ---
    std::cout << "\n--- 2. Side effects (left to right) ---" << std::endl;
    int a = 0, b = 0;
    // Note: a=1 and b=2 are both executed; the expression evaluates to b
    result = (a = 1, b = 2, a + b);
    std::cout << "a=" << a << ", b=" << b << ", result=" << result << std::endl;
    // Expected: a=1, b=2, result=3

    // --- 3. For loop with multiple variables ---
    std::cout << "\n--- 3. Comma in for loops ---" << std::endl;

    // Multiple init and update expressions
    std::cout << "  Two variables, opposite directions:" << std::endl;
    for (int i = 0, j = 10; i < j; ++i, --j) {
        std::cout << "    i=" << i << ", j=" << j << std::endl;
    }
    // Expected: i=0,j=10 -> i=1,j=9 -> ... -> i=4,j=6 -> i=5,j=5 (stops)

    // Complex update with comma
    std::cout << "\n  Fibonacci-like iteration:" << std::endl;
    int x, y, temp;
    for (x = 0, y = 1; x < 50; temp = x, x = y, y = temp + y) {
        std::cout << "    " << x << std::endl;
    }
    // Expected: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34

    // --- 4. Comma in while condition ---
    std::cout << "\n--- 4. Comma in while loop ---" << std::endl;
    int counter = 0;
    // The comma operator: increment counter, then check condition
    while (++counter, counter <= 5) {
        std::cout << "  counter = " << counter << std::endl;
    }
    // Expected: 1, 2, 3, 4, 5

    // --- 5. Comma to evaluate multiple expressions in a single statement ---
    std::cout << "\n--- 5. Multiple expressions in one statement ---" << std::endl;
    int p = 0, q = 0, r = 0;
    // All three assignments happen; statement evaluates to r
    p = 10, q = 20, r = 30;
    std::cout << "p=" << p << ", q=" << q << ", r=" << r << std::endl;
    // Expected: p=10, q=20, r=30

    // --- 6. Comma with function calls (all called, last result kept) ---
    std::cout << "\n--- 6. Comma with function calls ---" << std::endl;
    int val = (sideEffect(1, "first"),
               sideEffect(2, "second"),
               sideEffect(3, "third"));
    std::cout << "  Final value: " << val << std::endl;
    // Expected: all three called, val=3

    // --- 7. Comma vs separator: know the difference ---
    std::cout << "\n--- 7. Comma as separator (NOT operator) ---" << std::endl;

    // These commas are SEPARATORS, not comma operators:
    // a) Function arguments
    //    func(a, b)     <-- separator between arguments
    // b) Variable declarations
    //    int x, y;      <-- separator between declarators
    // c) Template arguments
    //    vector<int, allocator<int>>

    // This IS the comma operator (parentheses force it):
    int funcArgTest = 0;
    funcArgTest = (100, 200);  // Comma operator, result is 200
    std::cout << "  (100, 200) = " << funcArgTest << std::endl;
    // Expected: 200

    // Without parentheses in certain contexts:
    // int z = 100, 200;  // ERROR: comma is a separator here

    // --- 8. Comma operator precedence ---
    std::cout << "\n--- 8. Precedence matters ---" << std::endl;

    // Comma has the LOWEST precedence of all C++ operators
    int v;
    v = 1, 2, 3;         // Parsed as: (v = 1), 2, 3  -> v is 1
    std::cout << "  v = 1, 2, 3  -> v = " << v << std::endl;
    // Expected: 1

    v = (1, 2, 3);       // Parentheses force comma operator -> v is 3
    std::cout << "  v = (1,2,3)  -> v = " << v << std::endl;
    // Expected: 3

    // --- 9. Practical: compact swap ---
    std::cout << "\n--- 9. Practical: compact swap ---" << std::endl;
    int s1 = 10, s2 = 20;
    std::cout << "  Before: s1=" << s1 << ", s2=" << s2 << std::endl;

    // Swap using comma and a temporary (single expression)
    int tmp;
    tmp = s1, s1 = s2, s2 = tmp;
    std::cout << "  After:  s1=" << s1 << ", s2=" << s2 << std::endl;
    // Expected: s1=20, s2=10

    // --- 10. Overloaded comma operator ---
    std::cout << "\n--- 10. Overloaded comma operator ---" << std::endl;
    Builder builder;
    // The comma operator chains additions
    (builder, 10, 20, 30, 40, 50);
    builder.print();
    // Expected: Builder [10, 20, 30, 40, 50]

    return 0;
}

/*
Expected Output:
=== C++98 Comma Operator ===

--- 1. Basic comma operator ---
(1, 2, 3) = 3
(10+5, 20+3, 30+1) = 31

--- 2. Side effects (left to right) ---
a=1, b=2, result=3

--- 3. Comma in for loops ---
  Two variables, opposite directions:
    i=0, j=10
    i=1, j=9
    i=2, j=8
    i=3, j=7
    i=4, j=6

  Fibonacci-like iteration:
    0
    1
    1
    2
    3
    5
    8
    13
    21
    34

--- 4. Comma in while loop ---
  counter = 1
  counter = 2
  counter = 3
  counter = 4
  counter = 5

--- 5. Multiple expressions in one statement ---
p=10, q=20, r=30

--- 6. Comma with function calls ---
  sideEffect(first): 1
  sideEffect(second): 2
  sideEffect(third): 3
  Final value: 3

--- 7. Comma as separator (NOT operator) ---
  (100, 200) = 200

--- 8. Precedence matters ---
  v = 1, 2, 3  -> v = 1
  v = (1,2,3)  -> v = 3

--- 9. Practical: compact swap ---
  Before: s1=10, s2=20
  After:  s1=20, s2=10

--- 10. Overloaded comma operator ---
  Builder [10, 20, 30, 40, 50]
*/
