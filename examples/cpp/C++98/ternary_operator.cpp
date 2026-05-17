// CodeNebula - C++98 Example: Ternary (Conditional) Operator
// Compile: g++ -std=c++98 -Wall -Wextra -o example ternary_operator.cpp

// The ternary operator (? :) is a compact conditional expression:
//   condition ? value_if_true : value_if_false
// It can replace simple if/else in assignments, function arguments,
// and return statements. This example covers basic usage, nested ternary,
// and practical patterns.

#include <iostream>
#include <string>
#include <cmath>

// ------------------------------------------------------------------
// Helper functions using ternary in return statements
// ------------------------------------------------------------------
int absValue(int x) {
    return (x >= 0) ? x : -x;
}

const char* boolToString(bool val) {
    return val ? "true" : "false";
}

char grade(int score) {
    // Nested ternary (use sparingly - can hurt readability)
    return (score >= 90) ? 'A'
         : (score >= 80) ? 'B'
         : (score >= 70) ? 'C'
         : (score >= 60) ? 'D'
         :                 'F';
}

std::string classifyTemperature(double temp) {
    return (temp > 30.0) ? "Hot"
         : (temp > 20.0) ? "Warm"
         : (temp > 10.0) ? "Cool"
         :                 "Cold";
}

// Ternary to select between two function behaviors
int operate(int a, int b, bool doAdd) {
    return doAdd ? (a + b) : (a - b);
}

int main() {
    std::cout << "=== C++98 Ternary Operator ===" << std::endl;

    // --- 1. Basic usage in assignment ---
    std::cout << "\n--- 1. Basic ternary ---" << std::endl;
    int x = 10, y = 20;
    int maxVal = (x > y) ? x : y;
    int minVal = (x < y) ? x : y;
    std::cout << "x=" << x << ", y=" << y << std::endl;
    std::cout << "max = " << maxVal << std::endl;  // Expected: 20
    std::cout << "min = " << minVal << std::endl;  // Expected: 10

    // --- 2. In output statements ---
    std::cout << "\n--- 2. In output ---" << std::endl;
    int age = 17;
    std::cout << "Age " << age << ": "
              << ((age >= 18) ? "Adult" : "Minor") << std::endl;
    // Expected: Minor

    bool loggedIn = true;
    std::cout << "User is " << (loggedIn ? "logged in" : "logged out") << std::endl;
    // Expected: logged in

    int count = 1;
    std::cout << count << " item" << (count == 1 ? "" : "s") << std::endl;
    // Expected: 1 item

    count = 5;
    std::cout << count << " item" << (count == 1 ? "" : "s") << std::endl;
    // Expected: 5 items

    // --- 3. Return value from function ---
    std::cout << "\n--- 3. In return statements ---" << std::endl;
    std::cout << "abs(-7) = " << absValue(-7) << std::endl;   // Expected: 7
    std::cout << "abs(3)  = " << absValue(3) << std::endl;    // Expected: 3

    std::cout << "true  = " << boolToString(true) << std::endl;
    std::cout << "false = " << boolToString(false) << std::endl;

    // --- 4. Nested ternary (chained conditions) ---
    std::cout << "\n--- 4. Nested ternary ---" << std::endl;
    int scores[] = {95, 82, 73, 64, 45};
    for (int i = 0; i < 5; ++i) {
        std::cout << "Score " << scores[i] << " -> Grade: " << grade(scores[i]) << std::endl;
    }
    // Expected: A, B, C, D, F

    std::cout << std::endl;
    double temps[] = {35.0, 25.0, 15.0, 5.0};
    for (int i = 0; i < 4; ++i) {
        std::cout << temps[i] << " C -> " << classifyTemperature(temps[i]) << std::endl;
    }
    // Expected: Hot, Warm, Cool, Cold

    // --- 5. Ternary as function argument ---
    std::cout << "\n--- 5. As function argument ---" << std::endl;
    int a = 10, b = 3;
    std::cout << "10 + 3 = " << operate(a, b, true) << std::endl;   // Expected: 13
    std::cout << "10 - 3 = " << operate(a, b, false) << std::endl;  // Expected: 7

    // --- 6. Ternary with different types (careful!) ---
    std::cout << "\n--- 6. Type considerations ---" << std::endl;
    int intVal = 5;
    // Both branches must be compatible types
    double result = (intVal > 0) ? 1.5 : -1.5;
    std::cout << "result = " << result << std::endl;
    // Expected: 1.5

    // --- 7. Ternary for initialization ---
    std::cout << "\n--- 7. Initialization patterns ---" << std::endl;
    bool isDebug = true;
    int logLevel = isDebug ? 3 : 1;
    std::string mode = isDebug ? "DEBUG" : "RELEASE";
    std::cout << "Mode: " << mode << ", Log level: " << logLevel << std::endl;
    // Expected: Mode: DEBUG, Log level: 3

    // --- 8. Ternary with side effects (use carefully) ---
    std::cout << "\n--- 8. Side effects ---" << std::endl;
    int counter1 = 0, counter2 = 0;
    bool condition = true;

    // Increments only one counter based on condition
    (condition ? counter1 : counter2)++;
    std::cout << "counter1=" << counter1 << ", counter2=" << counter2 << std::endl;
    // Expected: counter1=1, counter2=0

    condition = false;
    (condition ? counter1 : counter2)++;
    std::cout << "counter1=" << counter1 << ", counter2=" << counter2 << std::endl;
    // Expected: counter1=1, counter2=1

    // --- 9. Ternary vs if/else comparison ---
    std::cout << "\n--- 9. Ternary vs if/else ---" << std::endl;

    int value = 42;

    // if/else version
    std::string descIf;
    if (value % 2 == 0) {
        descIf = "even";
    } else {
        descIf = "odd";
    }

    // Ternary version (more concise for simple cases)
    std::string descTernary = (value % 2 == 0) ? "even" : "odd";

    std::cout << "if/else:  " << value << " is " << descIf << std::endl;
    std::cout << "ternary:  " << value << " is " << descTernary << std::endl;
    // Both produce: 42 is even

    // --- 10. Practical: clamping without a function ---
    std::cout << "\n--- 10. Practical: clamping ---" << std::endl;
    int raw = 150;
    int lo = 0, hi = 100;
    int clamped = (raw < lo) ? lo : (raw > hi) ? hi : raw;
    std::cout << "clamp(" << raw << ", " << lo << ", " << hi << ") = " << clamped << std::endl;
    // Expected: 100

    raw = -5;
    clamped = (raw < lo) ? lo : (raw > hi) ? hi : raw;
    std::cout << "clamp(" << raw << ", " << lo << ", " << hi << ") = " << clamped << std::endl;
    // Expected: 0

    raw = 50;
    clamped = (raw < lo) ? lo : (raw > hi) ? hi : raw;
    std::cout << "clamp(" << raw << ", " << lo << ", " << hi << ") = " << clamped << std::endl;
    // Expected: 50

    return 0;
}

/*
Expected Output:
=== C++98 Ternary Operator ===

--- 1. Basic ternary ---
x=10, y=20
max = 20
min = 10

--- 2. In output ---
Age 17: Minor
User is logged in
1 item
5 items

--- 3. In return statements ---
abs(-7) = 7
abs(3)  = 3
true  = true
false = false

--- 4. Nested ternary ---
Score 95 -> Grade: A
Score 82 -> Grade: B
Score 73 -> Grade: C
Score 64 -> Grade: D
Score 45 -> Grade: F

35 C -> Hot
25 C -> Warm
15 C -> Cool
5 C -> Cold

--- 5. As function argument ---
10 + 3 = 13
10 - 3 = 7

--- 6. Type considerations ---
result = 1.5

--- 7. Initialization patterns ---
Mode: DEBUG, Log level: 3

--- 8. Side effects ---
counter1=1, counter2=0
counter1=1, counter2=1

--- 9. Ternary vs if/else ---
if/else:  42 is even
ternary:  42 is even

--- 10. Practical: clamping ---
clamp(150, 0, 100) = 100
clamp(-5, 0, 100) = 0
clamp(50, 0, 100) = 50
*/
