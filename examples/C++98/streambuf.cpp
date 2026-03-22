// CodeNebula - C++98 Example: std::streambuf (rdbuf swapping)
// Compile: g++ -std=c++98 -Wall -Wextra -o example streambuf.cpp

#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    const char* filename = "streambuf_test.txt";

    // Redirect cout to a file using rdbuf
    std::ofstream file(filename);
    std::streambuf* old_cout = std::cout.rdbuf(); // save original

    std::cout.rdbuf(file.rdbuf()); // redirect cout to file
    std::cout << "This goes to the file" << std::endl;
    std::cout << "So does this" << std::endl;

    std::cout.rdbuf(old_cout); // restore cout
    std::cout << "Back to console" << std::endl;
    file.close();

    // Read back the file contents
    std::ifstream in(filename);
    std::cout << "File contains:" << std::endl;
    std::cout << in.rdbuf(); // copy entire streambuf to cout
    in.close();

    // Redirect cerr to a stringstream
    std::ostringstream oss;
    std::streambuf* old_cerr = std::cerr.rdbuf();
    std::cerr.rdbuf(oss.rdbuf());

    std::cerr << "Error message captured";
    std::cerr.rdbuf(old_cerr); // restore

    std::cout << "Captured cerr: " << oss.str() << std::endl;

    std::remove(filename);
    return 0;
}

// Expected output:
// Back to console
// File contains:
// This goes to the file
// So does this
// Captured cerr: Error message captured
