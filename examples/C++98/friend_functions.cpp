// CodeNebula - C++98 Example: Friend Functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example friend_functions.cpp
//
// This example demonstrates:
// - Declaring a non-member function as a friend of a class
// - Friend functions can access private and protected members
// - Common use case: operator overloading (operator<<, operator+)
// - Friend functions are NOT member functions (no 'this' pointer)
// - Friendship is granted, not taken -- the class decides who its friends are

#include <iostream>
#include <cmath>

// ============================================================
// 1. Basic friend function
// ============================================================
class SecretBox {
private:
    int secretNumber;
    char secretWord[32];

public:
    SecretBox(int num, const char* word) : secretNumber(num) {
        std::strncpy(secretWord, word, 31);
        secretWord[31] = '\0';
    }

    // Declare reveal() as a friend -- it can access private members
    friend void reveal(const SecretBox& box);
};

// Definition of the friend function (NOT a member function)
void reveal(const SecretBox& box) {
    std::cout << "  Secret number: " << box.secretNumber << std::endl;
    std::cout << "  Secret word:   " << box.secretWord << std::endl;
}

// ============================================================
// 2. Friend function for operator overloading
// ============================================================
class Vector2D {
private:
    double x, y;

public:
    Vector2D(double xv, double yv) : x(xv), y(yv) {}

    double getX() const { return x; }
    double getY() const { return y; }
    double magnitude() const { return std::sqrt(x * x + y * y); }

    // Member operator+
    Vector2D operator+(const Vector2D& rhs) const {
        return Vector2D(x + rhs.x, y + rhs.y);
    }

    // Friend: operator<< (cannot be a member -- left operand is ostream)
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);

    // Friend: operator* for scalar * Vector2D (scalar on the LEFT)
    // Cannot be a member of Vector2D because the left operand is a double
    friend Vector2D operator*(double scalar, const Vector2D& v);

    // Friend: distance function that needs private access to both vectors
    friend double distance(const Vector2D& a, const Vector2D& b);
};

std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
    os << "(" << v.x << ", " << v.y << ")";  // accesses private x, y
    return os;
}

Vector2D operator*(double scalar, const Vector2D& v) {
    return Vector2D(scalar * v.x, scalar * v.y);  // accesses private x, y
}

double distance(const Vector2D& a, const Vector2D& b) {
    double dx = a.x - b.x;  // accesses private members of both objects
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

// ============================================================
// 3. Friend function operating on two different classes
// ============================================================
class Celsius;  // forward declaration

class Fahrenheit {
private:
    double temp;
public:
    Fahrenheit(double t) : temp(t) {}
    friend void compare(const Celsius& c, const Fahrenheit& f);
    friend std::ostream& operator<<(std::ostream& os, const Fahrenheit& f) {
        os << f.temp << " F";
        return os;
    }
};

class Celsius {
private:
    double temp;
public:
    Celsius(double t) : temp(t) {}
    friend void compare(const Celsius& c, const Fahrenheit& f);
    friend std::ostream& operator<<(std::ostream& os, const Celsius& c) {
        os << c.temp << " C";
        return os;
    }
};

// This function is a friend of BOTH classes
void compare(const Celsius& c, const Fahrenheit& f) {
    double cInF = c.temp * 9.0 / 5.0 + 32.0;
    std::cout << "  " << c << " = " << cInF << " F" << std::endl;
    std::cout << "  " << f << std::endl;
    if (cInF > f.temp) {
        std::cout << "  Celsius value is higher" << std::endl;
    } else if (cInF < f.temp) {
        std::cout << "  Fahrenheit value is higher" << std::endl;
    } else {
        std::cout << "  They are equal" << std::endl;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "1. BASIC FRIEND FUNCTION" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        SecretBox box(42, "OpenSesame");

        // box.secretNumber;  // COMPILE ERROR: private
        // But the friend function can access it:
        reveal(box);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "2. FRIEND FOR OPERATOR OVERLOADING" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Vector2D a(3.0, 4.0);
        Vector2D b(1.0, 2.0);

        // operator<< (friend)
        std::cout << "  a = " << a << std::endl;
        std::cout << "  b = " << b << std::endl;

        // operator+ (member)
        Vector2D c = a + b;
        std::cout << "  a + b = " << c << std::endl;

        // scalar * Vector2D (friend -- scalar on left)
        Vector2D d = 2.5 * a;
        std::cout << "  2.5 * a = " << d << std::endl;

        // distance (friend)
        std::cout << "  distance(a, b) = " << distance(a, b) << std::endl;
        std::cout << "  magnitude of a = " << a.magnitude() << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "3. FRIEND OF TWO CLASSES" << std::endl;
    std::cout << "========================================" << std::endl;
    {
        Celsius    c(100.0);
        Fahrenheit f(212.0);

        compare(c, f);

        std::cout << std::endl;

        Celsius    c2(0.0);
        Fahrenheit f2(100.0);
        compare(c2, f2);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "4. KEY POINTS ABOUT FRIEND FUNCTIONS" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "  - Declared inside the class with 'friend' keyword" << std::endl;
    std::cout << "  - Defined OUTSIDE the class (not a member)" << std::endl;
    std::cout << "  - Has access to private and protected members" << std::endl;
    std::cout << "  - No 'this' pointer -- must receive objects as parameters" << std::endl;
    std::cout << "  - Friendship is NOT inherited, transitive, or reciprocal" << std::endl;
    std::cout << "  - Common use: operator<<, operator>>, binary operators" << std::endl;
    std::cout << "    where the left operand is not the class type" << std::endl;

    return 0;
}

// Expected output:
// ========================================
// 1. BASIC FRIEND FUNCTION
// ========================================
//   Secret number: 42
//   Secret word:   OpenSesame
//
// ========================================
// 2. FRIEND FOR OPERATOR OVERLOADING
// ========================================
//   a = (3, 4)
//   b = (1, 2)
//   a + b = (4, 6)
//   2.5 * a = (7.5, 10)
//   distance(a, b) = 2.82843
//   magnitude of a = 5
//
// ========================================
// 3. FRIEND OF TWO CLASSES
// ========================================
//   100 C = 212 F
//   212 F
//   They are equal
//
//   0 C = 32 F
//   100 F
//   Fahrenheit value is higher
//
// ========================================
// 4. KEY POINTS ABOUT FRIEND FUNCTIONS
// ========================================
//   ...summary...
