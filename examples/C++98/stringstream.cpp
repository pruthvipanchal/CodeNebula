// CodeNebula - C++98 Example: std::stringstream
// Compile: g++ -std=c++98 -Wall -Wextra -o stringstream_example stringstream.cpp

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
    std::cout << "=== std::stringstream ===" << std::endl;

    // Basic string-to-number conversion
    std::cout << "--- String to Number ---" << std::endl;
    std::stringstream ss1("42 3.14 100");
    int i;
    double d;
    int j;
    ss1 >> i >> d >> j;
    std::cout << "int: " << i << ", double: " << d << ", int: " << j << std::endl;

    // Number-to-string conversion
    std::cout << "\n--- Number to String ---" << std::endl;
    std::ostringstream oss;
    oss << "Value is " << 42 << " and pi is " << 3.14;
    std::string result = oss.str();
    std::cout << result << std::endl;

    // Parse CSV-like data
    std::cout << "\n--- Parse CSV ---" << std::endl;
    std::string csv = "Alice,95,A";
    std::istringstream csvStream(csv);
    std::string name, grade;
    int score;
    std::getline(csvStream, name, ',');
    csvStream >> score;
    csvStream.ignore(1); // skip comma
    std::getline(csvStream, grade);
    std::cout << "Name: " << name << ", Score: " << score << ", Grade: " << grade << std::endl;

    // Split string by spaces
    std::cout << "\n--- Split by Space ---" << std::endl;
    std::istringstream words("the quick brown fox");
    std::string word;
    std::vector<std::string> tokens;
    while (words >> word) {
        tokens.push_back(word);
    }
    for (std::vector<std::string>::size_type k = 0; k < tokens.size(); ++k) {
        std::cout << "[" << k << "] " << tokens[k] << std::endl;
    }

    // Reuse stringstream with str() and clear()
    std::cout << "\n--- Reuse Stream ---" << std::endl;
    std::stringstream reusable;
    reusable << 123;
    std::string s1 = reusable.str();
    std::cout << "First: " << s1 << std::endl;

    reusable.str("");   // clear the buffer
    reusable.clear();   // clear error flags
    reusable << 456;
    std::string s2 = reusable.str();
    std::cout << "Second: " << s2 << std::endl;

    // Build formatted output
    std::cout << "\n--- Build Formatted ---" << std::endl;
    std::ostringstream table;
    table << "ID   Name    Score" << std::endl;
    table << "1    Alice   95" << std::endl;
    table << "2    Bob     87" << std::endl;
    std::cout << table.str();

    return 0;
}

// Expected Output:
// === std::stringstream ===
// --- String to Number ---
// int: 42, double: 3.14, int: 100
//
// --- Number to String ---
// Value is 42 and pi is 3.14
//
// --- Parse CSV ---
// Name: Alice, Score: 95, Grade: A
//
// --- Split by Space ---
// [0] the
// [1] quick
// [2] brown
// [3] fox
//
// --- Reuse Stream ---
// First: 123
// Second: 456
//
// --- Build Formatted ---
// ID   Name    Score
// 1    Alice   95
// 2    Bob     87
