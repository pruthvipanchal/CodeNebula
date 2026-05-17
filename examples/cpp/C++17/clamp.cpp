// CodeNebula - C++17 Example: std::clamp
// Compile: g++ -std=c++17 -Wall -Wextra -o example clamp.cpp

// Demonstrates std::clamp, which constrains a value to lie within a
// [low, high] range. If the value is below low, low is returned;
// if above high, high is returned; otherwise the value itself.

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic integer clamping
    // ------------------------------------------------------------------
    std::cout << "=== Integer Clamping ===" << std::endl;
    std::cout << "  clamp(-5, 0, 100)  = " << std::clamp(-5, 0, 100) << std::endl;
    std::cout << "  clamp(50, 0, 100)  = " << std::clamp(50, 0, 100) << std::endl;
    std::cout << "  clamp(200, 0, 100) = " << std::clamp(200, 0, 100) << std::endl;
    std::cout << "  clamp(0, 0, 100)   = " << std::clamp(0, 0, 100) << std::endl;
    std::cout << "  clamp(100, 0, 100) = " << std::clamp(100, 0, 100) << std::endl;

    // ------------------------------------------------------------------
    // 2. Floating-point clamping
    // ------------------------------------------------------------------
    std::cout << "\n=== Floating-Point Clamping ===" << std::endl;
    double temp = 105.7;
    double clamped = std::clamp(temp, 0.0, 100.0);
    std::cout << "  Temperature " << temp << " clamped to [0,100] = " << clamped << std::endl;

    double opacity = -0.3;
    std::cout << "  Opacity " << opacity << " clamped to [0,1] = "
              << std::clamp(opacity, 0.0, 1.0) << std::endl;

    // ------------------------------------------------------------------
    // 3. Clamping with custom comparator
    // ------------------------------------------------------------------
    std::cout << "\n=== Custom Comparator ===" << std::endl;
    // Clamp string by length comparison
    auto by_length = [](const std::string& a, const std::string& b) {
        return a.size() < b.size();
    };
    std::string lo = "ab";      // min length: 2
    std::string hi = "abcdef";  // max length: 6
    std::string val = "a";      // length: 1 (below min)

    const std::string& result = std::clamp(val, lo, hi, by_length);
    std::cout << "  clamp(\"a\", \"ab\", \"abcdef\") = \"" << result << "\"" << std::endl;

    // ------------------------------------------------------------------
    // 4. Practical: clamping RGB color values
    // ------------------------------------------------------------------
    std::cout << "\n=== RGB Color Clamping ===" << std::endl;
    std::vector<int> raw_colors = {-20, 128, 300, 0, 255, 512};
    std::cout << "  Raw:     ";
    for (int c : raw_colors) std::cout << c << " ";
    std::cout << std::endl;

    std::cout << "  Clamped: ";
    for (int c : raw_colors) {
        std::cout << std::clamp(c, 0, 255) << " ";
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Clamping in a calculation
    // ------------------------------------------------------------------
    std::cout << "\n=== Progress Bar ===" << std::endl;
    for (int raw : {-10, 0, 25, 50, 75, 100, 120}) {
        int pct = std::clamp(raw, 0, 100);
        int bars = pct / 10;
        std::cout << "  " << raw << "% -> [";
        for (int i = 0; i < 10; ++i)
            std::cout << (i < bars ? '#' : '.');
        std::cout << "] " << pct << "%" << std::endl;
    }

    return 0;
}

/*
Expected output:

=== Integer Clamping ===
  clamp(-5, 0, 100)  = 0
  clamp(50, 0, 100)  = 50
  clamp(200, 0, 100) = 100
  clamp(0, 0, 100)   = 0
  clamp(100, 0, 100) = 100

=== Floating-Point Clamping ===
  Temperature 105.7 clamped to [0,100] = 100
  Opacity -0.3 clamped to [0,1] = 0

=== Custom Comparator ===
  clamp("a", "ab", "abcdef") = "ab"

=== RGB Color Clamping ===
  Raw:     -20 128 300 0 255 512
  Clamped: 0 128 255 0 255 255

=== Progress Bar ===
  -10% -> [..........] 0%
  0% -> [..........] 0%
  25% -> [##........] 25%
  50% -> [#####.....] 50%
  75% -> [#######...] 75%
  100% -> [##########] 100%
  120% -> [##########] 100%
*/
