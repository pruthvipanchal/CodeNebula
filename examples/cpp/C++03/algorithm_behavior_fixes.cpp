// CodeNebula - C++03 Example: Algorithm Behavior Fixes
// Compile: g++ -std=c++03 -Wall -Wextra -o algorithm_behavior_fixes algorithm_behavior_fixes.cpp
//
// C++03 clarified and tightened guarantees for several STL algorithms:
//   - stable_sort: guaranteed O(N log²N) without extra memory, O(N log N) with
//   - remove/remove_if: well-defined element relocation semantics
//   - Other minor fixes to algorithm preconditions and postconditions

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <string>
#include <cstdlib>

// ============================================================
// Helpers
// ============================================================
struct Trade {
    std::string symbol;
    double      price;
    int         sequence;  // original order

    Trade(const std::string& s, double p, int seq)
        : symbol(s), price(p), sequence(seq) {}
};

bool compareByPrice(const Trade& a, const Trade& b) {
    return a.price < b.price;
}

void printTrades(const std::string& label, const std::vector<Trade>& trades) {
    std::cout << "  " << label << ":" << std::endl;
    for (std::vector<Trade>::size_type i = 0; i < trades.size(); ++i) {
        std::cout << "    " << trades[i].symbol
                  << " $" << trades[i].price
                  << " (seq=" << trades[i].sequence << ")"
                  << std::endl;
    }
}

void printVec(const std::string& label, const std::vector<int>& v) {
    std::cout << "  " << label << ": ";
    for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

bool isNegative(int x) { return x < 0; }
bool isEven(int x) { return x % 2 == 0; }

int main() {
    std::cout << "=== Algorithm Behavior Fixes ===" << std::endl;

    // --------------------------------------------------------
    // Demo 1: stable_sort — preserves relative order of equal elements
    //         C++03 guarantees: O(N log²N) without extra memory
    // --------------------------------------------------------
    std::cout << "\n--- Demo 1: stable_sort Guarantees ---" << std::endl;

    std::vector<Trade> trades;
    trades.push_back(Trade("AAPL",  150.0, 1));
    trades.push_back(Trade("GOOG",  100.0, 2));
    trades.push_back(Trade("MSFT",  150.0, 3));  // same price as AAPL
    trades.push_back(Trade("AMZN",  100.0, 4));  // same price as GOOG
    trades.push_back(Trade("META",  200.0, 5));
    trades.push_back(Trade("TSLA",  150.0, 6));  // same price as AAPL, MSFT

    printTrades("Before stable_sort", trades);

    std::stable_sort(trades.begin(), trades.end(), compareByPrice);

    printTrades("After stable_sort by price", trades);

    // Verify: elements with same price keep original sequence order
    std::cout << "\n  Stability check (same-price elements keep original order):" << std::endl;
    std::cout << "    $100 group: GOOG(seq=2) before AMZN(seq=4)? "
              << (trades[0].sequence < trades[1].sequence ? "YES" : "NO") << std::endl;
    std::cout << "    $150 group: AAPL(seq=1) < MSFT(seq=3) < TSLA(seq=6)? "
              << ((trades[2].sequence < trades[3].sequence &&
                   trades[3].sequence < trades[4].sequence) ? "YES" : "NO") << std::endl;

    // --------------------------------------------------------
    // Demo 2: sort vs stable_sort comparison
    // --------------------------------------------------------
    std::cout << "\n--- Demo 2: sort vs stable_sort ---" << std::endl;

    // Create data where stability matters
    std::vector<int> data1;
    std::vector<int> data2;
    int values[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    for (int i = 0; i < 10; ++i) {
        data1.push_back(values[i]);
        data2.push_back(values[i]);
    }

    std::sort(data1.begin(), data1.end());
    std::stable_sort(data2.begin(), data2.end());

    printVec("After sort       ", data1);
    printVec("After stable_sort", data2);
    std::cout << "  Both produce sorted output, but stable_sort preserves"
              << " relative order of equal elements" << std::endl;

    // --------------------------------------------------------
    // Demo 3: remove_if — well-defined relocation semantics
    //         C++03 guarantees: elements before the returned iterator
    //         are the ones that don't match the predicate
    // --------------------------------------------------------
    std::cout << "\n--- Demo 3: remove_if Well-Defined Semantics ---" << std::endl;

    std::vector<int> scores;
    scores.push_back(85);
    scores.push_back(-10);   // invalid
    scores.push_back(92);
    scores.push_back(-5);    // invalid
    scores.push_back(78);
    scores.push_back(0);
    scores.push_back(-3);    // invalid
    scores.push_back(95);

    printVec("Before remove_if(negative)", scores);

    // remove_if moves non-matching elements to the front
    std::vector<int>::iterator newEnd =
        std::remove_if(scores.begin(), scores.end(), isNegative);

    std::cout << "  Elements to keep: ";
    for (std::vector<int>::iterator it = scores.begin(); it != newEnd; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // The standard erase-remove idiom
    scores.erase(newEnd, scores.end());
    printVec("After erase-remove", scores);

    // --------------------------------------------------------
    // Demo 4: remove with erase idiom
    // --------------------------------------------------------
    std::cout << "\n--- Demo 4: remove + erase Idiom ---" << std::endl;

    std::vector<int> nums;
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(4);
    nums.push_back(2);
    nums.push_back(5);

    printVec("Before removing 2s", nums);

    nums.erase(std::remove(nums.begin(), nums.end(), 2), nums.end());

    printVec("After removing 2s ", nums);

    // --------------------------------------------------------
    // Demo 5: unique — consecutive duplicate removal
    // --------------------------------------------------------
    std::cout << "\n--- Demo 5: unique with Well-Defined Behavior ---" << std::endl;

    std::vector<int> sorted;
    sorted.push_back(1);
    sorted.push_back(1);
    sorted.push_back(2);
    sorted.push_back(3);
    sorted.push_back(3);
    sorted.push_back(3);
    sorted.push_back(4);
    sorted.push_back(5);
    sorted.push_back(5);

    printVec("Before unique", sorted);

    std::vector<int>::iterator uEnd =
        std::unique(sorted.begin(), sorted.end());
    sorted.erase(uEnd, sorted.end());

    printVec("After  unique", sorted);

    // --------------------------------------------------------
    // Demo 6: partition — predicate-based reordering
    // --------------------------------------------------------
    std::cout << "\n--- Demo 6: Partition Guarantees ---" << std::endl;

    std::vector<int> mixed;
    mixed.push_back(7);
    mixed.push_back(2);
    mixed.push_back(9);
    mixed.push_back(4);
    mixed.push_back(1);
    mixed.push_back(6);
    mixed.push_back(3);
    mixed.push_back(8);

    printVec("Before partition (even first)", mixed);

    std::vector<int>::iterator pivot =
        std::stable_partition(mixed.begin(), mixed.end(), isEven);

    std::cout << "  Even: ";
    for (std::vector<int>::iterator it = mixed.begin(); it != pivot; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "  Odd:  ";
    for (std::vector<int>::iterator it = pivot; it != mixed.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    printVec("After stable_partition      ", mixed);

    std::cout << "\n=== C++03: tighter algorithm guarantees for predictable behavior ===" << std::endl;

    return 0;
}

// Expected Output:
// === Algorithm Behavior Fixes ===
//
// --- Demo 1: stable_sort Guarantees ---
//   Before stable_sort:
//     AAPL $150 (seq=1)
//     GOOG $100 (seq=2)
//     MSFT $150 (seq=3)
//     AMZN $100 (seq=4)
//     META $200 (seq=5)
//     TSLA $150 (seq=6)
//   After stable_sort by price:
//     GOOG $100 (seq=2)
//     AMZN $100 (seq=4)
//     AAPL $150 (seq=1)
//     MSFT $150 (seq=3)
//     TSLA $150 (seq=6)
//     META $200 (seq=5)
//
//   Stability check (same-price elements keep original order):
//     $100 group: GOOG(seq=2) before AMZN(seq=4)? YES
//     $150 group: AAPL(seq=1) < MSFT(seq=3) < TSLA(seq=6)? YES
//
// --- Demo 2: sort vs stable_sort ---
//   After sort       : 1 1 2 3 3 4 5 5 6 9
//   After stable_sort: 1 1 2 3 3 4 5 5 6 9
//   Both produce sorted output, but stable_sort preserves relative order of equal elements
//
// --- Demo 3: remove_if Well-Defined Semantics ---
//   Before remove_if(negative): 85 -10 92 -5 78 0 -3 95
//   Elements to keep: 85 92 78 0 95
//   After erase-remove: 85 92 78 0 95
//
// --- Demo 4: remove + erase Idiom ---
//   Before removing 2s: 1 2 3 2 4 2 5
//   After removing 2s : 1 3 4 5
//
// --- Demo 5: unique with Well-Defined Behavior ---
//   Before unique: 1 1 2 3 3 3 4 5 5
//   After  unique: 1 2 3 4 5
//
// --- Demo 6: Partition Guarantees ---
//   Before partition (even first): 7 2 9 4 1 6 3 8
//   Even: 2 4 6 8
//   Odd:  7 9 1 3
//   After stable_partition      : 2 4 6 8 7 9 1 3
//
// === C++03: tighter algorithm guarantees for predictable behavior ===
