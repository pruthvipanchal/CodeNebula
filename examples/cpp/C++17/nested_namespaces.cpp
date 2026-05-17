// CodeNebula - C++17 Example: Nested Namespaces
// Compile: g++ -std=c++17 -Wall -Wextra -o example nested_namespaces.cpp

// Demonstrates the C++17 nested namespace definition syntax: namespace A::B::C {}.
// This replaces the verbose pre-C++17 style of nesting multiple namespace blocks.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. C++17 nested namespace definition (compact syntax)
// ------------------------------------------------------------------
namespace CodeNebula::Math::Constants {
    inline constexpr double pi = 3.14159265358979;
    inline constexpr double e  = 2.71828182845905;
    inline constexpr double golden_ratio = 1.61803398874989;
}

// ------------------------------------------------------------------
// 2. Another nested namespace with functions
// ------------------------------------------------------------------
namespace CodeNebula::Math::Geometry {
    double circle_area(double radius) {
        return Constants::pi * radius * radius;
    }

    double circle_circumference(double radius) {
        return 2.0 * Constants::pi * radius;
    }
}

// ------------------------------------------------------------------
// 3. Deeply nested namespace
// ------------------------------------------------------------------
namespace CodeNebula::IO::Format::Text {
    std::string bold(const std::string& s) {
        return "**" + s + "**";
    }

    std::string italic(const std::string& s) {
        return "_" + s + "_";
    }
}

// ------------------------------------------------------------------
// 4. Adding to an existing nested namespace
// ------------------------------------------------------------------
namespace CodeNebula::Math::Constants {
    inline constexpr double sqrt2 = 1.41421356237310;
}

int main()
{
    // Using nested namespace members
    std::cout << "=== Math::Constants ===" << std::endl;
    std::cout << "  pi          : " << CodeNebula::Math::Constants::pi << std::endl;
    std::cout << "  e           : " << CodeNebula::Math::Constants::e << std::endl;
    std::cout << "  golden_ratio: " << CodeNebula::Math::Constants::golden_ratio << std::endl;
    std::cout << "  sqrt2       : " << CodeNebula::Math::Constants::sqrt2 << std::endl;

    // Using geometry functions
    std::cout << "\n=== Math::Geometry ===" << std::endl;
    double r = 5.0;
    std::cout << "  radius        : " << r << std::endl;
    std::cout << "  circle_area   : " << CodeNebula::Math::Geometry::circle_area(r) << std::endl;
    std::cout << "  circumference : " << CodeNebula::Math::Geometry::circle_circumference(r) << std::endl;

    // Using a namespace alias for convenience
    namespace fmt = CodeNebula::IO::Format::Text;
    std::cout << "\n=== IO::Format::Text ===" << std::endl;
    std::cout << "  bold  : " << fmt::bold("hello") << std::endl;
    std::cout << "  italic: " << fmt::italic("world") << std::endl;

    // Using directive to bring a specific namespace into scope
    {
        using namespace CodeNebula::Math::Constants;
        std::cout << "\n=== using namespace (pi directly) ===" << std::endl;
        std::cout << "  2*pi = " << 2.0 * pi << std::endl;
    }

    return 0;
}

/*
Expected output:

=== Math::Constants ===
  pi          : 3.14159
  e           : 2.71828
  golden_ratio: 1.618
  sqrt2       : 1.41421

=== Math::Geometry ===
  radius        : 5
  circle_area   : 78.5398
  circumference : 31.4159

=== IO::Format::Text ===
  bold  : **hello**
  italic: _world_

=== using namespace (pi directly) ===
  2*pi = 6.28319
*/
