// CodeNebula - C++98 Example: std::length_error
// Compile: g++ -std=c++98 -Wall -Wextra -o example length_error.cpp

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

class FixedArray {
    int* data_;
    int size_;
    int capacity_;
public:
    FixedArray(int cap) : data_(new int[cap]), size_(0), capacity_(cap) {}
    ~FixedArray() { delete[] data_; }

    void push_back(int val) {
        if (size_ >= capacity_) {
            throw std::length_error("FixedArray capacity exceeded");
        }
        data_[size_++] = val;
    }
    int size() const { return size_; }
};

int main() {
    // string::resize with excessive length
    try {
        std::string s("hello");
        std::cout << "max_size: " << s.max_size() << std::endl;
        s.resize(s.max_size() + 1); // throws length_error
    } catch (const std::length_error& e) {
        std::cout << "Length error: " << e.what() << std::endl;
    }

    // Custom container with capacity limit
    try {
        FixedArray arr(3);
        arr.push_back(1);
        arr.push_back(2);
        arr.push_back(3);
        std::cout << "Added 3 elements" << std::endl;
        arr.push_back(4); // throws
    } catch (const std::length_error& e) {
        std::cout << "Length error: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output:
// max_size: <large platform-dependent number>
// Length error: <implementation-defined message>
// Added 3 elements
// Length error: FixedArray capacity exceeded
