// CodeNebula - C++98 Example: std::ofstream (file output)
// Compile: g++ -std=c++98 -Wall -Wextra -o example ofstream.cpp

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

int main() {
    const char* filename = "ofstream_test.txt";

    // Create and write to file
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cerr << "Cannot create file" << std::endl;
        return 1;
    }

    ofs << "Product Report" << std::endl;
    ofs << std::string(30, '-') << std::endl;
    ofs << std::left << std::setw(15) << "Item"
        << std::right << std::setw(10) << "Price" << std::endl;
    ofs << std::setw(15) << std::left << "Widget"
        << std::right << std::setw(10) << std::fixed << std::setprecision(2)
        << 9.99 << std::endl;
    ofs << std::setw(15) << std::left << "Gadget"
        << std::right << std::setw(10) << 24.95 << std::endl;
    ofs.close();
    std::cout << "File written" << std::endl;

    // Append mode
    std::ofstream app(filename, std::ios::app);
    app << std::setw(15) << std::left << "Doohickey"
        << std::right << std::setw(10) << std::fixed << std::setprecision(2)
        << 4.50 << std::endl;
    app.close();
    std::cout << "Appended to file" << std::endl;

    // Verify by reading back
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        std::cout << line << std::endl;
    }
    ifs.close();

    std::remove(filename);
    return 0;
}

// Expected output:
// File written
// Appended to file
// Product Report
// ------------------------------
// Item                Price
// Widget               9.99
// Gadget              24.95
// Doohickey            4.50
