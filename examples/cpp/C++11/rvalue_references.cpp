// CodeNebula - C++11 Example: Rvalue References
// Compile: g++ -std=c++11 -Wall -Wextra -o example rvalue_references.cpp

// Demonstrates rvalue references (&&): the foundation for move semantics.
// Rvalue references bind to temporaries (rvalues), enabling efficient
// resource transfer instead of expensive deep copies.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// Distinguish lvalue and rvalue overloads
// ------------------------------------------------------------------
void identify(int& x)
{
    std::cout << "  lvalue reference: " << x << std::endl;
}

void identify(int&& x)
{
    std::cout << "  rvalue reference: " << x << std::endl;
}

// Real-world scenario: a function that accepts only temporaries
void consumeString(std::string&& s)
{
    std::cout << "  Consumed: \"" << s << "\"" << std::endl;
    // After this, s can be moved from (still valid but unspecified state)
}

int getTemporary()
{
    return 42;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Lvalues vs rvalues
    // ------------------------------------------------------------------
    std::cout << "=== Lvalues vs rvalues ===" << std::endl;
    int a = 10;
    identify(a);            // a is an lvalue
    identify(20);           // 20 is an rvalue (temporary)
    identify(a + 5);        // a+5 produces an rvalue
    identify(getTemporary()); // return value is an rvalue
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Rvalue reference variables
    // ------------------------------------------------------------------
    int&& rref = 100;      // rref binds to the temporary 100
    rref = 200;             // rvalue refs are modifiable lvalues themselves

    std::cout << "=== Rvalue reference variable ===" << std::endl;
    std::cout << "  rref = " << rref << std::endl;
    // Note: rref itself is an lvalue (it has a name and address)
    identify(rref);         // calls lvalue overload! rref is a named variable
    identify(std::move(rref)); // std::move casts back to rvalue
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Binding rules
    // ------------------------------------------------------------------
    int x = 5;
    // int&& bad = x;       // ERROR: cannot bind rvalue ref to lvalue
    int&& good = x + 1;    // OK: x+1 is an rvalue
    const int& cref = 42;  // OK: const lvalue ref can bind to rvalue

    std::cout << "=== Binding rules ===" << std::endl;
    std::cout << "  int&& good = x+1  : " << good << std::endl;
    std::cout << "  const int& = 42   : " << cref << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Rvalue references with strings
    // ------------------------------------------------------------------
    std::cout << "=== String rvalue references ===" << std::endl;
    consumeString("hello world");                          // string literal -> temporary
    consumeString(std::string("built ") + "on the fly");   // concatenation -> temporary
    // std::string s = "named"; consumeString(s);  // ERROR: s is lvalue
    std::string s = "named";
    consumeString(std::move(s));   // OK: std::move casts to rvalue
    std::cout << "  s after move: \"" << s << "\" (valid but unspecified)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Lifetime extension
    // ------------------------------------------------------------------
    // Rvalue references extend the lifetime of temporaries
    std::string&& temp = std::string("I live longer!");
    std::cout << "=== Lifetime extension ===" << std::endl;
    std::cout << "  temp: " << temp << std::endl;
    // temp is valid here; the temporary's lifetime is extended

    return 0;
}

/*
Expected output:

=== Lvalues vs rvalues ===
  lvalue reference: 10
  rvalue reference: 20
  rvalue reference: 15
  rvalue reference: 42

=== Rvalue reference variable ===
  rref = 200
  lvalue reference: 200
  rvalue reference: 200

=== Binding rules ===
  int&& good = x+1  : 6
  const int& = 42   : 42

=== String rvalue references ===
  Consumed: "hello world"
  Consumed: "built on the fly"
  Consumed: "named"
  s after move: "" (valid but unspecified)

=== Lifetime extension ===
  temp: I live longer!
*/
