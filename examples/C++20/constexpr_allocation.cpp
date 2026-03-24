// CodeNebula - C++20 Example: Constexpr Allocation
// Compile: g++ -std=c++20 -Wall -Wextra -o example constexpr_allocation.cpp

// Demonstrates C++20 constexpr new/delete: transient allocation during
// constant evaluation. Memory must be freed before the constexpr context ends.

#include <iostream>
#include <memory>
#include <array>

// ------------------------------------------------------------------
// 1. constexpr function using new/delete (transient allocation)
// ------------------------------------------------------------------
constexpr int sum_with_buffer(int n) {
    int* buffer = new int[n];
    for (int i = 0; i < n; ++i)
        buffer[i] = i + 1;

    int total = 0;
    for (int i = 0; i < n; ++i)
        total += buffer[i];

    delete[] buffer;  // Must free before returning
    return total;
}

// ------------------------------------------------------------------
// 2. constexpr dynamic array reversal
// ------------------------------------------------------------------
constexpr auto reverse_array(const int* input, int n) {
    struct Result {
        int data[10]{};
        int size = 0;
    };

    int* temp = new int[n];
    for (int i = 0; i < n; ++i)
        temp[i] = input[n - 1 - i];

    Result r;
    r.size = n;
    for (int i = 0; i < n; ++i)
        r.data[i] = temp[i];

    delete[] temp;
    return r;
}

// ------------------------------------------------------------------
// 3. constexpr linked list with new/delete
// ------------------------------------------------------------------
struct Node {
    int value;
    Node* next;
};

constexpr int sum_linked_list(int n) {
    // Build linked list: 1 -> 2 -> 3 -> ... -> n
    Node* head = nullptr;
    for (int i = n; i >= 1; --i) {
        Node* node = new Node{i, head};
        head = node;
    }

    // Sum all values
    int total = 0;
    Node* curr = head;
    while (curr) {
        total += curr->value;
        curr = curr->next;
    }

    // Free all nodes
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    return total;
}

// ------------------------------------------------------------------
// 4. constexpr unique_ptr-like RAII wrapper
// ------------------------------------------------------------------
constexpr int demo_raii_allocation() {
    // Use a simple scope-based pattern
    int* p = new int(42);
    int val = *p;
    *p = val * 2;
    int result = *p;
    delete p;
    return result;
}

// ------------------------------------------------------------------
// 5. constexpr sorting with dynamic buffer
// ------------------------------------------------------------------
constexpr auto sort_values(std::initializer_list<int> init) {
    struct SortedResult {
        int data[10]{};
        int size = 0;
    };

    int n = static_cast<int>(init.size());
    int* buf = new int[n];

    int idx = 0;
    for (int v : init)
        buf[idx++] = v;

    // Bubble sort
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (buf[j] > buf[j + 1]) {
                int tmp = buf[j];
                buf[j] = buf[j + 1];
                buf[j + 1] = tmp;
            }

    SortedResult r;
    r.size = n;
    for (int i = 0; i < n; ++i)
        r.data[i] = buf[i];

    delete[] buf;
    return r;
}

int main()
{
    std::cout << "=== constexpr new/delete ===" << std::endl;
    constexpr int s5 = sum_with_buffer(5);     // 1+2+3+4+5
    constexpr int s10 = sum_with_buffer(10);   // 1+2+...+10
    std::cout << "  sum(1..5) = " << s5 << std::endl;
    std::cout << "  sum(1..10) = " << s10 << std::endl;
    static_assert(s5 == 15);
    static_assert(s10 == 55);

    std::cout << "\n=== constexpr Dynamic Reversal ===" << std::endl;
    constexpr int input[] = {10, 20, 30, 40, 50};
    constexpr auto rev = reverse_array(input, 5);
    std::cout << "  Reversed:";
    for (int i = 0; i < rev.size; ++i)
        std::cout << " " << rev.data[i];
    std::cout << std::endl;

    std::cout << "\n=== constexpr Linked List ===" << std::endl;
    constexpr int ll5 = sum_linked_list(5);
    constexpr int ll100 = sum_linked_list(100);
    std::cout << "  Linked list sum(1..5) = " << ll5 << std::endl;
    std::cout << "  Linked list sum(1..100) = " << ll100 << std::endl;
    static_assert(ll100 == 5050);

    std::cout << "\n=== constexpr RAII-like ===" << std::endl;
    constexpr int raii = demo_raii_allocation();
    std::cout << "  42 * 2 = " << raii << std::endl;

    std::cout << "\n=== constexpr Sort with Dynamic Buffer ===" << std::endl;
    constexpr auto sorted = sort_values({9, 3, 7, 1, 5, 2, 8, 4, 6, 0});
    std::cout << "  Sorted:";
    for (int i = 0; i < sorted.size; ++i)
        std::cout << " " << sorted.data[i];
    std::cout << std::endl;

    std::cout << "\n  All static_asserts passed" << std::endl;

    return 0;
}

/*
Expected output:

=== constexpr new/delete ===
  sum(1..5) = 15
  sum(1..10) = 55

=== constexpr Dynamic Reversal ===
  Reversed: 50 40 30 20 10

=== constexpr Linked List ===
  Linked list sum(1..5) = 15
  Linked list sum(1..100) = 5050

=== constexpr RAII-like ===
  42 * 2 = 84

=== constexpr Sort with Dynamic Buffer ===
  Sorted: 0 1 2 3 4 5 6 7 8 9

  All static_asserts passed
*/
