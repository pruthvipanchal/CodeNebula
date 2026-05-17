// CodeNebula - C++20 Example: std::to_address
// Compile: g++ -std=c++20 -Wall -Wextra -o example to_address.cpp

#include <iostream>
#include <memory>
#include <vector>

// A simple fancy pointer type that wraps a raw pointer
template <typename T>
class FancyPtr {
    T* ptr_;
public:
    using element_type = T;

    explicit FancyPtr(T* p = nullptr) : ptr_(p) {}
    T& operator*() const { return *ptr_; }
    T* operator->() const { return ptr_; }

    // to_address uses pointer_traits<FancyPtr>::to_address if available,
    // otherwise falls back to operator->()
    friend T* to_address_helper(const FancyPtr& fp) { return fp.ptr_; }
};

// Specialize pointer_traits for FancyPtr
template <typename T>
struct std::pointer_traits<FancyPtr<T>> {
    using pointer = FancyPtr<T>;
    using element_type = T;
    using difference_type = std::ptrdiff_t;

    static T* to_address(const FancyPtr<T>& p) noexcept {
        return &(*p);
    }
};

int main() {
    std::cout << "=== std::to_address with raw pointers ===\n";
    int x = 42;
    int* raw = &x;
    // to_address on a raw pointer returns the pointer itself
    std::cout << "to_address(raw) == raw: " << (std::to_address(raw) == raw) << "\n";
    std::cout << "*to_address(raw) = " << *std::to_address(raw) << "\n";

    std::cout << "\n=== std::to_address with smart pointers ===\n";
    auto sp = std::make_shared<int>(100);
    int* from_shared = std::to_address(sp);
    std::cout << "shared_ptr value via to_address: " << *from_shared << "\n";
    std::cout << "to_address(sp) == sp.get(): " << (from_shared == sp.get()) << "\n";

    auto up = std::make_unique<double>(3.14);
    double* from_unique = std::to_address(up);
    std::cout << "unique_ptr value via to_address: " << *from_unique << "\n";

    std::cout << "\n=== std::to_address with fancy pointer ===\n";
    double val = 2.718;
    FancyPtr<double> fancy(&val);
    double* from_fancy = std::to_address(fancy);
    std::cout << "FancyPtr value via to_address: " << *from_fancy << "\n";
    std::cout << "Addresses match: " << (from_fancy == &val) << "\n";

    std::cout << "\n=== Practical use: passing iterator data to C API ===\n";
    std::vector<int> vec = {10, 20, 30, 40, 50};
    // Safely get the raw pointer from a vector iterator
    int* data_ptr = std::to_address(vec.begin());
    std::cout << "First 3 elements via raw pointer: ";
    for (int i = 0; i < 3; ++i)
        std::cout << data_ptr[i] << " ";
    std::cout << "\n";

    return 0;
}
