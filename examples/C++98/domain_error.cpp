// CodeNebula - C++98 Example: std::domain_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example domain_error.cpp

#include <iostream>
#include <stdexcept>
#include <cmath>

double safe_log(double x) {
    if (x <= 0) {
        throw std::domain_error("logarithm undefined for non-positive values");
    }
    return std::log(x);
}

double safe_asin(double x) {
    if (x < -1.0 || x > 1.0) {
        throw std::domain_error("asin requires input in [-1, 1]");
    }
    return std::asin(x);
}

int main() {
    // Valid log
    try {
        std::cout << "log(10) = " << safe_log(10) << std::endl;
    } catch (const std::domain_error& e) {
        std::cout << "Domain error: " << e.what() << std::endl;
    }

    // Invalid log
    try {
        std::cout << "log(-5) = " << safe_log(-5) << std::endl;
    } catch (const std::domain_error& e) {
        std::cout << "Domain error: " << e.what() << std::endl;
    }

    // Valid asin
    try {
        std::cout << "asin(0.5) = " << safe_asin(0.5) << std::endl;
    } catch (const std::domain_error& e) {
        std::cout << "Domain error: " << e.what() << std::endl;
    }

    // Invalid asin
    try {
        std::cout << "asin(2.0) = " << safe_asin(2.0) << std::endl;
    } catch (const std::domain_error& e) {
        std::cout << "Domain error: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// log(10) = 2.30259
// Domain error: logarithm undefined for non-positive values
// asin(0.5) = 0.523599
// Domain error: asin requires input in [-1, 1]
