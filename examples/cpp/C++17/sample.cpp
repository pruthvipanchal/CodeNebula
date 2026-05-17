// CodeNebula - C++17 Example: std::sample
// Compile: g++ -std=c++17 -Wall -Wextra -o example sample.cpp

// Demonstrates std::sample, which randomly selects n elements from a range
// without replacement. The relative order of selected elements is preserved.
// Useful for statistical sampling, random subsets, and test data generation.

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <iterator>
#include <array>

int main()
{
    // Use a fixed seed for reproducible output in this example
    std::mt19937 rng(42);

    // ------------------------------------------------------------------
    // 1. Sample from a vector of integers
    // ------------------------------------------------------------------
    std::cout << "=== sample from vector<int> ===" << std::endl;
    std::vector<int> population = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> selected;

    std::sample(population.begin(), population.end(),
                std::back_inserter(selected), 4, rng);

    std::cout << "  Population: ";
    for (int x : population) std::cout << x << " ";
    std::cout << std::endl;

    std::cout << "  Sample(4) : ";
    for (int x : selected) std::cout << x << " ";
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Sample from strings
    // ------------------------------------------------------------------
    std::cout << "\n=== sample from vector<string> ===" << std::endl;
    std::vector<std::string> names = {
        "Alice", "Bob", "Carol", "Dave", "Eve",
        "Frank", "Grace", "Heidi", "Ivan", "Judy"
    };
    std::vector<std::string> chosen;

    std::sample(names.begin(), names.end(),
                std::back_inserter(chosen), 3, rng);

    std::cout << "  All names: ";
    for (const auto& n : names) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "  Chosen(3): ";
    for (const auto& n : chosen) std::cout << n << " ";
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Sample into a fixed-size array
    // ------------------------------------------------------------------
    std::cout << "\n=== sample into array ===" << std::endl;
    std::array<int, 3> arr{};
    std::sample(population.begin(), population.end(),
                arr.begin(), arr.size(), rng);

    std::cout << "  Array sample: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Multiple independent samples (different seeds)
    // ------------------------------------------------------------------
    std::cout << "\n=== multiple samples (different seeds) ===" << std::endl;
    for (int trial = 0; trial < 3; ++trial) {
        std::mt19937 trial_rng(trial * 100);
        std::vector<int> s;
        std::sample(population.begin(), population.end(),
                    std::back_inserter(s), 3, trial_rng);
        std::cout << "  Trial " << trial << ": ";
        for (int x : s) std::cout << x << " ";
        std::cout << std::endl;
    }

    // ------------------------------------------------------------------
    // 5. Sampling preserves relative order
    // ------------------------------------------------------------------
    std::cout << "\n=== order preservation ===" << std::endl;
    std::vector<char> letters = {'A','B','C','D','E','F','G','H'};
    std::vector<char> sub;
    std::sample(letters.begin(), letters.end(),
                std::back_inserter(sub), 5, rng);

    std::cout << "  Original: ";
    for (char c : letters) std::cout << c << " ";
    std::cout << std::endl;
    std::cout << "  Sampled : ";
    for (char c : sub) std::cout << c << " ";
    std::cout << " (relative order preserved)" << std::endl;

    return 0;
}

/*
Expected output (with seed=42; exact values depend on MT19937 implementation):

=== sample from vector<int> ===
  Population: 1 2 3 4 5 6 7 8 9 10
  Sample(4) : 1 2 5 8

=== sample from vector<string> ===
  All names: Alice Bob Carol Dave Eve Frank Grace Heidi Ivan Judy
  Chosen(3): Carol Grace Ivan

=== sample into array ===
  Array sample: 2 5 10

=== multiple samples (different seeds) ===
  Trial 0: 2 3 7
  Trial 1: 4 5 10
  Trial 2: 2 3 9

=== order preservation ===
  Original: A B C D E F G H
  Sampled : A B D F G (relative order preserved)
*/
