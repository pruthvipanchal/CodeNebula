// CodeNebula - C++98 Example: std::ifstream (file input)
// Compile: g++ -std=c++98 -Wall -Wextra -o example ifstream.cpp

#include <iostream>
#include <fstream>
#include <string>

int main() {
    const char* filename = "ifstream_test.txt";

    // First create a test file
    std::ofstream out(filename);
    out << "Alice 85" << std::endl;
    out << "Bob 92" << std::endl;
    out << "Carol 78" << std::endl;
    out.close();

    // Read using ifstream
    std::ifstream ifs(filename);
    if (!ifs.is_open()) {
        std::cerr << "Failed to open " << filename << std::endl;
        return 1;
    }

    // Read structured data
    std::string name;
    int score;
    std::cout << "Student scores:" << std::endl;
    while (ifs >> name >> score) {
        std::cout << "  " << name << ": " << score << std::endl;
    }

    // Check stream state after reading
    std::cout << "EOF reached: " << (ifs.eof() ? "yes" : "no") << std::endl;
    ifs.clear(); // clear EOF flag

    // Seek back to beginning and read line by line
    ifs.seekg(0);
    std::string line;
    std::cout << "Raw lines:" << std::endl;
    while (std::getline(ifs, line)) {
        std::cout << "  [" << line << "]" << std::endl;
    }

    ifs.close();
    std::remove(filename);

    return 0;
}

// Expected output:
// Student scores:
//   Alice: 85
//   Bob: 92
//   Carol: 78
// EOF reached: yes
// Raw lines:
//   [Alice 85]
//   [Bob 92]
//   [Carol 78]
