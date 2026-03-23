// CodeNebula - C++11 Example: std::stof, std::stod, std::stold
// Compile: g++ -std=c++11 -Wall -Wextra -o example stod.cpp

// std::stof, std::stod, and std::stold convert strings to floating-point
// types (float, double, long double). They handle scientific notation,
// special values (inf, nan), and report parsing positions.

#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>
#include <iomanip>

int main() {
    // Basic conversions
    float f = std::stof("3.14");
    double d = std::stod("2.71828");
    long double ld = std::stold("1.41421356237");
    std::cout << std::setprecision(10);
    std::cout << "stof(\"3.14\"):          " << f << std::endl;
    std::cout << "stod(\"2.71828\"):       " << d << std::endl;
    std::cout << "stold(\"1.41421...\"):   " << static_cast<double>(ld) << std::endl;

    // Negative and leading whitespace
    double neg = std::stod("  -42.5  ");
    std::cout << "\nstod(\"  -42.5  \"): " << neg << std::endl;

    // Scientific notation
    double sci1 = std::stod("1.5e3");
    double sci2 = std::stod("2.5E-4");
    double sci3 = std::stod("-1.23e+2");
    std::cout << "\nScientific notation:" << std::endl;
    std::cout << "  \"1.5e3\"   = " << sci1 << std::endl;
    std::cout << "  \"2.5E-4\"  = " << sci2 << std::endl;
    std::cout << "  \"-1.23e+2\"= " << sci3 << std::endl;

    // Hexadecimal floating-point (C99/C++11)
    double hf = std::stod("0x1.91eb86p+1");  // pi in hex float
    std::cout << "\nHex float \"0x1.91eb86p+1\" = " << hf << std::endl;

    // Special values
    double inf_val = std::stod("inf");
    double nan_val = std::stod("nan");
    std::cout << "\nSpecial values:" << std::endl;
    std::cout << "  \"inf\":  " << inf_val << " (isinf: "
              << (std::isinf(inf_val) ? "true" : "false") << ")" << std::endl;
    std::cout << "  \"nan\":  " << nan_val << " (isnan: "
              << (std::isnan(nan_val) ? "true" : "false") << ")" << std::endl;

    // Position tracking
    std::string data = "3.14 meters";
    std::size_t pos = 0;
    double value = std::stod(data, &pos);
    std::string unit = data.substr(pos);
    std::cout << "\nParsing \"" << data << "\":" << std::endl;
    std::cout << "  Value: " << value << std::endl;
    std::cout << "  Rest:  \"" << unit << "\"" << std::endl;

    // Parsing multiple values from a string
    std::string coords = "1.5 2.7 3.9";
    std::size_t offset = 0;
    std::cout << "\nParsing coordinates from \"" << coords << "\":" << std::endl;
    for (int i = 0; i < 3; ++i) {
        double v = std::stod(coords.substr(offset), &pos);
        offset += pos;
        std::cout << "  [" << i << "] = " << v << std::endl;
    }

    // Error handling
    try {
        std::stod("xyz");
    } catch (const std::invalid_argument& e) {
        std::cout << "\ninvalid_argument: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output (precision may vary):
// stof("3.14"):          3.140000105
// stod("2.71828"):       2.71828
// stold("1.41421..."):   1.41421356237
//
// stod("  -42.5  "): -42.5
//
// Scientific notation:
//   "1.5e3"   = 1500
//   "2.5E-4"  = 0.00025
//   "-1.23e+2"= -123
//
// Hex float "0x1.91eb86p+1" = 3.14159265
//
// Special values:
//   "inf":  inf (isinf: true)
//   "nan":  nan (isnan: true)
//
// Parsing "3.14 meters":
//   Value: 3.14
//   Rest:  " meters"
//
// Parsing coordinates from "1.5 2.7 3.9":
//   [0] = 1.5
//   [1] = 2.7
//   [2] = 3.9
//
// invalid_argument: stod
