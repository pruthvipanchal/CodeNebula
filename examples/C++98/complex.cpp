// CodeNebula - C++98 Example: std::complex
// Compile: g++ -std=c++98 -Wall -Wextra -o example complex.cpp

#include <iostream>
#include <complex>
#include <cmath>

int main() {
    std::complex<double> z1(3.0, 4.0);  // 3 + 4i
    std::complex<double> z2(1.0, -2.0); // 1 - 2i

    std::cout << "z1 = " << z1 << std::endl;
    std::cout << "z2 = " << z2 << std::endl;

    // Arithmetic
    std::cout << "z1 + z2 = " << (z1 + z2) << std::endl;
    std::cout << "z1 - z2 = " << (z1 - z2) << std::endl;
    std::cout << "z1 * z2 = " << (z1 * z2) << std::endl;
    std::cout << "z1 / z2 = " << (z1 / z2) << std::endl;

    // Properties
    std::cout << "real(z1) = " << z1.real() << std::endl;
    std::cout << "imag(z1) = " << z1.imag() << std::endl;
    std::cout << "abs(z1)  = " << std::abs(z1) << std::endl;   // magnitude
    std::cout << "arg(z1)  = " << std::arg(z1) << std::endl;   // angle
    std::cout << "norm(z1) = " << std::norm(z1) << std::endl;  // squared magnitude
    std::cout << "conj(z1) = " << std::conj(z1) << std::endl;  // conjugate

    // Polar form
    std::complex<double> p = std::polar(5.0, 0.9272952); // magnitude=5, angle~=atan(4/3)
    std::cout << "polar(5, 0.927) = " << p << std::endl;

    return 0;
}

// Expected output:
// z1 = (3,4)
// z2 = (1,-2)
// z1 + z2 = (4,2)
// z1 - z2 = (2,6)
// z1 * z2 = (11,-2)
// z1 / z2 = (-1,2)
// real(z1) = 3
// imag(z1) = 4
// abs(z1)  = 5
// arg(z1)  = 0.927295
// norm(z1) = 25
// conj(z1) = (3,-4)
// polar(5, 0.927) = (3.00001,3.99999)
