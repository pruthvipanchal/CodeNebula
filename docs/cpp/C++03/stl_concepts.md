# C++03 STL Concepts

This document covers evolved C++03 STL concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../../examples/C++03/). Only evolutions from C++98 are included.

## std::vector<bool> Improvements

**Explanation**: C++03 addressed several defects in the `std::vector<bool>` specialization inherited from C++98. The standard clarified the behavior of its proxy reference type, ensured that `swap` works correctly between individual bit references, and tightened the specification so that `flip()` and element access behave consistently across implementations. While `vector<bool>` remains a space-optimized specialization (packing bits rather than storing one `bool` per byte), the C++03 fixes made it more predictable for developers who rely on it for memory-efficient boolean collections.

**Real-World Scenario**: A feature-flag management system for a mobile application stores thousands of A/B test toggles per user session. Using `std::vector<bool>` keeps memory consumption minimal on constrained devices, and the C++03 fixes ensure that swapping two flags or flipping an entire experiment group behaves identically regardless of the target platform.

**Snippet**:
```cpp
#include <iostream>
#include <vector>

int main() {
    // Space-efficient storage of boolean feature flags
    std::vector<bool> featureFlags(8, false);

    // Enable specific experiments
    featureFlags[0] = true;  // Dark mode
    featureFlags[3] = true;  // New checkout flow
    featureFlags[7] = true;  // Push notifications v2

    // C++03 guarantees correct swap between proxy references
    std::cout << "Before swap — flag[0]: " << featureFlags[0]
              << ", flag[3]: " << featureFlags[3] << "\n";

    std::vector<bool>::swap(featureFlags[0], featureFlags[3]);

    std::cout << "After swap  — flag[0]: " << featureFlags[0]
              << ", flag[3]: " << featureFlags[3] << "\n";

    // flip() inverts all flags in one call
    featureFlags.flip();
    std::cout << "After flip  — flag[0]: " << featureFlags[0] << "\n";

    return 0;
}
```

**Example**: [vector_bool_improvements.cpp](../../examples/C++03/vector_bool_improvements.cpp)

## Algorithm Behavior Fixes

**Explanation**: C++03 introduced a set of minor but important corrections to the algorithm specifications in `<algorithm>`. These defect resolutions clarified the number of comparisons and assignments permitted by algorithms like `std::stable_sort`, pinned down the semantics of predicates passed to `std::remove_if` and `std::unique`, and resolved edge cases in `std::nth_element` and `std::partial_sort`. The cumulative effect was a tighter contract between the standard library and its users, making algorithm complexity guarantees and side-effect rules portable across compilers.

**Real-World Scenario**: A financial trading platform sorts millions of incoming order records by timestamp each second. The corrected complexity guarantees for `std::stable_sort` in C++03 give the engineering team confidence that worst-case performance stays within the documented O(N log^2 N) bound (or O(N log N) when extra memory is available), which is critical for meeting exchange-mandated latency windows.

**Snippet**:
```cpp
#include <algorithm>
#include <iostream>
#include <vector>

struct TradeOrder {
    int    id;
    double timestamp;
    double price;
};

bool byTimestamp(const TradeOrder& a, const TradeOrder& b) {
    return a.timestamp < b.timestamp;
}

int main() {
    std::vector<TradeOrder> orders;
    orders.push_back((TradeOrder){1, 1.002, 150.25});
    orders.push_back((TradeOrder){2, 1.001, 150.30});
    orders.push_back((TradeOrder){3, 1.002, 150.10});
    orders.push_back((TradeOrder){4, 1.000, 150.50});

    // stable_sort preserves relative order of equal-timestamp orders
    // C++03 fixes guarantee well-defined comparison counts
    std::stable_sort(orders.begin(), orders.end(), byTimestamp);

    std::cout << "Sorted trade orders:\n";
    for (std::size_t i = 0; i < orders.size(); ++i) {
        std::cout << "  ID " << orders[i].id
                  << "  t=" << orders[i].timestamp
                  << "  $"  << orders[i].price << "\n";
    }

    // remove_if with a well-defined predicate (C++03 tightened rules)
    // Remove orders below a price threshold
    struct BelowThreshold {
        double threshold;
        bool operator()(const TradeOrder& o) const {
            return o.price < threshold;
        }
    };
    BelowThreshold pred;
    pred.threshold = 150.20;

    std::vector<TradeOrder>::iterator newEnd =
        std::remove_if(orders.begin(), orders.end(), pred);
    orders.erase(newEnd, orders.end());

    std::cout << "After filtering cheap orders: "
              << orders.size() << " remaining\n";

    return 0;
}
```

**Example**: [algorithm_behavior_fixes.cpp](../../examples/C++03/algorithm_behavior_fixes.cpp)