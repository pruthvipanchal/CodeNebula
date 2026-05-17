// CodeNebula - C++98 Example: std::locale
// Compile: g++ -std=c++98 -Wall -Wextra -o example locale.cpp

#include <iostream>
#include <locale>
#include <string>
#include <sstream>

int main() {
    // Display the default (C) locale name
    std::cout << "Default locale: " << std::locale().name() << std::endl;

    // Classic locale is always available
    std::locale classic = std::locale::classic();
    std::cout << "Classic locale: " << classic.name() << std::endl;

    // Imbue cout with classic locale for consistent formatting
    std::cout.imbue(classic);
    std::cout << "Large number (classic): " << 1234567.89 << std::endl;

    // Use locale for character classification
    std::locale loc;
    char ch = 'A';
    std::cout << "'" << ch << "' is upper: "
              << (std::isupper(ch, loc) ? "yes" : "no") << std::endl;
    std::cout << "'" << ch << "' is alpha: "
              << (std::isalpha(ch, loc) ? "yes" : "no") << std::endl;

    char d = '5';
    std::cout << "'" << d << "' is digit: "
              << (std::isdigit(d, loc) ? "yes" : "no") << std::endl;

    // toupper/tolower with locale
    char lower = 'h';
    std::cout << "toupper('" << lower << "'): "
              << std::toupper(lower, loc) << std::endl;

    char upper = 'Z';
    std::cout << "tolower('" << upper << "'): "
              << std::tolower(upper, loc) << std::endl;

    return 0;
}

// Expected output:
// Default locale: C
// Classic locale: C
// Large number (classic): 1.23457e+06
// 'A' is upper: yes
// 'A' is alpha: yes
// '5' is digit: yes
// toupper('h'): H
// tolower('Z'): z
