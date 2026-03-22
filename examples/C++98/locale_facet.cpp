// CodeNebula - C++98 Example: locale facets (numpunct)
// Compile: g++ -std=c++98 -Wall -Wextra -o example locale_facet.cpp

#include <iostream>
#include <locale>
#include <sstream>
#include <string>

// Custom numpunct facet that uses underscores as thousands separator
class MyNumpunct : public std::numpunct<char> {
protected:
    virtual char do_thousands_sep() const { return '_'; }
    virtual std::string do_grouping() const { return "\3"; }
    virtual std::string do_truename() const { return "TRUE"; }
    virtual std::string do_falsename() const { return "FALSE"; }
    virtual char do_decimal_point() const { return '.'; }
};

int main() {
    // Query the default numpunct facet
    const std::numpunct<char>& np =
        std::use_facet<std::numpunct<char> >(std::locale());

    std::cout << "Default decimal point: '" << np.decimal_point() << "'" << std::endl;
    std::cout << "Default thousands sep: '" << np.thousands_sep() << "'" << std::endl;
    std::cout << "Default truename: " << np.truename() << std::endl;
    std::cout << "Default falsename: " << np.falsename() << std::endl;

    // Apply our custom facet
    std::locale custom(std::locale(), new MyNumpunct);
    std::ostringstream oss;
    oss.imbue(custom);
    oss << std::boolalpha << true << " " << false;
    std::cout << "Custom boolalpha: " << oss.str() << std::endl;

    // Format a number with custom thousands separator
    std::ostringstream oss2;
    oss2.imbue(custom);
    oss2 << 1234567;
    std::cout << "Custom number: " << oss2.str() << std::endl;

    return 0;
}

// Expected output:
// Default decimal point: '.'
// Default thousands sep: ''
// Default truename: true
// Default falsename: false
// Custom boolalpha: TRUE FALSE
// Custom number: 1_234_567
