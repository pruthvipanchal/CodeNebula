// CodeNebula - C++20 Example: unwrap_reference and unwrap_ref_decay
// Compile: g++ -std=c++20 -Wall -Wextra -o example unwrap_reference.cpp

#include <functional>
#include <iostream>
#include <type_traits>

// unwrap_reference<T>::type unwraps reference_wrapper<U> to U&, leaves others as T
// unwrap_ref_decay<T>::type applies decay first, then unwrap_reference

template <typename T>
void show_unwrapped_type(T&& val) {
    using original = decltype(val);
    using unwrapped = typename std::unwrap_reference<std::remove_cvref_t<original>>::type;
    std::cout << "  Value: " << val << "\n";
    std::cout << "  Is reference_wrapper: "
              << (!std::is_same_v<std::remove_cvref_t<original>, unwrapped> ? "yes" : "no")
              << "\n";
}

template <typename T>
void demonstrate_unwrap_ref_decay() {
    using decayed = std::unwrap_ref_decay_t<T>;
    std::cout << "  unwrap_ref_decay applied\n";
    std::cout << "  Same as original after decay: "
              << std::is_same_v<std::decay_t<T>, decayed> << "\n";
}

int main() {
    std::cout << "=== std::unwrap_reference ===\n";

    int x = 42;
    auto ref = std::ref(x);
    auto cref = std::cref(x);

    // unwrap_reference on reference_wrapper yields int&
    using T1 = std::unwrap_reference_t<decltype(ref)>;
    static_assert(std::is_same_v<T1, int&>);
    std::cout << "ref(x) unwraps to int&: true\n";

    // unwrap_reference on reference_wrapper<const int> yields const int&
    using T2 = std::unwrap_reference_t<decltype(cref)>;
    static_assert(std::is_same_v<T2, const int&>);
    std::cout << "cref(x) unwraps to const int&: true\n";

    // Plain types are left unchanged
    using T3 = std::unwrap_reference_t<int>;
    static_assert(std::is_same_v<T3, int>);
    std::cout << "int remains int: true\n";

    std::cout << "\n=== std::unwrap_ref_decay ===\n";

    // Decays array, then checks for reference_wrapper
    using T4 = std::unwrap_ref_decay_t<int[5]>;
    static_assert(std::is_same_v<T4, int*>);
    std::cout << "int[5] decays to int*: true\n";

    // Decays const ref, then checks
    using T5 = std::unwrap_ref_decay_t<const int&>;
    static_assert(std::is_same_v<T5, int>);
    std::cout << "const int& decays to int: true\n";

    // reference_wrapper through decay
    using T6 = std::unwrap_ref_decay_t<std::reference_wrapper<int>>;
    static_assert(std::is_same_v<T6, int&>);
    std::cout << "reference_wrapper<int> unwraps to int&: true\n";

    std::cout << "\n=== Practical use with make_pair-like function ===\n";
    show_unwrapped_type(ref);
    show_unwrapped_type(100);

    return 0;
}
