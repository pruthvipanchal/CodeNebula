// CodeNebula - C++20 Example: String starts_with and ends_with
// Compile: g++ -std=c++20 -Wall -Wextra -o example starts_ends_with.cpp

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

int main() {
    // std::string::starts_with - check prefix
    std::string url = "https://www.example.com/page";

    std::cout << "URL: " << url << '\n';
    std::cout << "Starts with \"https\"? "
              << (url.starts_with("https") ? "yes" : "no") << '\n';
    std::cout << "Starts with \"http\"?  "
              << (url.starts_with("http") ? "yes" : "no") << '\n';
    std::cout << "Starts with \"ftp\"?   "
              << (url.starts_with("ftp") ? "yes" : "no") << '\n';

    // Check single character prefix
    std::string greeting = "Hello, World!";
    std::cout << "\nStarts with 'H'? "
              << (greeting.starts_with('H') ? "yes" : "no") << '\n';
    std::cout << "Starts with 'h'? "
              << (greeting.starts_with('h') ? "yes" : "no") << '\n';

    // std::string::ends_with - check suffix
    std::string filename = "document.pdf";
    std::cout << "\nFilename: " << filename << '\n';
    std::cout << "Ends with \".pdf\"? "
              << (filename.ends_with(".pdf") ? "yes" : "no") << '\n';
    std::cout << "Ends with \".txt\"? "
              << (filename.ends_with(".txt") ? "yes" : "no") << '\n';
    std::cout << "Ends with 'f'?     "
              << (filename.ends_with('f') ? "yes" : "no") << '\n';

    // Works with string_view too
    std::string_view sv_prefix = "https";
    std::cout << "\nstarts_with(string_view): "
              << (url.starts_with(sv_prefix) ? "yes" : "no") << '\n';

    // Practical: filter files by extension
    std::vector<std::string> files = {
        "main.cpp", "util.hpp", "readme.md", "test.cpp",
        "config.json", "style.css", "app.cpp"
    };

    std::cout << "\nC++ source files:\n";
    for (const auto& f : files) {
        if (f.ends_with(".cpp") || f.ends_with(".hpp"))
            std::cout << "  " << f << '\n';
    }

    // Practical: categorize URLs
    std::vector<std::string> urls = {
        "https://secure.com", "http://old.com",
        "ftp://files.com", "https://api.com"
    };
    std::cout << "\nSecure URLs:\n";
    for (const auto& u : urls) {
        if (u.starts_with("https://"))
            std::cout << "  " << u << '\n';
    }

    return 0;
}
