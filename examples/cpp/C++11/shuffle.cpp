// CodeNebula - C++11 Example: std::shuffle with Random Engine
// Compile: g++ -std=c++11 -Wall -Wextra -o example shuffle.cpp

// std::shuffle randomly reorders elements using a uniform random number
// generator. It replaces the deprecated std::random_shuffle, which relied
// on std::rand(). Using a proper random engine gives better randomness.

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

int main() {
    // Create a random engine seeded with random_device
    std::random_device rd;
    std::mt19937 gen(rd());

    // Shuffle a vector of integers
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::cout << "Original: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    std::shuffle(numbers.begin(), numbers.end(), gen);
    std::cout << "Shuffled: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    // Shuffle again for a different order
    std::shuffle(numbers.begin(), numbers.end(), gen);
    std::cout << "Shuffled again: ";
    for (const auto& n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    // Shuffle strings (simulating a card deck)
    std::vector<std::string> cards = {"Ace", "King", "Queen", "Jack", "10"};
    std::shuffle(cards.begin(), cards.end(), gen);
    std::cout << "Shuffled cards: ";
    for (const auto& c : cards) std::cout << c << " ";
    std::cout << std::endl;

    // Reproducible shuffle with a fixed seed
    std::mt19937 fixed_gen(42);  // fixed seed for reproducibility
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::shuffle(data.begin(), data.end(), fixed_gen);
    std::cout << "Fixed seed shuffle 1: ";
    for (const auto& n : data) std::cout << n << " ";
    std::cout << std::endl;

    // Same seed produces same sequence
    data = {1, 2, 3, 4, 5};
    fixed_gen.seed(42);  // reset to same seed
    std::shuffle(data.begin(), data.end(), fixed_gen);
    std::cout << "Fixed seed shuffle 2: ";
    for (const auto& n : data) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}

// Expected output (shuffled values vary, fixed seed lines are identical):
// Original: 1 2 3 4 5 6 7 8 9 10
// Shuffled: <random permutation>
// Shuffled again: <random permutation>
// Shuffled cards: <random permutation>
// Fixed seed shuffle 1: <deterministic order>
// Fixed seed shuffle 2: <same deterministic order as above>
