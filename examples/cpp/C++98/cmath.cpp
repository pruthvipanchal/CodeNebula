// CodeNebula - C++98 Example: <cmath> functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example cmath.cpp

#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(4);

    // Trigonometric functions
    double pi = std::acos(-1.0);
    std::cout << "pi = " << pi << std::endl;
    std::cout << "sin(pi/6) = " << std::sin(pi / 6.0) << std::endl;
    std::cout << "cos(pi/3) = " << std::cos(pi / 3.0) << std::endl;
    std::cout << "tan(pi/4) = " << std::tan(pi / 4.0) << std::endl;

    // Inverse trig
    std::cout << "asin(0.5) = " << std::asin(0.5) << std::endl;
    std::cout << "atan2(1,1) = " << std::atan2(1.0, 1.0) << std::endl;

    // Power and roots
    std::cout << "sqrt(144) = " << std::sqrt(144.0) << std::endl;
    std::cout << "pow(2,10) = " << std::pow(2.0, 10.0) << std::endl;

    // Exponential and logarithmic
    std::cout << "exp(1) = " << std::exp(1.0) << std::endl;
    std::cout << "log(e) = " << std::log(std::exp(1.0)) << std::endl;
    std::cout << "log10(1000) = " << std::log10(1000.0) << std::endl;

    // Rounding and absolute
    std::cout << "fabs(-3.7) = " << std::fabs(-3.7) << std::endl;
    std::cout << "ceil(2.3) = " << std::ceil(2.3) << std::endl;
    std::cout << "floor(2.7) = " << std::floor(2.7) << std::endl;
    std::cout << "fmod(10.5, 3) = " << std::fmod(10.5, 3.0) << std::endl;

    return 0;
}

// Expected output:
// pi = 3.1416
// sin(pi/6) = 0.5000
// cos(pi/3) = 0.5000
// tan(pi/4) = 1.0000
// asin(0.5) = 0.5236
// atan2(1,1) = 0.7854
// sqrt(144) = 12.0000
// pow(2,10) = 1024.0000
// exp(1) = 2.7183
// log(e) = 1.0000
// log10(1000) = 3.0000
// fabs(-3.7) = 3.7000
// ceil(2.3) = 3.0000
// floor(2.7) = 2.0000
// fmod(10.5, 3) = 1.5000
