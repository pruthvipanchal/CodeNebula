// CodeNebula - C++17 Example: std::pmr::memory_resource
// Compile: g++ -std=c++17 -Wall -Wextra -o example memory_resource.cpp

// Demonstrates std::pmr::memory_resource, the abstract base class for
// polymorphic allocators. Shows how to implement a custom memory resource,
// use the default/null resources, and swap resources at runtime.

#include <iostream>
#include <memory_resource>
#include <vector>
#include <cstdlib>

// ------------------------------------------------------------------
// Custom memory resource that logs allocations
// ------------------------------------------------------------------
class LoggingResource : public std::pmr::memory_resource {
    std::string name_;
    std::pmr::memory_resource* upstream_;

public:
    explicit LoggingResource(std::string name,
                             std::pmr::memory_resource* up = std::pmr::get_default_resource())
        : name_(std::move(name)), upstream_(up) {}

protected:
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        std::cout << "  [" << name_ << "] allocate(" << bytes
                  << ", align=" << alignment << ")" << std::endl;
        return upstream_->allocate(bytes, alignment);
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        std::cout << "  [" << name_ << "] deallocate(" << bytes << ")" << std::endl;
        upstream_->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Default and null memory resources
    // ------------------------------------------------------------------
    std::cout << "=== Built-in Resources ===" << std::endl;
    auto* def  = std::pmr::get_default_resource();
    auto* null_res = std::pmr::null_memory_resource();
    std::cout << "  default resource  : " << def << std::endl;
    std::cout << "  null resource     : " << null_res << std::endl;
    std::cout << "  Are they equal?   : " << (*def == *null_res) << std::endl;

    // ------------------------------------------------------------------
    // 2. Custom logging resource
    // ------------------------------------------------------------------
    std::cout << "\n=== Custom Logging Resource ===" << std::endl;
    LoggingResource logger("MyAlloc");

    std::pmr::vector<int> vec(&logger);
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    std::cout << "  vec contents: ";
    for (int v : vec) std::cout << v << " ";
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. null_memory_resource always throws on allocate
    // ------------------------------------------------------------------
    std::cout << "\n=== Null Resource ===" << std::endl;
    try {
        null_res->allocate(1);
    } catch (const std::bad_alloc& e) {
        std::cout << "  null_memory_resource threw: " << e.what() << std::endl;
    }

    // ------------------------------------------------------------------
    // 4. Setting a new default resource
    // ------------------------------------------------------------------
    std::cout << "\n=== Set Default Resource ===" << std::endl;
    LoggingResource global_logger("Global");
    std::pmr::memory_resource* old = std::pmr::set_default_resource(&global_logger);

    // Now any pmr container using default resource will use our logger
    std::pmr::vector<int> vec2;  // Uses new default
    vec2.push_back(42);

    std::cout << "  vec2[0] = " << vec2[0] << std::endl;

    // Restore original default
    std::pmr::set_default_resource(old);
    std::cout << "  Default resource restored" << std::endl;

    return 0;
}

/*
Expected output (addresses vary):

=== Built-in Resources ===
  default resource  : 0x...
  null resource     : 0x...
  Are they equal?   : 0

=== Custom Logging Resource ===
  [MyAlloc] allocate(4, align=4)
  [MyAlloc] allocate(8, align=4)
  [MyAlloc] deallocate(4)
  [MyAlloc] allocate(16, align=4)
  [MyAlloc] deallocate(8)
  vec contents: 10 20 30

=== Null Resource ===
  null_memory_resource threw: bad_alloc

=== Set Default Resource ===
  [Global] allocate(4, align=4)
  vec2[0] = 42
  Default resource restored
*/
