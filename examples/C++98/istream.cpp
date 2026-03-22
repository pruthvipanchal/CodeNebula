// CodeNebula - C++98 Example: std::istream
// Compile: g++ -std=c++98 -Wall -Wextra -o istream_example istream.cpp

#include <iostream>
#include <sstream>
#include <string>

int main() {
    std::cout << "=== std::istream ===" << std::endl;

    // Using istringstream as an istream (works without user input)
    std::istringstream input("42 3.14 Hello World");

    // Read different types
    int num;
    double pi;
    std::string word1, word2;

    input >> num >> pi >> word1 >> word2;

    std::cout << "Read int:    " << num << std::endl;
    std::cout << "Read double: " << pi << std::endl;
    std::cout << "Read word1:  " << word1 << std::endl;
    std::cout << "Read word2:  " << word2 << std::endl;

    // getline - read full lines
    std::istringstream lines("First line\nSecond line\nThird line");
    std::string line;
    int lineNum = 1;
    while (std::getline(lines, line)) {
        std::cout << "Line " << lineNum++ << ": " << line << std::endl;
    }

    // Stream state after reading
    std::istringstream eof_test("100");
    int val;
    eof_test >> val;
    std::cout << "Value: " << val << std::endl;
    std::cout << "EOF reached: " << eof_test.eof() << std::endl;

    // peek and get
    std::istringstream peek_test("ABC");
    std::cout << "Peek: " << (char)peek_test.peek() << std::endl;
    std::cout << "Get:  " << (char)peek_test.get() << std::endl;
    std::cout << "Next: " << (char)peek_test.get() << std::endl;

    return 0;
}

// Expected Output:
// === std::istream ===
// Read int:    42
// Read double: 3.14
// Read word1:  Hello
// Read word2:  World
// Line 1: First line
// Line 2: Second line
// Line 3: Third line
// Value: 100
// EOF reached: 1
// Peek: A
// Get:  A
// Next: B
