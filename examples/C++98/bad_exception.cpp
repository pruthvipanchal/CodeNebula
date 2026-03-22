// CodeNebula - C++98 Example: std::bad_exception
// Compile: g++ -std=c++98 -Wall -Wextra -o example bad_exception.cpp
// Note: Exception specifications (throw(...)) are deprecated in C++11 and removed in C++17.

#include <iostream>
#include <exception>

// If a function with an exception specification throws something not listed,
// unexpected() is called. If bad_exception is in the spec, it gets rethrown
// as bad_exception.

// Function that only allows int and bad_exception
void restricted() throw(int, std::bad_exception) {
    throw 3.14; // throws double, which is not in the spec
}

void my_unexpected() {
    std::cout << "my_unexpected handler called" << std::endl;
    // Re-throw as bad_exception (which IS in the exception spec)
    throw;
}

int main() {
    // Install custom unexpected handler
    std::set_unexpected(my_unexpected);

    try {
        restricted();
    } catch (int e) {
        std::cout << "Caught int: " << e << std::endl;
    } catch (const std::bad_exception& e) {
        std::cout << "Caught bad_exception: " << e.what() << std::endl;
    } catch (...) {
        std::cout << "Caught unknown exception" << std::endl;
    }

    // Direct usage of bad_exception
    try {
        throw std::bad_exception();
    } catch (const std::exception& e) {
        std::cout << "Direct bad_exception: " << e.what() << std::endl;
    }

    return 0;
}

// Expected output (behavior may vary by compiler):
// my_unexpected handler called
// Caught bad_exception: std::bad_exception
// Direct bad_exception: std::bad_exception
