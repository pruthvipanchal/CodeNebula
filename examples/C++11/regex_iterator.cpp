// CodeNebula - C++11 Example: std::regex_iterator
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex_iterator.cpp

// std::regex_iterator iterates over ALL non-overlapping matches of a
// regex in a string. Each dereference yields a match_results object
// with full details about the match and its capture groups.

#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
    // Find all words in a string
    std::string text = "The quick brown fox jumps over the lazy dog";
    std::regex word_re(R"(\w+)");

    std::cout << "All words:" << std::endl;
    auto words_begin = std::sregex_iterator(text.begin(), text.end(), word_re);
    auto words_end = std::sregex_iterator();

    int count = 0;
    for (auto it = words_begin; it != words_end; ++it) {
        std::smatch match = *it;
        std::cout << "  [" << count++ << "] \"" << match.str()
                  << "\" at pos " << match.position() << std::endl;
    }
    std::cout << "Total words: " << count << std::endl;

    // Extract all numbers from mixed text
    std::string data = "Item #42 costs $19.99, qty: 5, total: $99.95";
    std::regex num_re(R"(\d+\.?\d*)");

    std::cout << "\nNumbers in: \"" << data << "\"" << std::endl;
    std::vector<std::string> numbers;
    for (auto it = std::sregex_iterator(data.begin(), data.end(), num_re);
         it != std::sregex_iterator(); ++it) {
        numbers.push_back(it->str());
        std::cout << "  " << it->str() << std::endl;
    }

    // Extract key-value pairs
    std::string config = "name=Alice age=30 city=London score=95.5";
    std::regex kv_re(R"((\w+)=([\w.]+))");

    std::cout << "\nKey-value pairs:" << std::endl;
    for (auto it = std::sregex_iterator(config.begin(), config.end(), kv_re);
         it != std::sregex_iterator(); ++it) {
        std::cout << "  " << (*it)[1] << " => " << (*it)[2] << std::endl;
    }

    // Count matches without storing
    std::string log = "ERROR: fail. WARN: issue. ERROR: crash. INFO: ok. ERROR: bug.";
    std::regex error_re(R"(ERROR)");
    auto err_begin = std::sregex_iterator(log.begin(), log.end(), error_re);
    auto err_end = std::sregex_iterator();
    long error_count = std::distance(err_begin, err_end);
    std::cout << "\nERROR count: " << error_count << std::endl;

    // Iterate over matches with position details
    std::string csv_line = "Alice,30,London";
    std::regex field_re(R"([^,]+)");

    std::cout << "\nCSV fields with positions:" << std::endl;
    for (auto it = std::sregex_iterator(csv_line.begin(), csv_line.end(), field_re);
         it != std::sregex_iterator(); ++it) {
        std::cout << "  pos=" << it->position() << " len=" << it->length()
                  << " val=\"" << it->str() << "\"" << std::endl;
    }

    return 0;
}

// Expected output:
// All words:
//   [0] "The" at pos 0
//   [1] "quick" at pos 4
//   [2] "brown" at pos 10
//   [3] "fox" at pos 16
//   [4] "jumps" at pos 20
//   [5] "over" at pos 26
//   [6] "the" at pos 31
//   [7] "lazy" at pos 35
//   [8] "dog" at pos 40
// Total words: 9
//
// Numbers in: "Item #42 costs $19.99, qty: 5, total: $99.95"
//   42
//   19.99
//   5
//   99.95
//
// Key-value pairs:
//   name => Alice
//   age => 30
//   city => London
//   score => 95.5
//
// ERROR count: 3
//
// CSV fields with positions:
//   pos=0 len=5 val="Alice"
//   pos=6 len=2 val="30"
//   pos=9 len=6 val="London"
