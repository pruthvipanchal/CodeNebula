// CodeNebula - C++20 Example: String contains
// Compile: g++ -std=c++20 -Wall -Wextra -o example contains.cpp

// Note: std::string::contains is a C++23 feature. In C++20, we demonstrate
// the equivalent using std::string::find and also associative container contains.

#include <iostream>
#include <string>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

int main() {
    // C++20 associative container contains() method
    // std::set::contains
    std::set<int> numbers = {1, 3, 5, 7, 9};
    std::cout << "Set {1,3,5,7,9}:\n";
    std::cout << "  contains(5)? " << (numbers.contains(5) ? "yes" : "no") << '\n';
    std::cout << "  contains(4)? " << (numbers.contains(4) ? "yes" : "no") << '\n';

    // std::map::contains
    std::map<std::string, int> ages = {
        {"Alice", 30}, {"Bob", 25}, {"Carol", 35}
    };
    std::cout << "\nMap contains:\n";
    std::cout << "  contains(\"Alice\")? "
              << (ages.contains("Alice") ? "yes" : "no") << '\n';
    std::cout << "  contains(\"Dave\")?  "
              << (ages.contains("Dave") ? "yes" : "no") << '\n';

    // std::unordered_set::contains
    std::unordered_set<std::string> keywords = {"if", "else", "for", "while", "return"};
    std::cout << "\nKeywords contains:\n";
    std::cout << "  contains(\"for\")?    " << (keywords.contains("for") ? "yes" : "no") << '\n';
    std::cout << "  contains(\"switch\")? " << (keywords.contains("switch") ? "yes" : "no") << '\n';

    // std::unordered_map::contains
    std::unordered_map<int, std::string> codes = {{200, "OK"}, {404, "Not Found"}};
    std::cout << "\nHTTP codes contains:\n";
    std::cout << "  contains(200)? " << (codes.contains(200) ? "yes" : "no") << '\n';
    std::cout << "  contains(500)? " << (codes.contains(500) ? "yes" : "no") << '\n';

    // String substring check using find (C++20 pattern, contains() added in C++23)
    std::string text = "The quick brown fox jumps over the lazy dog";
    auto has_substr = [&text](const char* sub) {
        return text.find(sub) != std::string::npos;
    };
    std::cout << "\nString \"" << text << "\":\n";
    std::cout << "  has \"fox\"?  " << (has_substr("fox") ? "yes" : "no") << '\n';
    std::cout << "  has \"cat\"?  " << (has_substr("cat") ? "yes" : "no") << '\n';

    // Practical: check membership before access
    std::map<std::string, double> prices = {
        {"apple", 1.20}, {"banana", 0.50}, {"cherry", 2.50}
    };
    std::string item = "banana";
    if (prices.contains(item)) {
        std::cout << "\n" << item << " costs $" << prices[item] << '\n';
    } else {
        std::cout << "\n" << item << " not found in inventory\n";
    }

    return 0;
}
