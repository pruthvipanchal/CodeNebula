// CodeNebula - C++11 Example: std::move Casting Utility
// Compile: g++ -std=c++11 -Wall -Wextra -o example move.cpp

// Demonstrates std::move as a casting utility. std::move does NOT move
// anything -- it is an unconditional cast to an rvalue reference, signaling
// that the caller is done with the object and its resources may be taken.

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

class Resource {
    std::string name_;
public:
    Resource(const std::string& n) : name_(n)
    {
        std::cout << "  [Ctor]  " << name_ << std::endl;
    }
    Resource(const Resource& o) : name_(o.name_)
    {
        std::cout << "  [Copy]  " << name_ << std::endl;
    }
    Resource(Resource&& o) noexcept : name_(std::move(o.name_))
    {
        std::cout << "  [Move]  " << name_ << std::endl;
    }
    Resource& operator=(Resource&& o) noexcept
    {
        name_ = std::move(o.name_);
        std::cout << "  [Move=] " << name_ << std::endl;
        return *this;
    }
    const std::string& name() const { return name_; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. std::move is just a cast (nothing moves yet)
    // ------------------------------------------------------------------
    std::cout << "=== std::move is a cast ===" << std::endl;
    std::string s = "Hello";
    std::string&& rref = std::move(s);  // cast only, no move yet
    std::cout << "  s after cast: \"" << s << "\" (still intact)" << std::endl;
    std::cout << "  rref:         \"" << rref << "\"" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Move happens when an rvalue ref is consumed
    // ------------------------------------------------------------------
    std::cout << "=== Actual move occurs on consumption ===" << std::endl;
    std::string dest = std::move(s);    // string move ctor consumes
    std::cout << "  dest: \"" << dest << "\"" << std::endl;
    std::cout << "  s:    \"" << s << "\" (moved-from)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. std::move with custom types
    // ------------------------------------------------------------------
    std::cout << "=== Move with Resource class ===" << std::endl;
    Resource r1("Database");
    Resource r2(std::move(r1));         // triggers move constructor
    std::cout << "  r2.name(): " << r2.name() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. std::move into containers
    // ------------------------------------------------------------------
    std::cout << "=== Move into vector ===" << std::endl;
    std::vector<Resource> vec;
    vec.reserve(3);     // prevent reallocation

    Resource a("Alpha");
    Resource b("Beta");
    vec.push_back(a);              // copy (a is lvalue)
    vec.push_back(std::move(b));   // move (std::move casts to rvalue)

    std::cout << "  vec[0]: " << vec[0].name() << std::endl;
    std::cout << "  vec[1]: " << vec[1].name() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. std::move in swap idiom
    // ------------------------------------------------------------------
    std::cout << "=== Move-based swap ===" << std::endl;
    std::string x = "Left";
    std::string y = "Right";
    std::cout << "  Before: x=\"" << x << "\", y=\"" << y << "\"" << std::endl;

    // Three moves, zero allocations
    std::string tmp = std::move(x);
    x = std::move(y);
    y = std::move(tmp);

    std::cout << "  After:  x=\"" << x << "\", y=\"" << y << "\"" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Moved-from objects are valid but unspecified
    // ------------------------------------------------------------------
    std::cout << "=== Moved-from state ===" << std::endl;
    std::vector<int> v = {1, 2, 3};
    std::vector<int> v2 = std::move(v);
    // v is valid: we can call clear, size, assign, etc.
    std::cout << "  v.size() after move : " << v.size() << std::endl;
    v.assign({10, 20});  // reuse is fine
    std::cout << "  v after reassign    : ";
    for (int n : v) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== std::move is a cast ===
  s after cast: "Hello" (still intact)
  rref:         "Hello"

=== Actual move occurs on consumption ===
  dest: "Hello"
  s:    "" (moved-from)

=== Move with Resource class ===
  [Ctor]  Database
  [Move]  Database
  r2.name(): Database

=== Move into vector ===
  [Ctor]  Alpha
  [Ctor]  Beta
  [Copy]  Alpha
  [Move]  Beta
  vec[0]: Alpha
  vec[1]: Beta

=== Move-based swap ===
  Before: x="Left", y="Right"
  After:  x="Right", y="Left"

=== Moved-from state ===
  v.size() after move : 0
  v after reassign    : 10 20
*/
