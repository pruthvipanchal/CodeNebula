// CodeNebula - C++14 Example: std::integer_sequence
// Compile: g++ -std=c++14 -Wall -Wextra -o example integer_sequence.cpp

// Demonstrates std::integer_sequence, std::index_sequence, and
// std::make_index_sequence for compile-time index generation. Real-world use:
// unpacking tuples into function arguments, compile-time array manipulation,
// and variadic template parameter pack indexing.

#include <iostream>
#include <tuple>
#include <array>
#include <utility>
#include <string>

// ------------------------------------------------------------------
// 1. Print all elements of a tuple using index_sequence
// ------------------------------------------------------------------
template<typename Tuple, std::size_t... Is>
void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>)
{
    // Fold using initializer list trick (C++14 compatible)
    using swallow = int[];
    (void)swallow{0, (void(std::cout << (Is == 0 ? "" : ", ")
                                     << std::get<Is>(t)), 0)...};
}

template<typename... Args>
void print_tuple(const std::tuple<Args...>& t)
{
    std::cout << "(";
    print_tuple_impl(t, std::make_index_sequence<sizeof...(Args)>{});
    std::cout << ")";
}

// ------------------------------------------------------------------
// 2. Call a function with tuple elements as arguments
// ------------------------------------------------------------------
template<typename F, typename Tuple, std::size_t... Is>
auto apply_impl(F&& f, Tuple&& t, std::index_sequence<Is...>)
{
    return f(std::get<Is>(std::forward<Tuple>(t))...);
}

template<typename F, typename Tuple>
auto apply(F&& f, Tuple&& t)
{
    constexpr auto size = std::tuple_size<typename std::decay<Tuple>::type>::value;
    return apply_impl(std::forward<F>(f), std::forward<Tuple>(t),
                      std::make_index_sequence<size>{});
}

// ------------------------------------------------------------------
// 3. Generate compile-time array with transformed values
// ------------------------------------------------------------------
template<std::size_t... Is>
constexpr auto make_squares(std::index_sequence<Is...>)
{
    return std::array<std::size_t, sizeof...(Is)>{{(Is * Is)...}};
}

template<std::size_t N>
constexpr auto make_squares()
{
    return make_squares(std::make_index_sequence<N>{});
}

// ------------------------------------------------------------------
// 4. Print an integer_sequence's values
// ------------------------------------------------------------------
template<typename T, T... Ints>
void print_sequence(std::integer_sequence<T, Ints...>)
{
    std::cout << "  Sequence:";
    using swallow = int[];
    (void)swallow{0, (void(std::cout << " " << Ints), 0)...};
    std::cout << std::endl;
}

// ------------------------------------------------------------------
// Test function for apply()
// ------------------------------------------------------------------
int sum_three(int a, int b, int c)
{
    return a + b + c;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Printing integer sequences
    // ------------------------------------------------------------------
    std::cout << "=== Integer Sequences ===" << std::endl;
    print_sequence(std::make_index_sequence<6>{});
    print_sequence(std::integer_sequence<int, 2, 4, 6, 8>{});
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Tuple printing with index_sequence
    // ------------------------------------------------------------------
    auto t1 = std::make_tuple(42, 3.14, std::string("hello"), 'A');

    std::cout << "=== Tuple Printing ===" << std::endl;
    std::cout << "  ";
    print_tuple(t1);
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Apply: unpack tuple into function call
    // ------------------------------------------------------------------
    auto args = std::make_tuple(10, 20, 30);
    int result = apply(sum_three, args);

    std::cout << "=== Apply (Tuple -> Function Args) ===" << std::endl;
    std::cout << "  sum_three(10, 20, 30) = " << result << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Compile-time array generation
    // ------------------------------------------------------------------
    constexpr auto squares = make_squares<8>();

    std::cout << "=== Compile-Time Squares Array ===" << std::endl;
    std::cout << "  squares[0..7]:";
    for (auto s : squares)
        std::cout << " " << s;
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Size of sequences
    // ------------------------------------------------------------------
    std::cout << "=== Sequence Sizes ===" << std::endl;
    using seq5 = std::make_index_sequence<5>;
    std::cout << "  make_index_sequence<5>::size() = " << seq5::size() << std::endl;
    using seq10 = std::make_index_sequence<10>;
    std::cout << "  make_index_sequence<10>::size() = " << seq10::size() << std::endl;

    return 0;
}

/*
Expected output:

=== Integer Sequences ===
  Sequence: 0 1 2 3 4 5
  Sequence: 2 4 6 8

=== Tuple Printing ===
  (42, 3.14, hello, A)

=== Apply (Tuple -> Function Args) ===
  sum_three(10, 20, 30) = 60

=== Compile-Time Squares Array ===
  squares[0..7]: 0 1 4 9 16 25 36 49

=== Sequence Sizes ===
  make_index_sequence<5>::size() = 5
  make_index_sequence<10>::size() = 10
*/
