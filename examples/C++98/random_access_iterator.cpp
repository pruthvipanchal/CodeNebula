// CodeNebula - C++98 Example: random_access_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example random_access_iterator.cpp

// Random access iterators support all iterator operations including
// pointer arithmetic (it + n, it - n, it[n], it1 - it2, comparisons).
// std::vector, std::deque, and raw pointers provide random access iterators.

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

int main() {
    // --- Vector random access ---
    std::cout << "=== Vector random access ===" << std::endl;
    int arr[] = {10, 20, 30, 40, 50, 60, 70, 80};
    std::vector<int> vec(arr, arr + 8);

    std::vector<int>::iterator it = vec.begin();
    std::cout << "*it       = " << *it << std::endl;
    std::cout << "*(it + 3) = " << *(it + 3) << std::endl;
    std::cout << "it[5]     = " << it[5] << std::endl;

    // --- Arithmetic operations ---
    std::cout << "\n=== Arithmetic operations ===" << std::endl;
    std::vector<int>::iterator first = vec.begin();
    std::vector<int>::iterator last = vec.end();

    // Addition and subtraction
    std::cout << "*(first + 2) = " << *(first + 2) << std::endl;
    std::cout << "*(last - 1)  = " << *(last - 1) << std::endl;
    std::cout << "*(last - 3)  = " << *(last - 3) << std::endl;

    // Distance (subtraction of iterators)
    std::cout << "last - first = " << (last - first) << std::endl;

    // Compound assignment
    it = vec.begin();
    it += 4;
    std::cout << "After it += 4: " << *it << std::endl;
    it -= 2;
    std::cout << "After it -= 2: " << *it << std::endl;

    // --- Comparison operators ---
    std::cout << "\n=== Comparison operators ===" << std::endl;
    std::vector<int>::iterator a = vec.begin() + 2;
    std::vector<int>::iterator b = vec.begin() + 5;
    std::cout << "*a = " << *a << ", *b = " << *b << std::endl;
    std::cout << "a < b:  " << (a < b ? "true" : "false") << std::endl;
    std::cout << "a > b:  " << (a > b ? "true" : "false") << std::endl;
    std::cout << "a <= b: " << (a <= b ? "true" : "false") << std::endl;
    std::cout << "a >= b: " << (a >= b ? "true" : "false") << std::endl;
    std::cout << "a == a: " << (a == a ? "true" : "false") << std::endl;
    std::cout << "a != b: " << (a != b ? "true" : "false") << std::endl;

    // --- Pointer arithmetic (raw pointers are random access iterators) ---
    std::cout << "\n=== Raw pointer arithmetic ===" << std::endl;
    int data[] = {100, 200, 300, 400, 500};
    int* ptr = data;

    std::cout << "*ptr       = " << *ptr << std::endl;
    std::cout << "*(ptr + 2) = " << *(ptr + 2) << std::endl;
    std::cout << "ptr[3]     = " << ptr[3] << std::endl;

    int* end_ptr = data + 5;
    std::cout << "end - begin = " << (end_ptr - ptr) << std::endl;

    // Use raw pointers with STL algorithms
    std::cout << "Sorted array: ";
    std::sort(data, data + 5);
    for (int* p = data; p != data + 5; ++p) {
        std::cout << *p << " ";
    }
    std::cout << std::endl;

    // --- Subscript operator ---
    std::cout << "\n=== Subscript operator ===" << std::endl;
    it = vec.begin();
    std::cout << "Accessing via it[i]:" << std::endl;
    for (int i = 0; i < static_cast<int>(vec.size()); ++i) {
        std::cout << "  it[" << i << "] = " << it[i] << std::endl;
    }

    // --- Using random access with algorithms ---
    std::cout << "\n=== Algorithms requiring random access ===" << std::endl;

    // std::sort requires random access iterators
    std::vector<int> unsorted;
    unsorted.push_back(50);
    unsorted.push_back(10);
    unsorted.push_back(40);
    unsorted.push_back(20);
    unsorted.push_back(30);

    std::sort(unsorted.begin(), unsorted.end());
    std::cout << "Sorted: ";
    std::copy(unsorted.begin(), unsorted.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // std::nth_element partitions around the nth element
    std::vector<int> nth_vec;
    nth_vec.push_back(50);
    nth_vec.push_back(10);
    nth_vec.push_back(40);
    nth_vec.push_back(20);
    nth_vec.push_back(30);

    std::nth_element(nth_vec.begin(), nth_vec.begin() + 2, nth_vec.end());
    std::cout << "Median (3rd element): " << nth_vec[2] << std::endl;

    // std::random_shuffle
    std::vector<int> shuffled;
    for (int i = 1; i <= 5; ++i) {
        shuffled.push_back(i);
    }
    std::random_shuffle(shuffled.begin(), shuffled.end());
    std::cout << "Shuffled: ";
    std::copy(shuffled.begin(), shuffled.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << " (random order)" << std::endl;

    // --- Deque random access ---
    std::cout << "\n=== Deque random access ===" << std::endl;
    std::deque<int> dq;
    dq.push_back(11);
    dq.push_back(22);
    dq.push_back(33);
    dq.push_back(44);

    std::deque<int>::iterator dit = dq.begin();
    std::cout << "dit[0] = " << dit[0] << std::endl;
    std::cout << "dit[2] = " << dit[2] << std::endl;
    std::cout << "*(dit + 3) = " << *(dit + 3) << std::endl;

    // --- Key properties ---
    std::cout << "\n=== Random access iterator properties ===" << std::endl;
    std::cout << "1. Supports all bidirectional operations PLUS:" << std::endl;
    std::cout << "2. it + n, it - n, it += n, it -= n" << std::endl;
    std::cout << "3. it1 - it2 (distance)" << std::endl;
    std::cout << "4. it[n] (subscript)" << std::endl;
    std::cout << "5. it1 < it2, it1 > it2, it1 <= it2, it1 >= it2" << std::endl;
    std::cout << "6. Category: std::random_access_iterator_tag" << std::endl;
    std::cout << "7. Containers: vector, deque, raw pointers (C arrays)" << std::endl;

    return 0;
}

/*
Expected output:
=== Vector random access ===
*it       = 10
*(it + 3) = 40
it[5]     = 60

=== Arithmetic operations ===
*(first + 2) = 30
*(last - 1)  = 80
*(last - 3)  = 60
last - first = 8
After it += 4: 50
After it -= 2: 30

=== Comparison operators ===
*a = 30, *b = 60
a < b:  true
a > b:  false
a <= b: true
a >= b: false
a == a: true
a != b: true

=== Raw pointer arithmetic ===
*ptr       = 100
*(ptr + 2) = 300
ptr[3]     = 400
end - begin = 5
Sorted array: 100 200 300 400 500

=== Subscript operator ===
Accessing via it[i]:
  it[0] = 10
  it[1] = 20
  it[2] = 30
  it[3] = 40
  it[4] = 50
  it[5] = 60
  it[6] = 70
  it[7] = 80

=== Algorithms requiring random access ===
Sorted: 10 20 30 40 50
Median (3rd element): 30
Shuffled: X X X X X (random order)

=== Deque random access ===
dit[0] = 11
dit[2] = 33
*(dit + 3) = 44

=== Random access iterator properties ===
1. Supports all bidirectional operations PLUS:
2. it + n, it - n, it += n, it -= n
3. it1 - it2 (distance)
4. it[n] (subscript)
5. it1 < it2, it1 > it2, it1 <= it2, it1 >= it2
6. Category: std::random_access_iterator_tag
7. Containers: vector, deque, raw pointers (C arrays)
*/
