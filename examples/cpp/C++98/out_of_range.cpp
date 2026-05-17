// CodeNebula - C++98 Example: std::out_of_range
// Compile: g++ -std=c++98 -Wall -Wextra -o example out_of_range.cpp

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

int main() {
    // vector::at() throws out_of_range for invalid index
    std::vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    try {
        std::cout << "v.at(1) = " << v.at(1) << std::endl;
        std::cout << "v.at(5) = " << v.at(5) << std::endl; // throws
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    }

    // string::at() also throws out_of_range
    std::string s = "Hello";
    try {
        std::cout << "s.at(0) = " << s.at(0) << std::endl;
        std::cout << "s.at(99) = " << s.at(99) << std::endl; // throws
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    }

    // Throwing out_of_range manually
    try {
        int index = -1;
        if (index < 0) {
            throw std::out_of_range("negative index not allowed");
        }
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// v.at(1) = 20
// Out of range: <implementation-defined message>
// s.at(0) = H
// Out of range: <implementation-defined message>
// Out of range: negative index not allowed
