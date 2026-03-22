// CodeNebula - C++98 Example: <cstdio> functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example cstdio.cpp

#include <iostream>
#include <cstdio>
#include <cstring>

int main() {
    // printf - formatted output
    std::printf("printf: Hello, %s! You are %d years old.\n", "Alice", 30);
    std::printf("printf: pi = %.4f\n", 3.14159);
    std::printf("printf: hex 255 = 0x%X\n", 255);
    std::printf("printf: padded [%10d]\n", 42);
    std::printf("printf: left   [%-10d]\n", 42);

    // sprintf - format to string buffer
    char buf[100];
    std::sprintf(buf, "Name: %s, Score: %d%%", "Bob", 95);
    std::cout << "sprintf result: " << buf << std::endl;

    // snprintf - safe formatting with size limit
    char small[20];
    int written = std::snprintf(small, sizeof(small), "Long string: %s", "abcdefghijklmnop");
    std::cout << "snprintf: " << small << " (would need " << written << " chars)" << std::endl;

    // sscanf - parse from string
    const char* data = "42 3.14 hello";
    int ival;
    double dval;
    char sval[20];
    std::sscanf(data, "%d %lf %s", &ival, &dval, sval);
    std::cout << "sscanf: int=" << ival << " double=" << dval
              << " str=" << sval << std::endl;

    // File operations with FILE*
    const char* fname = "cstdio_test.txt";
    std::FILE* fp = std::fopen(fname, "w");
    if (fp) {
        std::fprintf(fp, "Line %d\n", 1);
        std::fputs("Line 2\n", fp);
        std::fclose(fp);
    }
    std::remove(fname);
    std::cout << "File created and removed" << std::endl;

    return 0;
}

// Expected output:
// printf: Hello, Alice! You are 30 years old.
// printf: pi = 3.1416
// printf: hex 255 = 0xFF
// printf: padded [        42]
// printf: left   [42        ]
// sprintf result: Name: Bob, Score: 95%
// snprintf: Long string: abcde (would need 27 chars)
// sscanf: int=42 double=3.14 str=hello
// File created and removed
