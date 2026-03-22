// CodeNebula - C++98 Example: std::ostream
// Compile: g++ -std=c++98 -Wall -Wextra -o ostream_example ostream.cpp

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

int main() {
    std::cout << "=== std::ostream ===" << std::endl;

    // Basic output with different types
    std::cout << "String output" << std::endl;
    std::cout << "Integer: " << 255 << std::endl;
    std::cout << "Double:  " << 3.14159265 << std::endl;

    // Formatting with manipulators
    std::cout << "\n--- Number Formatting ---" << std::endl;
    std::cout << "Hex: " << std::hex << 255 << std::endl;
    std::cout << "Oct: " << std::oct << 255 << std::endl;
    std::cout << "Dec: " << std::dec << 255 << std::endl;

    // Width and fill
    std::cout << "\n--- Width and Fill ---" << std::endl;
    std::cout << std::setw(10) << std::setfill('*') << 42 << std::endl;
    std::cout << std::setw(10) << std::setfill(' ') << std::left << "Left" << "|" << std::endl;
    std::cout << std::setw(10) << std::right << "Right" << "|" << std::endl;

    // Precision
    std::cout << "\n--- Precision ---" << std::endl;
    double pi = 3.14159265358979;
    std::cout << std::setprecision(3) << pi << std::endl;
    std::cout << std::setprecision(8) << pi << std::endl;
    std::cout << std::fixed << std::setprecision(2) << pi << std::endl;
    std::cout << std::scientific << std::setprecision(4) << pi << std::endl;

    // ostringstream - write to string
    std::cout << "\n--- ostringstream ---" << std::endl;
    std::ostringstream oss;
    oss << "Score: " << 95 << "/100";
    std::string result = oss.str();
    std::cout << result << std::endl;

    // write() for raw output
    const char msg[] = "Raw output\n";
    std::cout.write(msg, 11);

    return 0;
}

// Expected Output:
// === std::ostream ===
// String output
// Integer: 255
// Double:  3.14159
//
// --- Number Formatting ---
// Hex: ff
// Oct: 377
// Dec: 255
//
// --- Width and Fill ---
// ********42
// Left      |
//      Right|
//
// --- Precision ---
// 3.14
// 3.1415927
// 3.14
// 3.1416e+00
//
// --- ostringstream ---
// Score: 95/100
// Raw output
