// CodeNebula - C++98 Example: forward_iterator
// Compile: g++ -std=c++98 -Wall -Wextra -o example forward_iterator.cpp

// Forward iterators support multi-pass forward traversal (++ but not --).
// They can read and write elements, and the same range can be traversed
// multiple times. In C++98, there is no std::forward_list, but we can
// demonstrate the concept with a custom singly-linked list.

#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>

// A simple singly-linked list node
template <typename T>
struct SListNode {
    T data;
    SListNode* next;
    SListNode(const T& val) : data(val), next(NULL) {}
};

// A simple singly-linked list with a forward iterator
template <typename T>
class SList {
public:
    // --- Forward Iterator class ---
    class iterator {
    public:
        // Required typedefs for iterator_traits
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef std::ptrdiff_t            difference_type;
        typedef T*                        pointer;
        typedef T&                        reference;

        iterator() : node_(NULL) {}
        explicit iterator(SListNode<T>* n) : node_(n) {}

        reference operator*() const { return node_->data; }
        pointer operator->() const { return &(node_->data); }

        iterator& operator++() {
            node_ = node_->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            node_ = node_->next;
            return tmp;
        }

        bool operator==(const iterator& other) const { return node_ == other.node_; }
        bool operator!=(const iterator& other) const { return node_ != other.node_; }

    private:
        SListNode<T>* node_;
    };

    // --- Const Forward Iterator class ---
    class const_iterator {
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef std::ptrdiff_t            difference_type;
        typedef const T*                  pointer;
        typedef const T&                  reference;

        const_iterator() : node_(NULL) {}
        explicit const_iterator(const SListNode<T>* n) : node_(n) {}
        const_iterator(const iterator& it) : node_(NULL) {
            // Conversion from iterator to const_iterator
            // This is a simplified version; in production code you'd store the node
            (void)it;
        }

        reference operator*() const { return node_->data; }
        pointer operator->() const { return &(node_->data); }

        const_iterator& operator++() {
            node_ = node_->next;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            node_ = node_->next;
            return tmp;
        }

        bool operator==(const const_iterator& other) const { return node_ == other.node_; }
        bool operator!=(const const_iterator& other) const { return node_ != other.node_; }

    private:
        const SListNode<T>* node_;
    };

    SList() : head_(NULL), size_(0) {}

    ~SList() {
        while (head_) {
            SListNode<T>* next = head_->next;
            delete head_;
            head_ = next;
        }
    }

    void push_front(const T& val) {
        SListNode<T>* node = new SListNode<T>(val);
        node->next = head_;
        head_ = node;
        ++size_;
    }

    iterator begin() { return iterator(head_); }
    iterator end()   { return iterator(NULL); }

    const_iterator begin() const { return const_iterator(head_); }
    const_iterator end() const   { return const_iterator(NULL); }

    std::size_t size() const { return size_; }
    bool empty() const { return head_ == NULL; }

private:
    SListNode<T>* head_;
    std::size_t size_;

    // Prevent copying for simplicity
    SList(const SList&);
    SList& operator=(const SList&);
};

int main() {
    // --- Create and populate the singly-linked list ---
    std::cout << "=== Singly-linked list with forward iterator ===" << std::endl;
    SList<int> slist;
    slist.push_front(50);
    slist.push_front(40);
    slist.push_front(30);
    slist.push_front(20);
    slist.push_front(10);

    // --- Forward traversal ---
    std::cout << "Forward traversal: ";
    for (SList<int>::iterator it = slist.begin(); it != slist.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Multi-pass: traverse multiple times ---
    std::cout << "\n=== Multi-pass traversal ===" << std::endl;
    std::cout << "Pass 1: ";
    for (SList<int>::iterator it = slist.begin(); it != slist.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Pass 2: ";
    for (SList<int>::iterator it = slist.begin(); it != slist.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Modifying through the iterator ---
    std::cout << "\n=== Modify through iterator ===" << std::endl;
    for (SList<int>::iterator it = slist.begin(); it != slist.end(); ++it) {
        *it *= 2;
    }
    std::cout << "After doubling: ";
    for (SList<int>::iterator it = slist.begin(); it != slist.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Using std::find with forward iterator ---
    std::cout << "\n=== std::find ===" << std::endl;
    SList<int>::iterator found = std::find(slist.begin(), slist.end(), 60);
    if (found != slist.end()) {
        std::cout << "Found: " << *found << std::endl;
    } else {
        std::cout << "60 not found" << std::endl;
    }

    found = std::find(slist.begin(), slist.end(), 999);
    if (found == slist.end()) {
        std::cout << "999 not found" << std::endl;
    }

    // --- Using std::count with forward iterator ---
    std::cout << "\n=== std::count ===" << std::endl;
    SList<int> dup_list;
    dup_list.push_front(10);
    dup_list.push_front(20);
    dup_list.push_front(10);
    dup_list.push_front(30);
    dup_list.push_front(10);

    int cnt = static_cast<int>(std::count(dup_list.begin(), dup_list.end(), 10));
    std::cout << "Count of 10: " << cnt << std::endl;

    // --- String singly-linked list ---
    std::cout << "\n=== String SList ===" << std::endl;
    SList<std::string> str_list;
    str_list.push_front("cherry");
    str_list.push_front("banana");
    str_list.push_front("apple");

    std::cout << "Strings: ";
    for (SList<std::string>::iterator it = str_list.begin();
         it != str_list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // --- Key properties of forward iterators ---
    std::cout << "\n=== Forward iterator properties ===" << std::endl;
    std::cout << "1. Multi-pass: the same range can be traversed multiple times" << std::endl;
    std::cout << "2. Read/Write: *it can be read and assigned" << std::endl;
    std::cout << "3. Supports: ++it, it++, *it, it == end, it != end" << std::endl;
    std::cout << "4. Does NOT support: --it (backward), it + n, it[n]" << std::endl;
    std::cout << "5. Category: std::forward_iterator_tag" << std::endl;

    return 0;
}

/*
Expected output:
=== Singly-linked list with forward iterator ===
Forward traversal: 10 20 30 40 50

=== Multi-pass traversal ===
Pass 1: 10 20 30 40 50
Pass 2: 10 20 30 40 50

=== Modify through iterator ===
After doubling: 20 40 60 80 100

=== std::find ===
Found: 60
999 not found

=== std::count ===
Count of 10: 3

=== String SList ===
Strings: apple banana cherry

=== Forward iterator properties ===
1. Multi-pass: the same range can be traversed multiple times
2. Read/Write: *it can be read and assigned
3. Supports: ++it, it++, *it, it == end, it != end
4. Does NOT support: --it (backward), it + n, it[n]
5. Category: std::forward_iterator_tag
*/
