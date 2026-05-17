// CodeNebula - C++20 Example: std::lerp (Linear Interpolation)
// Compile: g++ -std=c++20 -Wall -Wextra -o example lerp.cpp

#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>

int main() {
    std::cout << std::fixed << std::setprecision(4);

    std::cout << "=== Basic std::lerp ===\n";
    // lerp(a, b, t) = a + t*(b - a), but numerically stable
    std::cout << "lerp(0.0, 10.0, 0.0)  = " << std::lerp(0.0, 10.0, 0.0) << "\n";
    std::cout << "lerp(0.0, 10.0, 0.5)  = " << std::lerp(0.0, 10.0, 0.5) << "\n";
    std::cout << "lerp(0.0, 10.0, 1.0)  = " << std::lerp(0.0, 10.0, 1.0) << "\n";
    std::cout << "lerp(0.0, 10.0, 0.25) = " << std::lerp(0.0, 10.0, 0.25) << "\n";

    std::cout << "\n=== Extrapolation (t outside [0,1]) ===\n";
    std::cout << "lerp(0.0, 10.0, -0.5) = " << std::lerp(0.0, 10.0, -0.5) << "\n";
    std::cout << "lerp(0.0, 10.0, 1.5)  = " << std::lerp(0.0, 10.0, 1.5) << "\n";
    std::cout << "lerp(0.0, 10.0, 2.0)  = " << std::lerp(0.0, 10.0, 2.0) << "\n";

    std::cout << "\n=== Properties guaranteed by std::lerp ===\n";
    double a = 3.0, b = 7.0;
    // lerp(a, b, 0) == a exactly
    assert(std::lerp(a, b, 0.0) == a);
    std::cout << "lerp(a, b, 0) == a: true\n";
    // lerp(a, b, 1) == b exactly
    assert(std::lerp(a, b, 1.0) == b);
    std::cout << "lerp(a, b, 1) == b: true\n";
    // lerp(a, a, t) == a for any t
    assert(std::lerp(a, a, 0.42) == a);
    std::cout << "lerp(a, a, t) == a: true\n";
    // Monotonic: if t1 <= t2, lerp(a,b,t1) <= lerp(a,b,t2) when a <= b
    std::cout << "Monotonicity guaranteed by standard\n";

    std::cout << "\n=== Color interpolation example ===\n";
    double red_start = 255.0, red_end = 0.0;
    double green_start = 0.0, green_end = 128.0;
    double blue_start = 0.0, blue_end = 255.0;

    std::cout << "  t   |   R    |   G    |   B\n";
    std::cout << "------+--------+--------+--------\n";
    for (double t = 0.0; t <= 1.01; t += 0.25) {
        double r = std::lerp(red_start, red_end, t);
        double g = std::lerp(green_start, green_end, t);
        double bl = std::lerp(blue_start, blue_end, t);
        std::cout << " " << std::setw(4) << t << " | "
                  << std::setw(6) << r << " | "
                  << std::setw(6) << g << " | "
                  << std::setw(6) << bl << "\n";
    }

    std::cout << "\n=== Float precision ===\n";
    float fa = 1.0e10f, fb = 1.0f;
    std::cout << "lerp(1e10f, 1f, 0.5) = " << std::lerp(fa, fb, 0.5f) << "\n";
    std::cout << "lerp(1e10f, 1f, 1.0) = " << std::lerp(fa, fb, 1.0f) << "\n";

    return 0;
}
