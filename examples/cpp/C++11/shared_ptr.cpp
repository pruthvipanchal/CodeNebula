// CodeNebula - C++11 Example: std::shared_ptr
// Compile: g++ -std=c++11 -Wall -Wextra -o example shared_ptr.cpp
//
// This example demonstrates:
// - std::shared_ptr for shared ownership of heap objects
// - Reference counting and automatic deletion
// - std::make_shared for efficient allocation
// - Custom deleters
// - use_count() to observe reference counts

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================================
// 1. A class to track construction/destruction
// ============================================================
class Resource {
    std::string name_;
public:
    Resource(const std::string& name) : name_(name) {
        std::cout << "  Resource \"" << name_ << "\" created" << std::endl;
    }

    ~Resource() {
        std::cout << "  Resource \"" << name_ << "\" destroyed" << std::endl;
    }

    void use() const {
        std::cout << "  Using resource: " << name_ << std::endl;
    }

    const std::string& name() const { return name_; }
};

// ============================================================
// 2. Function that shares ownership
// ============================================================
void holdReference(std::shared_ptr<Resource> ptr) {
    std::cout << "  holdReference: use_count = " << ptr.use_count() << std::endl;
    ptr->use();
}

// ============================================================
// 3. Factory that returns shared_ptr
// ============================================================
std::shared_ptr<Resource> createResource(const std::string& name) {
    return std::make_shared<Resource>(name);
}

int main() {
    std::cout << "=== std::shared_ptr ===" << std::endl;

    // Basic creation and usage
    std::cout << "\n--- Basic usage ---" << std::endl;
    {
        std::shared_ptr<Resource> p1 = std::make_shared<Resource>("Alpha");
        std::cout << "  use_count: " << p1.use_count() << std::endl;

        {
            std::shared_ptr<Resource> p2 = p1;  // Shared ownership
            std::cout << "  After copy, use_count: " << p1.use_count() << std::endl;
            p2->use();
        }
        std::cout << "  After p2 scope, use_count: " << p1.use_count() << std::endl;
    }
    std::cout << "  After all scopes: resource destroyed" << std::endl;

    // make_shared vs constructor
    std::cout << "\n--- make_shared vs new ---" << std::endl;
    auto sp1 = std::make_shared<Resource>("Efficient");  // Single allocation
    std::shared_ptr<Resource> sp2(new Resource("Two-alloc"));  // Two allocations
    sp1.reset();
    sp2.reset();

    // Sharing across function calls
    std::cout << "\n--- Shared across functions ---" << std::endl;
    {
        auto res = createResource("Shared");
        std::cout << "  Before call: use_count = " << res.use_count() << std::endl;
        holdReference(res);
        std::cout << "  After call: use_count = " << res.use_count() << std::endl;
    }

    // Container of shared_ptrs
    std::cout << "\n--- Container of shared_ptr ---" << std::endl;
    {
        std::vector<std::shared_ptr<Resource>> resources;
        auto r1 = std::make_shared<Resource>("DB");
        auto r2 = std::make_shared<Resource>("Cache");

        resources.push_back(r1);
        resources.push_back(r2);
        resources.push_back(r1);  // r1 shared again

        std::cout << "  r1 use_count: " << r1.use_count() << std::endl;
        std::cout << "  r2 use_count: " << r2.use_count() << std::endl;

        resources.clear();
        std::cout << "  After clear, r1 use_count: " << r1.use_count() << std::endl;
    }

    // Custom deleter
    std::cout << "\n--- Custom deleter ---" << std::endl;
    {
        auto deleter = [](Resource* p) {
            std::cout << "  Custom deleter for: " << p->name() << std::endl;
            delete p;
        };
        std::shared_ptr<Resource> custom(new Resource("Custom"), deleter);
        custom->use();
    }

    // Checking for null
    std::cout << "\n--- Null and boolean checks ---" << std::endl;
    std::shared_ptr<int> empty;
    std::shared_ptr<int> valid = std::make_shared<int>(42);
    std::cout << "  empty is null: " << (empty ? "no" : "yes") << std::endl;
    std::cout << "  valid is null: " << (valid ? "no" : "yes") << std::endl;
    std::cout << "  *valid = " << *valid << std::endl;

    return 0;
}

// Expected output:
// === std::shared_ptr ===
//
// --- Basic usage ---
//   Resource "Alpha" created
//   use_count: 1
//   After copy, use_count: 2
//   Using resource: Alpha
//   After p2 scope, use_count: 1
//   Resource "Alpha" destroyed
//   After all scopes: resource destroyed
//
// --- make_shared vs new ---
//   Resource "Efficient" created
//   Resource "Two-alloc" created
//   Resource "Efficient" destroyed
//   Resource "Two-alloc" destroyed
//
// --- Shared across functions ---
//   Resource "Shared" created
//   Before call: use_count = 1
//   holdReference: use_count = 2
//   Using resource: Shared
//   After call: use_count = 1
//   Resource "Shared" destroyed
//
// --- Container of shared_ptr ---
//   Resource "DB" created
//   Resource "Cache" created
//   r1 use_count: 3
//   r2 use_count: 2
//   After clear, r1 use_count: 1
//   Resource "Cache" destroyed
//   Resource "DB" destroyed
//
// --- Custom deleter ---
//   Resource "Custom" created
//   Using resource: Custom
//   Custom deleter for: Custom
//   Resource "Custom" destroyed
//
// --- Null and boolean checks ---
//   empty is null: yes
//   valid is null: no
//   *valid = 42
