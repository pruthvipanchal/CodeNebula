// CodeNebula - C++98 Example: auto_ptr (Ownership Transfer)
// Compile: g++ -std=c++98 -Wall -Wextra -o example auto_ptr.cpp
// NOTE: auto_ptr is deprecated in C++11 and removed in C++17. Use unique_ptr instead.

#include <iostream>
#include <memory>
#include <string>

class Resource {
    std::string name_;
public:
    Resource(const std::string& n) : name_(n) {
        std::cout << "Resource '" << name_ << "' created" << std::endl;
    }
    ~Resource() {
        std::cout << "Resource '" << name_ << "' destroyed" << std::endl;
    }
    void use() const { std::cout << "Using '" << name_ << "'" << std::endl; }
};

int main() {
    // auto_ptr owns the object and deletes it when it goes out of scope
    std::auto_ptr<Resource> p1(new Resource("Alpha"));
    p1->use();

    // Ownership transfer: p1 becomes NULL after assignment
    std::auto_ptr<Resource> p2 = p1;
    std::cout << "After transfer, p1 is "
              << (p1.get() == NULL ? "NULL" : "valid") << std::endl;
    p2->use();

    // Release gives up ownership without deleting
    Resource* raw = p2.release();
    std::cout << "After release, p2 is "
              << (p2.get() == NULL ? "NULL" : "valid") << std::endl;
    raw->use();

    // Reset replaces the managed object
    std::auto_ptr<Resource> p3(new Resource("Beta"));
    p3.reset(raw); // deletes Beta, takes ownership of Alpha
    std::cout << "After reset:" << std::endl;
    p3->use();

    std::cout << "--- end of main ---" << std::endl;
    return 0;
}

// Expected output:
// Resource 'Alpha' created
// Using 'Alpha'
// After transfer, p1 is NULL
// Using 'Alpha'
// After release, p2 is NULL
// Using 'Alpha'
// Resource 'Beta' created
// Resource 'Beta' destroyed
// After reset:
// Using 'Alpha'
// --- end of main ---
// Resource 'Alpha' destroyed
