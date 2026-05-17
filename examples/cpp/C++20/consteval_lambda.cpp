// CodeNebula - C++20 Example: Consteval Lambdas
// Compile: g++ -std=c++20 -Wall -Wextra -o example consteval_lambda.cpp

// Demonstrates consteval lambdas that are guaranteed to execute at compile
// time. Unlike constexpr lambdas, consteval lambdas cannot be called at
// runtime.

#include <iostream>
#include <array>

// ------------------------------------------------------------------
// 1. Basic consteval lambda
// ------------------------------------------------------------------
consteval auto square(int x) {
    return x * x;
}

// ------------------------------------------------------------------
// 2. consteval function using lambda internally
// ------------------------------------------------------------------
consteval int sum_of_squares(int n) {
    auto sq = [](int x) consteval { return x * x; };
    int total = 0;
    for (int i = 1; i <= n; ++i)
        total += sq(i);
    return total;
}

// ------------------------------------------------------------------
// 3. consteval lambda for compile-time string length
// ------------------------------------------------------------------
consteval int ct_strlen(const char* s) {
    int len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

// ------------------------------------------------------------------
// 4. consteval lambda to generate compile-time lookup table
// ------------------------------------------------------------------
consteval auto make_fibonacci_table() {
    std::array<long long, 20> fib{};
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 20; ++i)
        fib[i] = fib[i - 1] + fib[i - 2];
    return fib;
}

// ------------------------------------------------------------------
// 5. consteval lambda for compile-time validation
// ------------------------------------------------------------------
consteval int validated_port(int port) {
    if (port < 1 || port > 65535)
        throw "Invalid port number";  // Compile-time error if invalid
    return port;
}

// ------------------------------------------------------------------
// 6. consteval lambda for factorial
// ------------------------------------------------------------------
consteval long long factorial(int n) {
    auto impl = [](auto self, int n) consteval -> long long {
        return n <= 1 ? 1 : n * self(self, n - 1);
    };
    return impl(impl, n);
}

int main()
{
    std::cout << "=== Basic consteval ===" << std::endl;
    constexpr int sq5 = square(5);
    std::cout << "  square(5) = " << sq5 << std::endl;
    constexpr int sq12 = square(12);
    std::cout << "  square(12) = " << sq12 << std::endl;

    std::cout << "\n=== Sum of Squares (consteval) ===" << std::endl;
    constexpr int s3 = sum_of_squares(3);  // 1+4+9 = 14
    constexpr int s5 = sum_of_squares(5);  // 1+4+9+16+25 = 55
    std::cout << "  sum_of_squares(3) = " << s3 << std::endl;
    std::cout << "  sum_of_squares(5) = " << s5 << std::endl;

    std::cout << "\n=== Compile-Time String Length ===" << std::endl;
    constexpr int len1 = ct_strlen("Hello");
    constexpr int len2 = ct_strlen("C++20 consteval");
    std::cout << "  strlen(\"Hello\") = " << len1 << std::endl;
    std::cout << "  strlen(\"C++20 consteval\") = " << len2 << std::endl;

    std::cout << "\n=== Compile-Time Fibonacci Table ===" << std::endl;
    constexpr auto fib = make_fibonacci_table();
    std::cout << "  First 10 Fibonacci numbers:";
    for (int i = 0; i < 10; ++i)
        std::cout << " " << fib[i];
    std::cout << std::endl;
    std::cout << "  fib[19] = " << fib[19] << std::endl;

    std::cout << "\n=== Compile-Time Validation ===" << std::endl;
    constexpr int port = validated_port(8080);
    std::cout << "  Validated port: " << port << std::endl;
    constexpr int port2 = validated_port(443);
    std::cout << "  Validated port: " << port2 << std::endl;
    // validated_port(70000);  // Would cause compile-time error

    std::cout << "\n=== Consteval Factorial ===" << std::endl;
    constexpr auto f5 = factorial(5);
    constexpr auto f10 = factorial(10);
    constexpr auto f15 = factorial(15);
    std::cout << "  5! = " << f5 << std::endl;
    std::cout << "  10! = " << f10 << std::endl;
    std::cout << "  15! = " << f15 << std::endl;

    // All values are compile-time constants
    static_assert(square(6) == 36);
    static_assert(factorial(6) == 720);
    std::cout << "\n  static_assert checks passed" << std::endl;

    return 0;
}

/*
Expected output:

=== Basic consteval ===
  square(5) = 25
  square(12) = 144

=== Sum of Squares (consteval) ===
  sum_of_squares(3) = 14
  sum_of_squares(5) = 55

=== Compile-Time String Length ===
  strlen("Hello") = 5
  strlen("C++20 consteval") = 15

=== Compile-Time Fibonacci Table ===
  First 10 Fibonacci numbers: 0 1 1 2 3 5 8 13 21 34
  fib[19] = 4181

=== Compile-Time Validation ===
  Validated port: 8080
  Validated port: 443

=== Consteval Factorial ===
  5! = 120
  10! = 3628800
  15! = 1307674368000

  static_assert checks passed
*/
