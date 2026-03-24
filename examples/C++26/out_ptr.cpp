// CodeNebula - C++26 Example: std::out_ptr / std::inout_ptr Improvements
// Compile: g++ -std=c++26 -Wall -Wextra -o example out_ptr.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <memory>

// C++23 introduced out_ptr/inout_ptr for C-API interop (T** params).
// C++26 adds: shared_ptr support, better constexpr, improved CTAD.
//   out_ptr(smart_ptr)   - for APIs writing to uninitialized T**
//   inout_ptr(smart_ptr) - for APIs that release old and write new T**

struct Resource { int id; Resource(int i) : id(i) {} };

int c_create(Resource** out, int id) { *out = new Resource(id); return 0; }
int c_replace(Resource** io, int new_id) { delete *io; *io = new Resource(new_id); return 0; }

int main() {
    std::cout << "--- std::out_ptr (C++26) ---\n\n";

    // out_ptr: acquire from C API. Real: c_create(std::out_ptr(res), 42);
    std::unique_ptr<Resource> res;
    { Resource* raw = nullptr; c_create(&raw, 42); res.reset(raw); }
    std::cout << "Created id: " << res->id << "\n";

    // inout_ptr: replace via C API. Real: c_replace(std::inout_ptr(res), 99);
    { Resource* raw = res.release(); c_replace(&raw, 99); res.reset(raw); }
    std::cout << "Replaced id: " << res->id << "\n";

    // C++26: shared_ptr support
    std::cout << "\n--- shared_ptr support ---\n";
    std::shared_ptr<Resource> shared;
    { Resource* raw = nullptr; c_create(&raw, 77); shared.reset(raw); }
    std::cout << "Shared id: " << shared->id << ", use_count: " << shared.use_count() << "\n";
    auto copy = shared;
    std::cout << "After copy, use_count: " << shared.use_count() << "\n";

    std::cout << "\nout_ptr/inout_ptr: safe C-API smart pointer interop.\n";
    return 0;
}

// Expected output:
// --- std::out_ptr (C++26) ---
//
// Created id: 42
// Replaced id: 99
//
// --- shared_ptr support ---
// Shared id: 77, use_count: 1
// After copy, use_count: 2
//
// out_ptr/inout_ptr: safe C-API smart pointer interop.
