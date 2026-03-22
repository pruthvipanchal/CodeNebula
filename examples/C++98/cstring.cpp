// CodeNebula - C++98 Example: <cstring> functions
// Compile: g++ -std=c++98 -Wall -Wextra -o example cstring.cpp

#include <iostream>
#include <cstring>

int main() {
    // strlen - string length
    const char* str = "Hello, World!";
    std::cout << "strlen(\"" << str << "\") = " << std::strlen(str) << std::endl;

    // strcpy and strncpy
    char dest[50];
    std::strcpy(dest, "Hello");
    std::cout << "strcpy: " << dest << std::endl;

    std::strncpy(dest, "Goodbye, World!", 7);
    dest[7] = '\0';
    std::cout << "strncpy(7): " << dest << std::endl;

    // strcat - concatenation
    char buf[50] = "Hello";
    std::strcat(buf, " World");
    std::cout << "strcat: " << buf << std::endl;

    // strcmp - comparison
    std::cout << "strcmp(\"abc\",\"abc\") = " << std::strcmp("abc", "abc") << std::endl;
    std::cout << "strcmp(\"abc\",\"abd\") = " << std::strcmp("abc", "abd") << std::endl;
    std::cout << "strcmp(\"abd\",\"abc\") = " << std::strcmp("abd", "abc") << std::endl;

    // strchr - find character
    const char* p = std::strchr(str, 'W');
    if (p) std::cout << "strchr 'W': " << p << std::endl;

    // strstr - find substring
    const char* sub = std::strstr(str, "World");
    if (sub) std::cout << "strstr \"World\": " << sub << std::endl;

    // memset and memcpy
    char block[10];
    std::memset(block, 'X', 9);
    block[9] = '\0';
    std::cout << "memset: " << block << std::endl;

    char copy[10];
    std::memcpy(copy, block, 10);
    std::cout << "memcpy: " << copy << std::endl;

    return 0;
}

// Expected output:
// strlen("Hello, World!") = 13
// strcpy: Hello
// strncpy(7): Goodbye
// strcat: Hello World
// strcmp("abc","abc") = 0
// strcmp("abc","abd") = -1
// strcmp("abd","abc") = 1
// strchr 'W': World!
// strstr "World": World!
// memset: XXXXXXXXX
// memcpy: XXXXXXXXX
