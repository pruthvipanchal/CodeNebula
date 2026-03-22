// CodeNebula - C++98 Example: std::fstream (file read/write)
// Compile: g++ -std=c++98 -Wall -Wextra -o example fstream.cpp

#include <iostream>
#include <fstream>
#include <string>

int main() {
    const char* filename = "fstream_test.txt";

    // Write to file using fstream in output mode
    std::fstream fs(filename, std::ios::out);
    if (!fs) {
        std::cerr << "Cannot open file for writing" << std::endl;
        return 1;
    }
    fs << "Line 1: Hello fstream" << std::endl;
    fs << "Line 2: Read and write" << std::endl;
    fs << "Line 3: End of file" << std::endl;
    fs.close();
    std::cout << "Wrote 3 lines to file" << std::endl;

    // Read from same file using fstream in input mode
    fs.open(filename, std::ios::in);
    if (!fs) {
        std::cerr << "Cannot open file for reading" << std::endl;
        return 1;
    }

    std::string line;
    std::cout << "Reading back:" << std::endl;
    while (std::getline(fs, line)) {
        std::cout << "  " << line << std::endl;
    }
    fs.close();

    // Open for both reading and writing (in|out)
    fs.open(filename, std::ios::in | std::ios::out);
    if (fs) {
        fs.seekp(0, std::ios::end);
        fs << "Line 4: Appended via read/write mode" << std::endl;
        fs.seekg(0);
        std::cout << "After append, first line: ";
        std::getline(fs, line);
        std::cout << line << std::endl;
        fs.close();
    }

    // Clean up
    std::remove(filename);
    std::cout << "Temp file removed" << std::endl;

    return 0;
}

// Expected output:
// Wrote 3 lines to file
// Reading back:
//   Line 1: Hello fstream
//   Line 2: Read and write
//   Line 3: End of file
// After append, first line: Line 1: Hello fstream
// Temp file removed
