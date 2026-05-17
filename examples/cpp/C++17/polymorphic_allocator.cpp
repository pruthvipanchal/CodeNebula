// CodeNebula - C++17 Example: std::pmr::polymorphic_allocator
// Compile: g++ -std=c++17 -Wall -Wextra -o example polymorphic_allocator.cpp

// Demonstrates std::pmr::polymorphic_allocator, which wraps a memory_resource
// pointer and satisfies the Allocator concept. Unlike traditional allocators,
// containers with different underlying resources share the same type.

#include <iostream>
#include <memory_resource>
#include <vector>
#include <string>
#include <array>

// Logging resource to observe allocation patterns
class TrackingResource : public std::pmr::memory_resource {
    std::size_t total_allocated_ = 0;
    std::size_t alloc_count_ = 0;
    std::pmr::memory_resource* upstream_;
public:
    explicit TrackingResource(std::pmr::memory_resource* up = std::pmr::get_default_resource())
        : upstream_(up) {}

    std::size_t total_allocated() const { return total_allocated_; }
    std::size_t alloc_count() const { return alloc_count_; }

protected:
    void* do_allocate(std::size_t bytes, std::size_t align) override {
        total_allocated_ += bytes;
        ++alloc_count_;
        return upstream_->allocate(bytes, align);
    }
    void do_deallocate(void* p, std::size_t bytes, std::size_t align) override {
        upstream_->deallocate(p, bytes, align);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

// Function that accepts ANY pmr::vector<int> regardless of resource
void print_vec(const std::pmr::vector<int>& v, const std::string& label) {
    std::cout << "  " << label << ": ";
    for (int x : v) std::cout << x << " ";
    std::cout << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Same container type, different resources
    // ------------------------------------------------------------------
    std::cout << "=== Same Type, Different Resources ===" << std::endl;
    TrackingResource tracker1, tracker2;

    std::pmr::vector<int> v1(&tracker1);
    std::pmr::vector<int> v2(&tracker2);

    v1 = {1, 2, 3, 4, 5};
    v2 = {10, 20, 30};

    print_vec(v1, "v1 (tracker1)");
    print_vec(v2, "v2 (tracker2)");
    std::cout << "  v1 and v2 are same type: "
              << std::is_same_v<decltype(v1), decltype(v2)> << std::endl;

    // ------------------------------------------------------------------
    // 2. Tracking allocations
    // ------------------------------------------------------------------
    std::cout << "\n=== Allocation Tracking ===" << std::endl;
    std::cout << "  tracker1: " << tracker1.alloc_count() << " allocs, "
              << tracker1.total_allocated() << " bytes" << std::endl;
    std::cout << "  tracker2: " << tracker2.alloc_count() << " allocs, "
              << tracker2.total_allocated() << " bytes" << std::endl;

    // ------------------------------------------------------------------
    // 3. Stack-based allocation via monotonic_buffer_resource
    // ------------------------------------------------------------------
    std::cout << "\n=== Stack Buffer ===" << std::endl;
    std::array<std::byte, 256> stack_buf{};
    std::pmr::monotonic_buffer_resource pool(
        stack_buf.data(), stack_buf.size(), std::pmr::null_memory_resource()
    );

    std::pmr::vector<int> stack_vec(&pool);
    for (int i = 0; i < 10; ++i) stack_vec.push_back(i * i);

    print_vec(stack_vec, "stack_vec");
    std::cout << "  (Allocated entirely from stack buffer)" << std::endl;

    // ------------------------------------------------------------------
    // 4. polymorphic_allocator properties
    // ------------------------------------------------------------------
    std::cout << "\n=== Allocator Properties ===" << std::endl;
    auto alloc = v1.get_allocator();
    std::cout << "  resource() == &tracker1: " << (alloc.resource() == &tracker1) << std::endl;
    std::cout << "  v1.alloc == v2.alloc:    " << (v1.get_allocator() == v2.get_allocator()) << std::endl;

    return 0;
}

/*
Expected output:

=== Same Type, Different Resources ===
  v1 (tracker1): 1 2 3 4 5
  v2 (tracker2): 10 20 30
  v1 and v2 are same type: 1

=== Allocation Tracking ===
  tracker1: 1 allocs, 20 bytes
  tracker2: 1 allocs, 12 bytes

=== Stack Buffer ===
  stack_vec: 0 1 4 9 16 25 36 49 64 81
  (Allocated entirely from stack buffer)

=== Allocator Properties ===
  resource() == &tracker1: 1
  v1.alloc == v2.alloc:    0
*/
