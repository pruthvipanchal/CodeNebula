// CodeNebula - C++23 Example: std::out_ptr
// Compile: g++ -std=c++23 -Wall -Wextra -o example out_ptr.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <memory>

// std::out_ptr and std::inout_ptr adapt smart pointers for C-style APIs
// that take T** output parameters (e.g., create/get functions).

// Simulated C-style API: creates a resource, returns via out-parameter
struct CResource {
    int id;
    const char* name;
};

int c_create_resource(CResource** out, int id) {
    if (!out) return -1;
    *out = new CResource{id, "MyResource"};
    return 0;  // success
}

void c_free_resource(CResource* res) {
    delete res;
}

// Another C API: replaces an existing resource (inout pattern)
int c_replace_resource(CResource** inout, int new_id) {
    if (!inout) return -1;
    if (*inout) {
        c_free_resource(*inout);
    }
    *inout = new CResource{new_id, "ReplacedResource"};
    return 0;
}

// Custom deleter for unique_ptr
struct ResourceDeleter {
    void operator()(CResource* r) const {
        std::cout << "  Deleting resource id=" << r->id << "\n";
        c_free_resource(r);
    }
};

using ResourcePtr = std::unique_ptr<CResource, ResourceDeleter>;

int main() {
    std::cout << "=== std::out_ptr for C API interop ===\n\n";

    // --- std::out_ptr: acquire a new resource ---
    std::cout << "Creating resource with std::out_ptr:\n";
    ResourcePtr res;
    int err = c_create_resource(std::out_ptr(res), 42);
    if (err == 0) {
        std::cout << "  Resource created: id=" << res->id
                  << ", name=" << res->name << "\n";
    }

    // --- std::inout_ptr: replace an existing resource ---
    std::cout << "\nReplacing resource with std::inout_ptr:\n";
    err = c_replace_resource(std::inout_ptr(res), 99);
    if (err == 0) {
        std::cout << "  Resource replaced: id=" << res->id
                  << ", name=" << res->name << "\n";
    }

    // --- out_ptr with shared_ptr ---
    std::cout << "\nUsing out_ptr with shared_ptr:\n";
    std::shared_ptr<CResource> shared_res;
    err = c_create_resource(
        std::out_ptr(shared_res, ResourceDeleter{}), 77);
    if (err == 0) {
        std::cout << "  Shared resource: id=" << shared_res->id
                  << ", use_count=" << shared_res.use_count() << "\n";
    }

    std::cout << "\nResources cleaned up automatically on scope exit:\n";
    return 0;
}

// Expected output:
// === std::out_ptr for C API interop ===
//
// Creating resource with std::out_ptr:
//   Resource created: id=42, name=MyResource
//
// Replacing resource with std::inout_ptr:
//   Deleting resource id=42
//   Resource replaced: id=99, name=ReplacedResource
//
// Using out_ptr with shared_ptr:
//   Shared resource: id=77, use_count=1
//
// Resources cleaned up automatically on scope exit:
//   Deleting resource id=77
//   Deleting resource id=99
