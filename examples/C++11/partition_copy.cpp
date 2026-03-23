// CodeNebula - C++11 Example: std::partition_copy
// Compile: g++ -std=c++11 -Wall -Wextra -o partition_copy partition_copy.cpp

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::cout << "=== std::partition_copy ===" << std::endl;

    // Split numbers into even and odd
    std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> evens, odds;

    std::partition_copy(numbers.begin(), numbers.end(),
                        std::back_inserter(evens),
                        std::back_inserter(odds),
                        [](int n) { return n % 2 == 0; });

    std::cout << "Original: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "Evens:    ";
    for (int n : evens) std::cout << n << " ";
    std::cout << std::endl;

    std::cout << "Odds:     ";
    for (int n : odds) std::cout << n << " ";
    std::cout << std::endl;

    // Split students by passing grade
    std::vector<int> scores = {85, 42, 91, 55, 73, 38, 96, 61};
    std::vector<int> passed, failed;

    std::partition_copy(scores.begin(), scores.end(),
                        std::back_inserter(passed),
                        std::back_inserter(failed),
                        [](int s) { return s >= 60; });

    std::cout << "\nScores:  ";
    for (int s : scores) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "Passed:  ";
    for (int s : passed) std::cout << s << " ";
    std::cout << std::endl;

    std::cout << "Failed:  ";
    for (int s : failed) std::cout << s << " ";
    std::cout << std::endl;

    return 0;
}

// Expected Output:
// === std::partition_copy ===
// Original: 1 2 3 4 5 6 7 8 9 10
// Evens:    2 4 6 8 10
// Odds:     1 3 5 7 9
//
// Scores:  85 42 91 55 73 38 96 61
// Passed:  85 91 73 96 61
// Failed:  42 55 38
