// CodeNebula - C++03 Example: std::vector<bool> Improvements
// Compile: g++ -std=c++03 -Wall -Wextra -o vector_bool_improvements vector_bool_improvements.cpp
//
// C++03 improved std::vector<bool> with:
//   - Better defined proxy reference behavior
//   - Proper swap() semantics for individual bits
//   - flip() operation for toggling all bits
//   - Clarified space-efficient packed storage (1 bit per element)

#include <iostream>
#include <vector>
#include <algorithm>

// Helper: print a vector<bool> as a bit pattern
void printBits(const std::string& label, const std::vector<bool>& v) {
    std::cout << "  " << label << ": [";
    for (std::vector<bool>::size_type i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << " ";
    }
    std::cout << "]" << std::endl;
}

int main() {
    std::cout << "=== std::vector<bool> Improvements ===" << std::endl;

    // --------------------------------------------------------
    // Demo 1: Basic construction and packed storage
    // --------------------------------------------------------
    std::cout << "\n--- Demo 1: Construction & Storage ---" << std::endl;

    std::vector<bool> flags(8, false);
    flags[0] = true;
    flags[2] = true;
    flags[5] = true;
    flags[7] = true;

    printBits("flags", flags);
    std::cout << "  Size:     " << flags.size() << " elements" << std::endl;
    std::cout << "  Capacity: " << flags.capacity() << std::endl;

    // Note: vector<bool> stores bits packed — much smaller than vector<char>
    std::vector<char> charFlags(8, 0);
    std::cout << "  vector<bool> is space-optimized (1 bit per element)" << std::endl;

    // --------------------------------------------------------
    // Demo 2: Proxy reference behavior
    // --------------------------------------------------------
    std::cout << "\n--- Demo 2: Proxy References ---" << std::endl;

    std::vector<bool> bits(4, false);
    bits[0] = true;
    bits[2] = true;

    // operator[] returns a proxy reference, not bool&
    // This proxy supports assignment and implicit conversion to bool
    std::vector<bool>::reference ref = bits[1];
    std::cout << "  bits[1] before: " << ref << std::endl;
    ref = true;  // modify through proxy
    std::cout << "  bits[1] after:  " << ref << std::endl;
    printBits("bits", bits);

    // --------------------------------------------------------
    // Demo 3: swap() for individual bits
    // --------------------------------------------------------
    std::cout << "\n--- Demo 3: swap() Individual Bits ---" << std::endl;

    std::vector<bool> v(4, false);
    v[0] = true;
    v[3] = true;
    printBits("Before swap(v[0], v[1])", v);

    // C++03 swap for vector<bool> references
    std::vector<bool>::swap(v[0], v[1]);
    printBits("After  swap(v[0], v[1])", v);

    std::vector<bool>::swap(v[2], v[3]);
    printBits("After  swap(v[2], v[3])", v);

    // --------------------------------------------------------
    // Demo 4: flip() — toggle all bits
    // --------------------------------------------------------
    std::cout << "\n--- Demo 4: flip() All Bits ---" << std::endl;

    std::vector<bool> mask(6, false);
    mask[1] = true;
    mask[3] = true;
    mask[5] = true;
    printBits("Before flip()", mask);

    mask.flip();
    printBits("After  flip()", mask);

    mask.flip();
    printBits("After  flip() again", mask);

    // --------------------------------------------------------
    // Demo 5: Feature flag management pattern
    // --------------------------------------------------------
    std::cout << "\n--- Demo 5: Feature Flag Manager ---" << std::endl;

    // Simulate feature flags for an application
    enum Feature {
        DARK_MODE     = 0,
        NOTIFICATIONS = 1,
        AUTO_SAVE     = 2,
        SPELL_CHECK   = 3,
        CLOUD_SYNC    = 4,
        BETA_FEATURES = 5,
        NUM_FEATURES  = 6
    };

    std::vector<bool> features(NUM_FEATURES, false);
    features[DARK_MODE]     = true;
    features[AUTO_SAVE]     = true;
    features[CLOUD_SYNC]    = true;

    const char* featureNames[] = {
        "Dark Mode", "Notifications", "Auto Save",
        "Spell Check", "Cloud Sync", "Beta Features"
    };

    std::cout << "  Feature Status:" << std::endl;
    for (int i = 0; i < NUM_FEATURES; ++i) {
        std::cout << "    " << featureNames[i] << ": "
                  << (features[i] ? "ON" : "OFF") << std::endl;
    }

    // Count enabled features
    int enabledCount = 0;
    for (std::vector<bool>::size_type i = 0; i < features.size(); ++i) {
        if (features[i]) ++enabledCount;
    }
    std::cout << "  Enabled: " << enabledCount << "/" << NUM_FEATURES << std::endl;

    // --------------------------------------------------------
    // Demo 6: Using with algorithms
    // --------------------------------------------------------
    std::cout << "\n--- Demo 6: Algorithms with vector<bool> ---" << std::endl;

    std::vector<bool> data(8, false);
    data[1] = true;
    data[3] = true;
    data[5] = true;
    data[7] = true;

    // count
    std::cout << "  True count: "
              << std::count(data.begin(), data.end(), true) << std::endl;

    // find first true
    std::vector<bool>::iterator it = std::find(data.begin(), data.end(), true);
    if (it != data.end()) {
        std::cout << "  First true at index: "
                  << (it - data.begin()) << std::endl;
    }

    // reverse
    std::reverse(data.begin(), data.end());
    printBits("After reverse", data);

    std::cout << "\n=== vector<bool>: space-efficient bit container ===" << std::endl;

    return 0;
}

// Expected Output:
// === std::vector<bool> Improvements ===
//
// --- Demo 1: Construction & Storage ---
//   flags: [1 0 1 0 0 1 0 1]
//   Size:     8 elements
//   Capacity: 32
//   vector<bool> is space-optimized (1 bit per element)
//
// --- Demo 2: Proxy References ---
//   bits[1] before: 0
//   bits[1] after:  1
//   bits: [1 1 1 0]
//
// --- Demo 3: swap() Individual Bits ---
//   Before swap(v[0], v[1]): [1 0 0 1]
//   After  swap(v[0], v[1]): [0 1 0 1]
//   After  swap(v[2], v[3]): [0 1 1 0]
//
// --- Demo 4: flip() All Bits ---
//   Before flip(): [0 1 0 1 0 1]
//   After  flip(): [1 0 1 0 1 0]
//   After  flip() again: [0 1 0 1 0 1]
//
// --- Demo 5: Feature Flag Manager ---
//   Feature Status:
//     Dark Mode: ON
//     Notifications: OFF
//     Auto Save: ON
//     Spell Check: OFF
//     Cloud Sync: ON
//     Beta Features: OFF
//   Enabled: 3/6
//
// --- Demo 6: Algorithms with vector<bool> ---
//   True count: 4
//   First true at index: 1
//   After reverse: [1 0 1 0 1 0 1 0]
//
// === vector<bool>: space-efficient bit container ===
