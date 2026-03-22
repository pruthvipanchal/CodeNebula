// CodeNebula - C++98 Example: iterator_traits
// Compile: g++ -std=c++98 -Wall -Wextra -o example iterator_traits.cpp

// std::iterator_traits provides a uniform interface to query properties of
// iterators (value_type, difference_type, pointer, reference, iterator_category).
// This enables writing generic algorithms that adapt to iterator capabilities.

#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <typeinfo>

// --- Helper: print the iterator category name ---
std::string category_name(std::input_iterator_tag) {
    return "input_iterator_tag";
}
std::string category_name(std::output_iterator_tag) {
    return "output_iterator_tag";
}
std::string category_name(std::forward_iterator_tag) {
    return "forward_iterator_tag";
}
std::string category_name(std::bidirectional_iterator_tag) {
    return "bidirectional_iterator_tag";
}
std::string category_name(std::random_access_iterator_tag) {
    return "random_access_iterator_tag";
}

// --- Generic function using iterator_traits ---
template <typename Iterator>
void print_iterator_info(const std::string& name) {
    typedef typename std::iterator_traits<Iterator>::value_type      value_type;
    typedef typename std::iterator_traits<Iterator>::difference_type difference_type;
    typedef typename std::iterator_traits<Iterator>::iterator_category category;

    std::cout << name << ":" << std::endl;
    std::cout << "  value_type:      " << typeid(value_type).name() << std::endl;
    std::cout << "  difference_type: " << typeid(difference_type).name() << std::endl;
    std::cout << "  category:        " << category_name(category()) << std::endl;
}

// --- A generic advance_n that uses tag dispatch ---
// For random access iterators: O(1) jump
template <typename Iterator>
void advance_impl(Iterator& it, int n, std::random_access_iterator_tag) {
    std::cout << "  [Using random access: it += " << n << "]" << std::endl;
    it += n;
}

// For bidirectional iterators: O(n) step-by-step, forward or backward
template <typename Iterator>
void advance_impl(Iterator& it, int n, std::bidirectional_iterator_tag) {
    std::cout << "  [Using bidirectional: stepping " << n << " times]" << std::endl;
    if (n > 0) {
        for (int i = 0; i < n; ++i) ++it;
    } else {
        for (int i = 0; i > n; --i) --it;
    }
}

// For input/forward iterators: O(n) step forward only
template <typename Iterator>
void advance_impl(Iterator& it, int n, std::input_iterator_tag) {
    std::cout << "  [Using input/forward: stepping " << n << " times forward]" << std::endl;
    for (int i = 0; i < n; ++i) ++it;
}

// Main dispatch function
template <typename Iterator>
void my_advance(Iterator& it, int n) {
    typedef typename std::iterator_traits<Iterator>::iterator_category category;
    advance_impl(it, n, category());
}

// --- Generic distance using iterator_traits ---
template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
my_distance_impl(Iterator first, Iterator last, std::random_access_iterator_tag) {
    std::cout << "  [random access subtraction]" << std::endl;
    return last - first;
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
my_distance_impl(Iterator first, Iterator last, std::input_iterator_tag) {
    std::cout << "  [counting increments]" << std::endl;
    typename std::iterator_traits<Iterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template <typename Iterator>
typename std::iterator_traits<Iterator>::difference_type
my_distance(Iterator first, Iterator last) {
    typedef typename std::iterator_traits<Iterator>::iterator_category category;
    return my_distance_impl(first, last, category());
}

// --- Generic sum using value_type ---
template <typename Iterator>
typename std::iterator_traits<Iterator>::value_type
generic_sum(Iterator first, Iterator last) {
    typedef typename std::iterator_traits<Iterator>::value_type T;
    T sum = T();
    while (first != last) {
        sum += *first;
        ++first;
    }
    return sum;
}

int main() {
    // --- Query iterator traits ---
    std::cout << "=== Iterator traits info ===" << std::endl;
    print_iterator_info<std::vector<int>::iterator>("vector<int>::iterator");
    std::cout << std::endl;
    print_iterator_info<std::list<double>::iterator>("list<double>::iterator");
    std::cout << std::endl;
    print_iterator_info<int*>("int*");
    std::cout << std::endl;
    print_iterator_info<const char*>("const char*");

    // --- Tag dispatch: my_advance ---
    std::cout << "\n=== Tag dispatch: my_advance ===" << std::endl;

    // Random access (vector)
    std::vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);

    std::vector<int>::iterator vit = vec.begin();
    std::cout << "Vector advance(3) from " << *vit << ":" << std::endl;
    my_advance(vit, 3);
    std::cout << "  Result: " << *vit << std::endl;

    // Bidirectional (list)
    std::list<int> lst;
    lst.push_back(100);
    lst.push_back(200);
    lst.push_back(300);
    lst.push_back(400);

    std::list<int>::iterator lit = lst.begin();
    std::cout << "\nList advance(2) from " << *lit << ":" << std::endl;
    my_advance(lit, 2);
    std::cout << "  Result: " << *lit << std::endl;

    std::cout << "\nList advance(-1) from " << *lit << ":" << std::endl;
    my_advance(lit, -1);
    std::cout << "  Result: " << *lit << std::endl;

    // Raw pointer
    int arr[] = {1, 2, 3, 4, 5};
    int* p = arr;
    std::cout << "\nPointer advance(4) from " << *p << ":" << std::endl;
    my_advance(p, 4);
    std::cout << "  Result: " << *p << std::endl;

    // --- Tag dispatch: my_distance ---
    std::cout << "\n=== Tag dispatch: my_distance ===" << std::endl;

    std::cout << "Vector distance:" << std::endl;
    std::cout << "  = " << my_distance(vec.begin(), vec.end()) << std::endl;

    std::cout << "List distance:" << std::endl;
    std::cout << "  = " << my_distance(lst.begin(), lst.end()) << std::endl;

    // --- Generic sum using value_type ---
    std::cout << "\n=== Generic sum using value_type ===" << std::endl;
    std::cout << "Vector sum: " << generic_sum(vec.begin(), vec.end()) << std::endl;
    std::cout << "Array sum:  " << generic_sum(arr, arr + 5) << std::endl;

    std::vector<double> dvec;
    dvec.push_back(1.5);
    dvec.push_back(2.5);
    dvec.push_back(3.5);
    std::cout << "Double sum: " << generic_sum(dvec.begin(), dvec.end()) << std::endl;

    return 0;
}

/*
Expected output (type names are compiler-specific, shown as examples):
=== Iterator traits info ===
vector<int>::iterator:
  value_type:      i
  difference_type: ...
  category:        random_access_iterator_tag

list<double>::iterator:
  value_type:      d
  difference_type: ...
  category:        bidirectional_iterator_tag

int*:
  value_type:      i
  difference_type: ...
  category:        random_access_iterator_tag

const char*:
  value_type:      c
  difference_type: ...
  category:        random_access_iterator_tag

=== Tag dispatch: my_advance ===
Vector advance(3) from 10:
  [Using random access: it += 3]
  Result: 40

List advance(2) from 100:
  [Using bidirectional: stepping 2 times]
  Result: 300

List advance(-1) from 300:
  [Using bidirectional: stepping -1 times]
  Result: 200

Pointer advance(4) from 1:
  [Using random access: it += 4]
  Result: 5

=== Tag dispatch: my_distance ===
Vector distance:
  [random access subtraction]
  = 5
List distance:
  [counting increments]
  = 4

=== Generic sum using value_type ===
Vector sum: 150
Array sum:  15
Double sum: 7.5
*/
