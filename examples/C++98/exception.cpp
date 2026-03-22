// CodeNebula - C++98 Example: std::exception
// Compile: g++ -std=c++98 -Wall -Wextra -o example exception.cpp

#include <iostream>
#include <exception>
#include <string>

// Custom exception deriving from std::exception
class MyError : public std::exception {
    std::string msg_;
public:
    MyError(const std::string& msg) : msg_(msg) {}
    virtual ~MyError() throw() {}
    virtual const char* what() const throw() { return msg_.c_str(); }
};

void risky_function(int x) {
    if (x < 0) throw MyError("negative value not allowed");
    if (x == 0) throw std::exception();
}

int main() {
    // Catch custom exception
    try {
        risky_function(-1);
    } catch (const MyError& e) {
        std::cout << "MyError caught: " << e.what() << std::endl;
    }

    // Catch base std::exception
    try {
        risky_function(0);
    } catch (const std::exception& e) {
        std::cout << "std::exception caught: " << e.what() << std::endl;
    }

    // Catch-all
    try {
        throw 42;
    } catch (...) {
        std::cout << "Unknown exception caught" << std::endl;
    }

    std::cout << "Program continues normally" << std::endl;
    return 0;
}

// Expected output:
// MyError caught: negative value not allowed
// std::exception caught: std::exception
// Unknown exception caught
// Program continues normally
