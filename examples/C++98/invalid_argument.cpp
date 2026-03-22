// CodeNebula - C++98 Example: std::invalid_argument
// Compile: g++ -std=c++98 -Wall -Wextra -o example invalid_argument.cpp

#include <iostream>
#include <stdexcept>
#include <cmath>

double compute_sqrt(double x) {
    if (x < 0) {
        throw std::invalid_argument("cannot compute sqrt of negative number");
    }
    return std::sqrt(x);
}

int parse_day(int day) {
    if (day < 1 || day > 31) {
        throw std::invalid_argument("day must be between 1 and 31");
    }
    return day;
}

int main() {
    try {
        std::cout << "sqrt(25) = " << compute_sqrt(25) << std::endl;
        std::cout << "sqrt(-1) = " << compute_sqrt(-1) << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }

    try {
        parse_day(15);
        std::cout << "Day 15 is valid" << std::endl;
        parse_day(42);
    } catch (const std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// sqrt(25) = 5
// Invalid argument: cannot compute sqrt of negative number
// Day 15 is valid
// Invalid argument: day must be between 1 and 31
