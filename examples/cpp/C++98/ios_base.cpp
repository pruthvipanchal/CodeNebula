// CodeNebula - C++98 Example: std::ios_base (format flags, precision)
// Compile: g++ -std=c++98 -Wall -Wextra -o example ios_base.cpp

#include <iostream>
#include <iomanip>

int main() {
    double pi = 3.14159265358979;
    int num = 255;

    // Precision control
    std::cout << "Default precision: " << pi << std::endl;
    std::cout << std::setprecision(3) << "Precision 3: " << pi << std::endl;
    std::cout << std::fixed << "Fixed 3: " << pi << std::endl;
    std::cout << std::scientific << "Scientific 3: " << pi << std::endl;

    // Reset to default
    std::cout.unsetf(std::ios::floatfield);
    std::cout << std::setprecision(6);

    // Integer base formatting
    std::cout << "\nInteger bases for " << num << ":" << std::endl;
    std::cout << "Dec: " << std::dec << num << std::endl;
    std::cout << "Oct: " << std::oct << num << std::endl;
    std::cout << "Hex: " << std::hex << num << std::endl;
    std::cout << "Hex+show: " << std::showbase << std::hex << num << std::endl;
    std::cout << std::noshowbase << std::dec;

    // Width and fill
    std::cout << "\nWidth and fill:" << std::endl;
    std::cout << "[" << std::setw(10) << 42 << "]" << std::endl;
    std::cout << "[" << std::setw(10) << std::left << 42 << "]" << std::endl;
    std::cout << "[" << std::setw(10) << std::right << 42 << "]" << std::endl;
    std::cout << "[" << std::setfill('*') << std::setw(10) << 42 << "]" << std::endl;

    // Boolean format
    std::cout << std::setfill(' ');
    std::cout << "\nBooleans:" << std::endl;
    std::cout << "Default: " << true << " " << false << std::endl;
    std::cout << std::boolalpha;
    std::cout << "Alpha:   " << true << " " << false << std::endl;

    return 0;
}

// Expected output:
// Default precision: 3.14159
// Precision 3: 3.14
// Fixed 3: 3.142
// Scientific 3: 3.142e+00
//
// Integer bases for 255:
// Dec: 255
// Oct: 377
// Hex: ff
// Hex+show: 0xff
//
// Width and fill:
// [        42]
// [42        ]
// [        42]
// [********42]
//
// Booleans:
// Default: 1 0
// Alpha:   true false
