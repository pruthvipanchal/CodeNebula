// CodeNebula - C++14 Example: std::is_final
// Compile: g++ -std=c++14 -Wall -Wextra -o example is_final.cpp

// Demonstrates the std::is_final type trait added in C++14. It checks at
// compile time whether a class is declared 'final' (cannot be inherited from).
// Real-world use: template metaprogramming to choose between inheritance-based
// and composition-based strategies, static assertions in framework code,
// and optimizations like Empty Base Optimization (EBO) decisions.

#include <iostream>
#include <type_traits>
#include <string>

// ------------------------------------------------------------------
// 1. Regular class (not final)
// ------------------------------------------------------------------
class Animal
{
public:
    virtual ~Animal() = default;
    virtual std::string speak() const { return "..."; }
};

// ------------------------------------------------------------------
// 2. Final class (cannot be inherited)
// ------------------------------------------------------------------
class Dog final : public Animal
{
public:
    std::string speak() const override { return "Woof!"; }
};

// ------------------------------------------------------------------
// 3. Final class with no base
// ------------------------------------------------------------------
class Singleton final
{
    int value_;
public:
    explicit Singleton(int v) : value_(v) {}
    int value() const { return value_; }
};

// ------------------------------------------------------------------
// 4. Non-final class
// ------------------------------------------------------------------
class Widget
{
    int id_;
public:
    explicit Widget(int id) : id_(id) {}
    int id() const { return id_; }
};

// ------------------------------------------------------------------
// 5. Template that adapts behavior based on is_final
// ------------------------------------------------------------------
template<typename T, bool IsFinal = std::is_final<T>::value>
struct Wrapper;

// Specialization for non-final: can inherit (enables EBO)
template<typename T>
struct Wrapper<T, false> : private T
{
    int extra_data;
    Wrapper(T base, int data) : T(std::move(base)), extra_data(data) {}
    static const char* strategy() { return "inheritance (EBO eligible)"; }
    const T& base() const { return static_cast<const T&>(*this); }
};

// Specialization for final: must compose (cannot inherit)
template<typename T>
struct Wrapper<T, true>
{
    T base_obj;
    int extra_data;
    Wrapper(T base, int data) : base_obj(std::move(base)), extra_data(data) {}
    static const char* strategy() { return "composition (final class)"; }
    const T& base() const { return base_obj; }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic is_final checks
    // ------------------------------------------------------------------
    std::cout << "=== std::is_final Checks ===" << std::endl;
    std::cout << std::boolalpha;
    std::cout << "  is_final<Animal>    : " << std::is_final<Animal>::value << std::endl;
    std::cout << "  is_final<Dog>       : " << std::is_final<Dog>::value << std::endl;
    std::cout << "  is_final<Singleton> : " << std::is_final<Singleton>::value << std::endl;
    std::cout << "  is_final<Widget>    : " << std::is_final<Widget>::value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. With fundamental and standard library types
    // ------------------------------------------------------------------
    std::cout << "=== Standard Types ===" << std::endl;
    std::cout << "  is_final<int>       : " << std::is_final<int>::value << std::endl;
    std::cout << "  is_final<std::string>: " << std::is_final<std::string>::value << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Adaptive wrapper using is_final
    // ------------------------------------------------------------------
    std::cout << "=== Adaptive Wrapper Pattern ===" << std::endl;

    Wrapper<Widget> w1(Widget(42), 100);
    std::cout << "  Wrapper<Widget>   : " << w1.strategy()
              << ", id=" << w1.base().id() << std::endl;

    Wrapper<Singleton> w2(Singleton(7), 200);
    std::cout << "  Wrapper<Singleton>: " << w2.strategy()
              << ", value=" << w2.base().value() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Size comparison showing EBO effect
    // ------------------------------------------------------------------
    std::cout << "=== Size Comparison (EBO Effect) ===" << std::endl;
    std::cout << "  sizeof(Widget)           : " << sizeof(Widget) << std::endl;
    std::cout << "  sizeof(Wrapper<Widget>)  : " << sizeof(Wrapper<Widget>) << std::endl;
    std::cout << "  sizeof(Singleton)        : " << sizeof(Singleton) << std::endl;
    std::cout << "  sizeof(Wrapper<Singleton>): " << sizeof(Wrapper<Singleton>) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Static assert example (compile-time enforcement)
    // ------------------------------------------------------------------
    std::cout << "=== Compile-Time Enforcement ===" << std::endl;
    static_assert(std::is_final<Dog>::value,
                  "Dog must be final for security reasons");
    static_assert(!std::is_final<Animal>::value,
                  "Animal must not be final to allow polymorphism");
    std::cout << "  static_assert(is_final<Dog>)     : passed" << std::endl;
    std::cout << "  static_assert(!is_final<Animal>) : passed" << std::endl;

    return 0;
}

/*
Expected output:

=== std::is_final Checks ===
  is_final<Animal>    : false
  is_final<Dog>       : true
  is_final<Singleton> : true
  is_final<Widget>    : false

=== Standard Types ===
  is_final<int>       : false
  is_final<std::string>: false

=== Adaptive Wrapper Pattern ===
  Wrapper<Widget>   : inheritance (EBO eligible), id=42
  Wrapper<Singleton>: composition (final class), value=7

=== Size Comparison (EBO Effect) ===
  sizeof(Widget)           : 4
  sizeof(Wrapper<Widget>)  : 8
  sizeof(Singleton)        : 4
  sizeof(Wrapper<Singleton>): 8

=== Compile-Time Enforcement ===
  static_assert(is_final<Dog>)     : passed
  static_assert(!is_final<Animal>) : passed
*/
