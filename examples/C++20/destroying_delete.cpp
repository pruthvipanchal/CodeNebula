// CodeNebula - C++20 Example: std::destroying_delete_t
// Compile: g++ -std=c++20 -Wall -Wextra -o example destroying_delete.cpp

// std::destroying_delete_t lets operator delete receive the object
// BEFORE the destructor runs. This enables:
//   1. Custom deallocation based on runtime object state
//   2. Variable-size allocations where the object knows its true size
//   3. Classes that control their own destruction sequence

#include <iostream>
#include <new>
#include <cstdlib>
#include <cstring>

// --- Example 1: Object that tracks its own allocation size ---
struct FlexibleBuffer {
    std::size_t alloc_size;
    char data[1];  // flexible array member pattern

    // Factory: allocate extra bytes for the data
    static FlexibleBuffer* create(std::size_t data_size) {
        std::size_t total = sizeof(FlexibleBuffer) + data_size - 1;
        void* mem = ::operator new(total);
        auto* obj = new (mem) FlexibleBuffer();
        obj->alloc_size = total;
        std::memset(obj->data, 0, data_size);
        std::cout << "  Allocated " << total << " bytes\n";
        return obj;
    }

    // Destroying delete: we get the object before destruction
    void operator delete(FlexibleBuffer* ptr, std::destroying_delete_t) {
        std::size_t size = ptr->alloc_size;  // read BEFORE destroying
        ptr->~FlexibleBuffer();               // manually call destructor
        std::cout << "  Deallocating " << size << " bytes\n";
        ::operator delete(ptr);
    }
};

// --- Example 2: Prevent deletion of derived types through base pointer ---
struct SafeBase {
    int id;
    SafeBase(int i) : id(i) { std::cout << "  SafeBase(" << id << ") constructed\n"; }
    ~SafeBase() { std::cout << "  SafeBase(" << id << ") destroyed\n"; }

    // This destroying delete controls the deletion process
    void operator delete(SafeBase* ptr, std::destroying_delete_t) {
        std::cout << "  Destroying delete called for SafeBase id=" << ptr->id << "\n";
        ptr->~SafeBase();
        ::operator delete(ptr);
    }
};

// --- Example 3: Conditional destruction ---
struct MaybePooled {
    bool from_pool;
    int value;

    MaybePooled(bool pooled, int v) : from_pool(pooled), value(v) {
        std::cout << "  Created MaybePooled(" << value << ") "
                  << (from_pool ? "[pooled]" : "[heap]") << "\n";
    }

    ~MaybePooled() {
        std::cout << "  Destroyed MaybePooled(" << value << ")\n";
    }

    void operator delete(MaybePooled* ptr, std::destroying_delete_t) {
        bool pooled = ptr->from_pool;
        int val = ptr->value;
        ptr->~MaybePooled();  // manually destroy

        if (pooled) {
            std::cout << "  Returning " << val << " to pool (simulated)\n";
            ::operator delete(ptr);  // in real code, return to pool
        } else {
            std::cout << "  Freeing " << val << " from heap\n";
            ::operator delete(ptr);
        }
    }
};

int main() {
    std::cout << "=== std::destroying_delete_t ===\n\n";

    // Example 1: Variable-size deallocation
    std::cout << "FlexibleBuffer (100 bytes of data):\n";
    FlexibleBuffer* buf = FlexibleBuffer::create(100);
    delete buf;
    std::cout << "\n";

    // Example 2: SafeBase deletion
    std::cout << "SafeBase:\n";
    SafeBase* sb = new SafeBase(42);
    delete sb;
    std::cout << "\n";

    // Example 3: Conditional deallocation strategy
    std::cout << "Conditional deallocation:\n";
    MaybePooled* heap_obj = new MaybePooled(false, 10);
    MaybePooled* pool_obj = new MaybePooled(true, 20);
    delete heap_obj;
    delete pool_obj;

    std::cout << "\nKey point: destroying_delete receives the live object,\n"
              << "so it can inspect state before calling the destructor.\n";

    return 0;
}

// Expected output:
// === std::destroying_delete_t ===
//
// FlexibleBuffer (100 bytes of data):
//   Allocated ... bytes
//   Deallocating ... bytes
//
// SafeBase:
//   SafeBase(42) constructed
//   Destroying delete called for SafeBase id=42
//   SafeBase(42) destroyed
//
// Conditional deallocation:
//   Created MaybePooled(10) [heap]
//   Created MaybePooled(20) [pooled]
//   Destroyed MaybePooled(10)
//   Freeing 10 from heap
//   Destroyed MaybePooled(20)
//   Returning 20 to pool (simulated)
//
// Key point: destroying_delete receives the live object,
// so it can inspect state before calling the destructor.
