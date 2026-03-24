// CodeNebula - C++17 Example: std::is_swappable / std::is_nothrow_swappable
// Compile: g++ -std=c++17 -Wall -Wextra -o example is_swappable.cpp

// Demonstrates the C++17 type traits for detecting whether types support
// swapping, and whether that swap is noexcept. Useful for writing generic
// code that needs to conditionally enable swap-based operations.

#include <iostream>
#include <type_traits>
#include <string>
#include <vector>

// A type that cannot be swapped (deleted swap)
struct NoSwap {
    NoSwap() = default;
    NoSwap(NoSwap&&) = delete;
    NoSwap& operator=(NoSwap&&) = delete;
};

// A type with a noexcept swap
struct SafeSwap {
    int data = 0;
    friend void swap(SafeSwap& a, SafeSwap& b) noexcept {
        std::swap(a.data, b.data);
    }
};

// A type with a potentially-throwing swap
struct ThrowSwap {
    int data = 0;
    friend void swap(ThrowSwap& a, ThrowSwap& b) {
        // Not marked noexcept
        std::swap(a.data, b.data);
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. is_swappable: can a type be swapped?
    // ------------------------------------------------------------------
    std::cout << "=== std::is_swappable ===" << std::endl;
    std::cout << "  int            : " << std::is_swappable_v<int> << std::endl;
    std::cout << "  std::string    : " << std::is_swappable_v<std::string> << std::endl;
    std::cout << "  vector<int>    : " << std::is_swappable_v<std::vector<int>> << std::endl;
    std::cout << "  SafeSwap       : " << std::is_swappable_v<SafeSwap> << std::endl;
    std::cout << "  ThrowSwap      : " << std::is_swappable_v<ThrowSwap> << std::endl;
    std::cout << "  NoSwap         : " << std::is_swappable_v<NoSwap> << std::endl;

    // ------------------------------------------------------------------
    // 2. is_nothrow_swappable: can a type be swapped without throwing?
    // ------------------------------------------------------------------
    std::cout << "\n=== std::is_nothrow_swappable ===" << std::endl;
    std::cout << "  int            : " << std::is_nothrow_swappable_v<int> << std::endl;
    std::cout << "  std::string    : " << std::is_nothrow_swappable_v<std::string> << std::endl;
    std::cout << "  SafeSwap       : " << std::is_nothrow_swappable_v<SafeSwap> << std::endl;
    std::cout << "  ThrowSwap      : " << std::is_nothrow_swappable_v<ThrowSwap> << std::endl;

    // ------------------------------------------------------------------
    // 3. is_swappable_with: can two different types be swapped?
    // ------------------------------------------------------------------
    std::cout << "\n=== std::is_swappable_with ===" << std::endl;
    std::cout << "  int& <-> int&  : "
              << std::is_swappable_with_v<int&, int&> << std::endl;
    std::cout << "  int& <-> double&: "
              << std::is_swappable_with_v<int&, double&> << std::endl;

    // ------------------------------------------------------------------
    // 4. Practical: constexpr-if conditional swap
    // ------------------------------------------------------------------
    auto safe_swap = [](auto& a, auto& b) {
        if constexpr (std::is_nothrow_swappable_v<std::decay_t<decltype(a)>>) {
            std::cout << "  Swapping (noexcept path)" << std::endl;
            using std::swap;
            swap(a, b);
        } else if constexpr (std::is_swappable_v<std::decay_t<decltype(a)>>) {
            std::cout << "  Swapping (may-throw path)" << std::endl;
            using std::swap;
            swap(a, b);
        } else {
            std::cout << "  Cannot swap this type!" << std::endl;
        }
    };

    std::cout << "\n=== Practical ===" << std::endl;
    int x = 10, y = 20;
    safe_swap(x, y);
    std::cout << "  x=" << x << " y=" << y << std::endl;

    return 0;
}

/*
Expected output:

=== std::is_swappable ===
  int            : 1
  std::string    : 1
  vector<int>    : 1
  SafeSwap       : 1
  ThrowSwap      : 1
  NoSwap         : 0

=== std::is_nothrow_swappable ===
  int            : 1
  std::string    : 1
  SafeSwap       : 1
  ThrowSwap      : 0

=== std::is_swappable_with ===
  int& <-> int&  : 1
  int& <-> double&: 0

=== Practical ===
  Swapping (noexcept path)
  x=20 y=10
*/
