// CodeNebula - C++98 Example: std::iostream
// Compile: g++ -std=c++98 -Wall -Wextra -o iostream_example iostream.cpp

#include <iostream>
#include <string>

int main() {
    std::cout << "=== std::iostream ===" << std::endl;

    // std::cout - standard output
    std::cout << "Hello from std::cout!" << std::endl;

    // Output formatting
    std::cout << "Integer: " << 42 << std::endl;
    std::cout << "Double:  " << 3.14159 << std::endl;
    std::cout << "String:  " << "CodeNebula" << std::endl;
    std::cout << "Char:    " << 'A' << std::endl;
    std::cout << "Bool:    " << true << std::endl;

    // Chaining output
    std::cout << "Chained: " << 1 << ", " << 2 << ", " << 3 << std::endl;

    // std::cin - standard input (commented out for online compiler)
    // std::string name;
    // std::cout << "Enter your name: ";
    // std::cin >> name;
    // std::cout << "Hello, " << name << "!" << std::endl;

    // std::cerr - unbuffered error output
    std::cerr << "This is an error message (via std::cerr)" << std::endl;

    // std::clog - buffered log output
    std::clog << "This is a log message (via std::clog)" << std::endl;

    // Stream state checking
    std::cout << "cout good? " << std::cout.good() << std::endl;
    std::cout << "cout fail? " << std::cout.fail() << std::endl;

    return 0;
}

// Expected Output:
// === std::iostream ===
// Hello from std::cout!
// Integer: 42
// Double:  3.14159
// String:  CodeNebula
// Char:    A
// Bool:    1
// Chained: 1, 2, 3
// This is an error message (via std::cerr)
// This is a log message (via std::clog)
// cout good? 1
// cout fail? 0
