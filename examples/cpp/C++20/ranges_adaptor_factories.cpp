// CodeNebula - C++20 Example: views::iota, views::empty, views::single
// Compile: g++ -std=c++20 -Wall -Wextra -o example ranges_adaptor_factories.cpp

#include <iostream>
#include <ranges>
#include <vector>
#include <string>

int main() {
    // views::iota - generate incrementing sequence
    std::cout << "Bounded iota [1, 11): ";
    for (int n : std::views::iota(1, 11)) std::cout << n << " ";
    std::cout << "\n";

    // Unbounded iota with take
    std::cout << "Unbounded iota from 100 (first 5): ";
    for (int n : std::views::iota(100) | std::views::take(5)) std::cout << n << " ";
    std::cout << "\n";

    // Iota for generating indices
    std::vector<std::string> fruits = {"apple", "banana", "cherry", "date"};
    std::cout << "\nIndexed fruits:\n";
    for (int i : std::views::iota(0, static_cast<int>(fruits.size())))
        std::cout << "  " << i << ": " << fruits[i] << "\n";

    // views::empty - a range with no elements
    std::cout << "Empty view size: " << std::ranges::size(std::views::empty<int>) << "\n";
    int count = 0;
    for ([[maybe_unused]] int n : std::views::empty<int>) ++count;
    std::cout << "Elements iterated in empty: " << count << "\n";

    // views::single - a range with exactly one element
    std::cout << "\nSingle(42): ";
    for (int n : std::views::single(42)) std::cout << n << " ";
    std::cout << "\n";
    auto sv = std::views::single(std::string("hello"));
    std::cout << "Single string: " << *sv.begin() << "\n";

    // Combining factories with adaptors
    std::cout << "\nIota squares (first 8): ";
    for (int n : std::views::iota(1)
                 | std::views::transform([](int x) { return x * x; })
                 | std::views::take(8))
        std::cout << n << " ";
    std::cout << "\n";

    // Iota with filter: prime numbers
    auto is_prime = [](int n) {
        if (n < 2) return false;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) return false;
        return true;
    };
    std::cout << "First 10 primes: ";
    for (int n : std::views::iota(2)
                 | std::views::filter(is_prime)
                 | std::views::take(10))
        std::cout << n << " ";
    std::cout << "\n";

    // Using factories for generic code patterns
    auto process = [](auto rng) {
        int sum = 0;
        for (int n : rng) sum += n;
        return sum;
    };
    std::cout << "\nSum of iota(1,6): " << process(std::views::iota(1, 6)) << "\n";
    std::cout << "Sum of single(99): " << process(std::views::single(99)) << "\n";
    std::cout << "Sum of empty: " << process(std::views::empty<int>) << "\n";
    return 0;
}
