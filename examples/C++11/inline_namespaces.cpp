// CodeNebula - C++11 Example: Inline Namespaces
// Compile: g++ -std=c++11 -Wall -Wextra -o example inline_namespaces.cpp
//
// This example demonstrates:
// - inline namespace for API versioning
// - Members of inline namespaces are accessible from the enclosing namespace
// - Switching default version by changing which namespace is inline
// - Library versioning pattern used in real-world code (e.g., libc++)

#include <iostream>
#include <string>

// ============================================================
// 1. Basic inline namespace
// ============================================================
namespace Graphics {
    inline namespace v2 {
        void draw(const std::string& shape) {
            std::cout << "  [v2] Drawing " << shape << " with anti-aliasing" << std::endl;
        }

        struct Color {
            float r, g, b, a;  // v2 added alpha channel
            void print() const {
                std::cout << "  [v2] Color(" << r << ", " << g << ", "
                          << b << ", " << a << ")" << std::endl;
            }
        };
    }

    namespace v1 {
        void draw(const std::string& shape) {
            std::cout << "  [v1] Drawing " << shape << " (basic)" << std::endl;
        }

        struct Color {
            float r, g, b;  // v1 had no alpha
            void print() const {
                std::cout << "  [v1] Color(" << r << ", " << g << ", "
                          << b << ")" << std::endl;
            }
        };
    }
}

// ============================================================
// 2. Library versioning pattern
// ============================================================
namespace MyLib {
    namespace v1 {
        int compute(int x) { return x * 2; }
        std::string format(int x) {
            return "Result: " + std::to_string(x);
        }
    }

    inline namespace v2 {
        int compute(int x) { return x * x; }  // Changed behavior
        std::string format(int x) {
            return "[v2] Result = " + std::to_string(x);
        }
    }

    namespace v3_experimental {
        int compute(int x) { return x * x * x; }
        std::string format(int x) {
            return "[v3-exp] " + std::to_string(x);
        }
    }
}

// ============================================================
// 3. Template specialization across versions
// ============================================================
namespace Serializer {
    inline namespace v2 {
        template <typename T>
        std::string serialize(const T& val) {
            return "{\"value\": " + std::to_string(val) + "}";
        }
    }

    namespace v1 {
        template <typename T>
        std::string serialize(const T& val) {
            return std::to_string(val);
        }
    }
}

int main() {
    std::cout << "=== Inline Namespaces ===" << std::endl;

    // Using default (inline) version
    std::cout << "\n--- Default (inline v2) ---" << std::endl;
    Graphics::draw("Circle");         // Calls v2::draw
    Graphics::Color c1{1.0f, 0.0f, 0.0f, 0.5f};
    c1.print();

    // Explicitly using older version
    std::cout << "\n--- Explicit v1 ---" << std::endl;
    Graphics::v1::draw("Circle");     // Calls v1::draw
    Graphics::v1::Color c2{1.0f, 0.0f, 0.0f};
    c2.print();

    // Library versioning
    std::cout << "\n--- Library versioning ---" << std::endl;
    std::cout << "  MyLib::compute(5) = " << MyLib::compute(5)
              << " (v2: x*x)" << std::endl;
    std::cout << "  MyLib::v1::compute(5) = " << MyLib::v1::compute(5)
              << " (v1: x*2)" << std::endl;
    std::cout << "  MyLib::v3_experimental::compute(5) = "
              << MyLib::v3_experimental::compute(5)
              << " (v3: x*x*x)" << std::endl;

    std::cout << "  " << MyLib::format(25) << std::endl;
    std::cout << "  " << MyLib::v1::format(25) << std::endl;

    // Serializer versioning
    std::cout << "\n--- Serializer versioning ---" << std::endl;
    std::cout << "  Default: " << Serializer::serialize(42) << std::endl;
    std::cout << "  v1:      " << Serializer::v1::serialize(42) << std::endl;

    std::cout << "\nKey: 'inline namespace' makes its members the default" << std::endl;

    return 0;
}

// Expected output:
// === Inline Namespaces ===
//
// --- Default (inline v2) ---
//   [v2] Drawing Circle with anti-aliasing
//   [v2] Color(1, 0, 0, 0.5)
//
// --- Explicit v1 ---
//   [v1] Drawing Circle (basic)
//   [v1] Color(1, 0, 0)
//
// --- Library versioning ---
//   MyLib::compute(5) = 25 (v2: x*x)
//   MyLib::v1::compute(5) = 10 (v1: x*2)
//   MyLib::v3_experimental::compute(5) = 125 (v3: x*x*x)
//   [v2] Result = 25
//   Result: 25
//
// --- Serializer versioning ---
//   Default: {"value": 42}
//   v1:      42
//
// Key: 'inline namespace' makes its members the default
