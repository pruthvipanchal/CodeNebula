// CodeNebula - C++11 Example: Unrestricted Unions
// Compile: g++ -std=c++11 -Wall -Wextra -o example unrestricted_unions.cpp
//
// This example demonstrates:
// - C++11 unions can contain members with non-trivial constructors/destructors
// - Manual lifetime management of union members using placement new
// - Tagged union (discriminated union) pattern
// - Comparison with C++98 union restrictions

#include <iostream>
#include <string>
#include <new>       // placement new
#include <cstdint>

// ============================================================
// 1. In C++98, unions could only hold POD types.
//    In C++11, unions can hold types like std::string.
// ============================================================
union SimpleUnion {
    int i;
    double d;
    std::string s;  // Would be illegal in C++98!

    // Must provide constructor/destructor since string is non-trivial
    SimpleUnion() : i(0) {}
    ~SimpleUnion() {}  // Does NOT destroy s automatically
};

// ============================================================
// 2. Tagged union (discriminated union) pattern
// ============================================================
class Variant {
public:
    enum Type { INT, DOUBLE, STRING, NONE };

private:
    Type type_;
    union Storage {
        int i;
        double d;
        std::string s;

        Storage() {}   // No-op: active member set manually
        ~Storage() {}  // No-op: Variant manages lifetime
    } data_;

    void destroy() {
        if (type_ == STRING) {
            data_.s.~basic_string();  // Explicit destructor call
        }
        type_ = NONE;
    }

public:
    Variant() : type_(NONE) {}

    Variant(int val) : type_(INT) {
        data_.i = val;
    }

    Variant(double val) : type_(DOUBLE) {
        data_.d = val;
    }

    Variant(const std::string& val) : type_(STRING) {
        new (&data_.s) std::string(val);  // Placement new
    }

    ~Variant() { destroy(); }

    // Copy constructor
    Variant(const Variant& other) : type_(NONE) {
        switch (other.type_) {
            case INT:    type_ = INT;    data_.i = other.data_.i; break;
            case DOUBLE: type_ = DOUBLE; data_.d = other.data_.d; break;
            case STRING: type_ = STRING; new (&data_.s) std::string(other.data_.s); break;
            case NONE:   break;
        }
    }

    // Assignment
    Variant& operator=(const Variant& other) {
        if (this != &other) {
            destroy();
            switch (other.type_) {
                case INT:    type_ = INT;    data_.i = other.data_.i; break;
                case DOUBLE: type_ = DOUBLE; data_.d = other.data_.d; break;
                case STRING: type_ = STRING; new (&data_.s) std::string(other.data_.s); break;
                case NONE:   break;
            }
        }
        return *this;
    }

    Type getType() const { return type_; }

    void print() const {
        switch (type_) {
            case INT:    std::cout << "int(" << data_.i << ")"; break;
            case DOUBLE: std::cout << "double(" << data_.d << ")"; break;
            case STRING: std::cout << "string(\"" << data_.s << "\")"; break;
            case NONE:   std::cout << "none"; break;
        }
    }
};

int main() {
    std::cout << "=== Unrestricted Unions ===" << std::endl;

    // Basic union with string
    std::cout << "\n--- Simple union with std::string ---" << std::endl;
    SimpleUnion su;
    su.i = 42;
    std::cout << "  As int: " << su.i << std::endl;

    new (&su.s) std::string("Hello, union!");
    std::cout << "  As string: " << su.s << std::endl;
    su.s.~basic_string();  // Must destroy manually

    // Tagged variant
    std::cout << "\n--- Tagged variant ---" << std::endl;
    Variant v1(42);
    Variant v2(3.14);
    Variant v3(std::string("C++11"));
    Variant v4;

    std::cout << "  v1 = "; v1.print(); std::cout << std::endl;
    std::cout << "  v2 = "; v2.print(); std::cout << std::endl;
    std::cout << "  v3 = "; v3.print(); std::cout << std::endl;
    std::cout << "  v4 = "; v4.print(); std::cout << std::endl;

    // Reassignment changes type
    std::cout << "\n--- Reassignment ---" << std::endl;
    v1 = v3;  // int -> string
    std::cout << "  v1 after = v3: "; v1.print(); std::cout << std::endl;

    v2 = Variant(99);
    std::cout << "  v2 after = 99: "; v2.print(); std::cout << std::endl;

    std::cout << "\n  sizeof(Variant): " << sizeof(Variant) << " bytes" << std::endl;

    return 0;
}

// Expected output:
// === Unrestricted Unions ===
//
// --- Simple union with std::string ---
//   As int: 42
//   As string: Hello, union!
//
// --- Tagged variant ---
//   v1 = int(42)
//   v2 = double(3.14)
//   v3 = string("C++11")
//   v4 = none
//
// --- Reassignment ---
//   v1 after = v3: string("C++11")
//   v2 after = 99: int(99)
//
//   sizeof(Variant): ... bytes
