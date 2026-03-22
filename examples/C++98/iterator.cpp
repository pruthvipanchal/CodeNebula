// CodeNebula - C++98 Example: iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example iterator.cpp

// In C++98, custom iterators can inherit from std::iterator to automatically
// define the required typedefs (iterator_category, value_type, difference_type,
// pointer, reference). This base class was deprecated in C++17.

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

// ============================================================================
// Example 1: A custom iterator over a fixed-size array
// ============================================================================
template <typename T, int N>
class FixedArray {
public:
    FixedArray() {
        for (int i = 0; i < N; ++i) {
            data_[i] = T();
        }
    }

    T& operator[](int i) { return data_[i]; }
    const T& operator[](int i) const { return data_[i]; }
    int size() const { return N; }

    // --- Custom iterator inheriting from std::iterator ---
    class iterator : public std::iterator<std::random_access_iterator_tag, T> {
    public:
        iterator() : ptr_(NULL) {}
        explicit iterator(T* p) : ptr_(p) {}

        T& operator*() const { return *ptr_; }
        T* operator->() const { return ptr_; }
        T& operator[](int n) const { return ptr_[n]; }

        iterator& operator++() { ++ptr_; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++ptr_; return tmp; }
        iterator& operator--() { --ptr_; return *this; }
        iterator operator--(int) { iterator tmp = *this; --ptr_; return tmp; }

        iterator& operator+=(int n) { ptr_ += n; return *this; }
        iterator& operator-=(int n) { ptr_ -= n; return *this; }
        iterator operator+(int n) const { return iterator(ptr_ + n); }
        iterator operator-(int n) const { return iterator(ptr_ - n); }

        typename std::iterator<std::random_access_iterator_tag, T>::difference_type
        operator-(const iterator& other) const { return ptr_ - other.ptr_; }

        bool operator==(const iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const iterator& other) const { return ptr_ < other.ptr_; }
        bool operator>(const iterator& other) const { return ptr_ > other.ptr_; }
        bool operator<=(const iterator& other) const { return ptr_ <= other.ptr_; }
        bool operator>=(const iterator& other) const { return ptr_ >= other.ptr_; }

    private:
        T* ptr_;
    };

    // --- Const iterator ---
    class const_iterator : public std::iterator<std::random_access_iterator_tag, T,
                                                 std::ptrdiff_t, const T*, const T&> {
    public:
        const_iterator() : ptr_(NULL) {}
        explicit const_iterator(const T* p) : ptr_(p) {}
        const_iterator(const iterator& it) : ptr_(&(*it)) {}

        const T& operator*() const { return *ptr_; }
        const T* operator->() const { return ptr_; }

        const_iterator& operator++() { ++ptr_; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++ptr_; return tmp; }
        const_iterator& operator--() { --ptr_; return *this; }
        const_iterator operator--(int) { const_iterator tmp = *this; --ptr_; return tmp; }

        const_iterator operator+(int n) const { return const_iterator(ptr_ + n); }
        const_iterator operator-(int n) const { return const_iterator(ptr_ - n); }
        std::ptrdiff_t operator-(const const_iterator& other) const {
            return ptr_ - other.ptr_;
        }

        bool operator==(const const_iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const const_iterator& other) const { return ptr_ != other.ptr_; }
        bool operator<(const const_iterator& other) const { return ptr_ < other.ptr_; }

    private:
        const T* ptr_;
    };

    iterator begin() { return iterator(data_); }
    iterator end() { return iterator(data_ + N); }
    const_iterator begin() const { return const_iterator(data_); }
    const_iterator end() const { return const_iterator(data_ + N); }

private:
    T data_[N];
};

// ============================================================================
// Example 2: A range iterator (generates values on the fly)
// ============================================================================
class RangeIterator : public std::iterator<std::forward_iterator_tag, int> {
public:
    RangeIterator() : value_(0), step_(1) {}
    RangeIterator(int val, int step) : value_(val), step_(step) {}

    int operator*() const { return value_; }

    RangeIterator& operator++() {
        value_ += step_;
        return *this;
    }

    RangeIterator operator++(int) {
        RangeIterator tmp = *this;
        value_ += step_;
        return tmp;
    }

    bool operator==(const RangeIterator& other) const {
        return value_ == other.value_;
    }

    bool operator!=(const RangeIterator& other) const {
        return value_ != other.value_;
    }

private:
    int value_;
    int step_;
};

// Convenience class for range-based iteration
class Range {
public:
    Range(int start, int end, int step = 1)
        : start_(start), end_(end), step_(step) {
        // Adjust end to be an exact multiple of step from start
        int count = (end_ - start_ + step_ - 1) / step_;
        end_ = start_ + count * step_;
    }

    RangeIterator begin() const { return RangeIterator(start_, step_); }
    RangeIterator end() const { return RangeIterator(end_, step_); }

private:
    int start_;
    int end_;
    int step_;
};

int main() {
    // --- FixedArray with custom iterator ---
    std::cout << "=== FixedArray with custom iterator ===" << std::endl;
    FixedArray<int, 6> arr;
    for (int i = 0; i < 6; ++i) {
        arr[i] = (i + 1) * 10;
    }

    // Forward iteration
    std::cout << "Forward: ";
    for (FixedArray<int, 6>::iterator it = arr.begin(); it != arr.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Reverse iteration
    std::cout << "Reverse: ";
    FixedArray<int, 6>::iterator it = arr.end();
    while (it != arr.begin()) {
        --it;
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Random access
    std::cout << "arr.begin()[2] = " << arr.begin()[2] << std::endl;
    std::cout << "*(arr.begin() + 4) = " << *(arr.begin() + 4) << std::endl;

    // --- Using STL algorithms with custom iterator ---
    std::cout << "\n=== STL algorithms with custom iterator ===" << std::endl;

    // std::sort
    FixedArray<int, 5> unsorted;
    unsorted[0] = 50;
    unsorted[1] = 10;
    unsorted[2] = 40;
    unsorted[3] = 20;
    unsorted[4] = 30;

    std::cout << "Before sort: ";
    for (FixedArray<int, 5>::iterator it2 = unsorted.begin();
         it2 != unsorted.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

    std::sort(unsorted.begin(), unsorted.end());

    std::cout << "After sort:  ";
    for (FixedArray<int, 5>::iterator it2 = unsorted.begin();
         it2 != unsorted.end(); ++it2) {
        std::cout << *it2 << " ";
    }
    std::cout << std::endl;

    // std::find
    FixedArray<int, 5>::iterator found = std::find(unsorted.begin(), unsorted.end(), 30);
    if (found != unsorted.end()) {
        std::cout << "Found 30 at position: " << (found - unsorted.begin()) << std::endl;
    }

    // std::copy to vector
    std::vector<int> vec(unsorted.begin(), unsorted.end());
    std::cout << "Copied to vector: ";
    for (std::vector<int>::iterator vit = vec.begin(); vit != vec.end(); ++vit) {
        std::cout << *vit << " ";
    }
    std::cout << std::endl;

    // --- Verify iterator_traits work ---
    std::cout << "\n=== iterator_traits verification ===" << std::endl;
    typedef std::iterator_traits<FixedArray<int, 5>::iterator> traits;
    std::cout << "Category is random_access: "
              << (typeid(traits::iterator_category) ==
                  typeid(std::random_access_iterator_tag) ? "true" : "false")
              << std::endl;

    // --- RangeIterator (forward iterator) ---
    std::cout << "\n=== RangeIterator (forward) ===" << std::endl;
    std::cout << "Range(0, 10, 2): ";
    Range r(0, 10, 2);
    for (RangeIterator rit = r.begin(); rit != r.end(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    std::cout << "Range(1, 6, 1): ";
    Range r2(1, 6, 1);
    for (RangeIterator rit = r2.begin(); rit != r2.end(); ++rit) {
        std::cout << *rit << " ";
    }
    std::cout << std::endl;

    // Copy range into a vector
    std::vector<int> range_vec;
    Range r3(10, 15, 1);
    for (RangeIterator rit = r3.begin(); rit != r3.end(); ++rit) {
        range_vec.push_back(*rit);
    }
    std::cout << "Range(10,15) in vector: ";
    for (std::vector<int>::iterator vit = range_vec.begin();
         vit != range_vec.end(); ++vit) {
        std::cout << *vit << " ";
    }
    std::cout << std::endl;

    return 0;
}

/*
Expected output:
=== FixedArray with custom iterator ===
Forward: 10 20 30 40 50 60
Reverse: 60 50 40 30 20 10
arr.begin()[2] = 30
*(arr.begin() + 4) = 50

=== STL algorithms with custom iterator ===
Before sort: 50 10 40 20 30
After sort:  10 20 30 40 50
Found 30 at position: 2
Copied to vector: 10 20 30 40 50

=== iterator_traits verification ===
Category is random_access: true

=== RangeIterator (forward) ===
Range(0, 10, 2): 0 2 4 6 8
Range(1, 6, 1): 1 2 3 4 5
Range(10,15) in vector: 10 11 12 13 14
*/
