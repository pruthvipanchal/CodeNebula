// CodeNebula - C++98 Example: <cfloat> floating-point limits
// Compile: g++ -std=c++98 -Wall -Wextra -o example cfloat.cpp

#include <iostream>
#include <cfloat>
#include <iomanip>

int main() {
    std::cout << "=== Float ===" << std::endl;
    std::cout << "FLT_MIN:       " << FLT_MIN << std::endl;
    std::cout << "FLT_MAX:       " << FLT_MAX << std::endl;
    std::cout << "FLT_EPSILON:   " << FLT_EPSILON << std::endl;
    std::cout << "FLT_DIG:       " << FLT_DIG << std::endl;
    std::cout << "FLT_MANT_DIG:  " << FLT_MANT_DIG << std::endl;

    std::cout << "\n=== Double ===" << std::endl;
    std::cout << "DBL_MIN:       " << DBL_MIN << std::endl;
    std::cout << "DBL_MAX:       " << DBL_MAX << std::endl;
    std::cout << "DBL_EPSILON:   " << DBL_EPSILON << std::endl;
    std::cout << "DBL_DIG:       " << DBL_DIG << std::endl;
    std::cout << "DBL_MANT_DIG:  " << DBL_MANT_DIG << std::endl;

    std::cout << "\n=== Long Double ===" << std::endl;
    std::cout << "LDBL_MIN:      " << LDBL_MIN << std::endl;
    std::cout << "LDBL_MAX:      " << LDBL_MAX << std::endl;
    std::cout << "LDBL_EPSILON:  " << LDBL_EPSILON << std::endl;
    std::cout << "LDBL_DIG:      " << LDBL_DIG << std::endl;

    // Practical: demonstrate epsilon significance
    double a = 1.0;
    double b = a + DBL_EPSILON;
    double c = a + DBL_EPSILON / 2.0;

    std::cout << std::setprecision(20);
    std::cout << "\n=== Epsilon Demo ===" << std::endl;
    std::cout << "1.0 == 1.0 + eps:     " << (a == b ? "equal" : "different") << std::endl;
    std::cout << "1.0 == 1.0 + eps/2:   " << (a == c ? "equal" : "different") << std::endl;

    return 0;
}

// Expected output (platform-dependent values):
// === Float ===
// FLT_MIN:       1.17549e-38
// FLT_MAX:       3.40282e+38
// FLT_EPSILON:   1.19209e-07
// FLT_DIG:       6
// FLT_MANT_DIG:  24
//
// === Double ===
// DBL_MIN:       2.22507e-308
// DBL_MAX:       1.79769e+308
// DBL_EPSILON:   2.22045e-16
// DBL_DIG:       15
// DBL_MANT_DIG:  53
//
// === Long Double ===
// LDBL_MIN:      <platform-dependent>
// LDBL_MAX:      <platform-dependent>
// LDBL_EPSILON:  <platform-dependent>
// LDBL_DIG:      <platform-dependent>
//
// === Epsilon Demo ===
// 1.0 == 1.0 + eps:     different
// 1.0 == 1.0 + eps/2:   equal
