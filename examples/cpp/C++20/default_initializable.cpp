// CodeNebula - C++20 Example: std::default_initializable Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example default_initializable.cpp

// std::default_initializable<T> is satisfied when T can be default-constructed,
// value-initialized with T{}, and default-initialized with T t;.
// This is stronger than just having a default constructor.

#include <concepts>
#include <iostream>
#include <string>
#include <vector>

// Default-initializable type
struct Config {
    int width = 800;
    int height = 600;
    std::string title = "Untitled";
};

// Not default-initializable (deleted default constructor)
struct RequiresArgs {
    int value;
    RequiresArgs(int v) : value(v) {}
    // No default constructor available
};

// Create a default-initialized array of N elements
template <std::default_initializable T, std::size_t N>
std::vector<T> make_defaults() {
    std::vector<T> result(N);  // requires default_initializable
    return result;
}

// Reset an object to its default state
template <std::default_initializable T>
void reset(T& obj) {
    obj = T{};  // requires value-initialization
}

template <typename T>
void check_default_init(const char* name) {
    std::cout << name << ": " << std::default_initializable<T> << "\n";
}

int main() {
    // Create defaults
    auto configs = make_defaults<Config, 3>();
    std::cout << "Created " << configs.size() << " default configs\n";
    std::cout << "First config: " << configs[0].width << "x"
              << configs[0].height << " \"" << configs[0].title << "\"\n";

    // Reset a modified config
    configs[0].width = 1920;
    configs[0].title = "My App";
    std::cout << "Modified: " << configs[0].width << " \"" << configs[0].title << "\"\n";
    reset(configs[0]);
    std::cout << "Reset: " << configs[0].width << " \"" << configs[0].title << "\"\n";

    // Make default ints
    auto nums = make_defaults<int, 5>();
    std::cout << "\nDefault ints: ";
    for (int n : nums) std::cout << n << " ";
    std::cout << "\n";

    // Concept checks
    std::cout << "\nDefault initializable checks:\n";
    check_default_init<int>("int");
    check_default_init<std::string>("string");
    check_default_init<Config>("Config");
    check_default_init<std::vector<int>>("vector<int>");
    check_default_init<RequiresArgs>("RequiresArgs");

    return 0;
}

// Expected output:
// Created 3 default configs
// First config: 800x600 "Untitled"
// Modified: 1920 "My App"
// Reset: 800 "Untitled"
//
// Default ints: 0 0 0 0 0
//
// Default initializable checks:
// int: 1
// string: 1
// Config: 1
// vector<int>: 1
// RequiresArgs: 0
