// CodeNebula - C++17 Example: std::pmr::unsynchronized_pool_resource
// Compile: g++ -std=c++17 -Wall -Wextra -o example unsynchronized_pool_resource.cpp

// Demonstrates std::pmr::unsynchronized_pool_resource, a pool-based memory
// resource for single-threaded use. Unlike monotonic_buffer_resource, it
// recycles deallocated blocks, making it suitable for mixed alloc/dealloc
// patterns where memory reuse matters.

#include <iostream>
#include <memory_resource>
#include <vector>
#include <list>
#include <string>

// Tracking resource to observe upstream allocations
class UpstreamTracker : public std::pmr::memory_resource {
    std::size_t total_ = 0;
    std::size_t count_ = 0;
    std::pmr::memory_resource* upstream_;
public:
    explicit UpstreamTracker(std::pmr::memory_resource* up = std::pmr::get_default_resource())
        : upstream_(up) {}
    std::size_t total() const { return total_; }
    std::size_t count() const { return count_; }
protected:
    void* do_allocate(std::size_t bytes, std::size_t align) override {
        total_ += bytes;
        ++count_;
        return upstream_->allocate(bytes, align);
    }
    void do_deallocate(void* p, std::size_t bytes, std::size_t align) override {
        upstream_->deallocate(p, bytes, align);
    }
    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return this == &other;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic usage with a list (frequent small allocations)
    // ------------------------------------------------------------------
    std::cout << "=== Basic Pool Usage ===" << std::endl;
    UpstreamTracker tracker;
    std::pmr::unsynchronized_pool_resource pool(&tracker);

    std::pmr::list<int> lst(&pool);
    for (int i = 1; i <= 10; ++i) lst.push_back(i);

    std::cout << "  List: ";
    for (int x : lst) std::cout << x << " ";
    std::cout << std::endl;
    std::cout << "  Upstream allocs: " << tracker.count() << std::endl;

    // ------------------------------------------------------------------
    // 2. Memory reuse after deallocation
    // ------------------------------------------------------------------
    std::cout << "\n=== Memory Reuse ===" << std::endl;
    UpstreamTracker tracker2;
    std::pmr::unsynchronized_pool_resource reuse_pool(&tracker2);

    // Allocate and deallocate in a loop -- pool reuses freed blocks
    for (int round = 0; round < 5; ++round) {
        std::pmr::vector<int> temp(&reuse_pool);
        for (int i = 0; i < 20; ++i) temp.push_back(i);
        // temp is destroyed, memory returned to pool (not upstream)
    }

    std::cout << "  After 5 rounds of alloc/dealloc:" << std::endl;
    std::cout << "  Upstream allocs: " << tracker2.count()
              << " (pool reused blocks)" << std::endl;

    // ------------------------------------------------------------------
    // 3. Pool options
    // ------------------------------------------------------------------
    std::cout << "\n=== Custom Pool Options ===" << std::endl;
    std::pmr::pool_options opts;
    opts.max_blocks_per_chunk = 16;
    opts.largest_required_pool_block = 256;

    UpstreamTracker tracker3;
    std::pmr::unsynchronized_pool_resource custom_pool(opts, &tracker3);

    std::pmr::vector<int> v(&custom_pool);
    for (int i = 0; i < 50; ++i) v.push_back(i);

    std::cout << "  max_blocks_per_chunk      = 16" << std::endl;
    std::cout << "  largest_required_pool_block = 256" << std::endl;
    std::cout << "  Stored " << v.size() << " elements" << std::endl;
    std::cout << "  Upstream allocs: " << tracker3.count() << std::endl;

    // ------------------------------------------------------------------
    // 4. release() returns all memory to upstream
    // ------------------------------------------------------------------
    std::cout << "\n=== release() ===" << std::endl;
    {
        UpstreamTracker tracker4;
        std::pmr::unsynchronized_pool_resource rel_pool(&tracker4);
        std::pmr::vector<int> temp(&rel_pool);
        for (int i = 0; i < 100; ++i) temp.push_back(i);
        temp.clear();

        std::cout << "  Before release: upstream allocs = " << tracker4.count() << std::endl;
        rel_pool.release();
        std::cout << "  After release: all blocks returned to upstream" << std::endl;
    }

    return 0;
}

/*
Expected output (counts may vary by implementation):

=== Basic Pool Usage ===
  List: 1 2 3 4 5 6 7 8 9 10
  Upstream allocs: 2

=== Memory Reuse ===
  After 5 rounds of alloc/dealloc:
  Upstream allocs: 4 (pool reused blocks)

=== Custom Pool Options ===
  max_blocks_per_chunk      = 16
  largest_required_pool_block = 256
  Stored 50 elements
  Upstream allocs: 3

=== release() ===
  Before release: upstream allocs = 3
  After release: all blocks returned to upstream
*/
