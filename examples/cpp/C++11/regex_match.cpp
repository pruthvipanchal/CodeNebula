// CodeNebula - C++11 Example: std::regex_match
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex_match.cpp

// std::regex_match checks if the ENTIRE string matches a pattern.
// Unlike regex_search, it requires the full string to conform to
// the pattern. Use it for validation (emails, dates, IDs, etc.).

#include <iostream>
#include <regex>
#include <string>
#include <vector>

int main() {
    // Simple full-string match
    std::regex number_re(R"(-?\d+)");
    std::cout << "Full string matches:" << std::endl;
    std::cout << "  \"42\" is integer:    "
              << (std::regex_match(std::string("42"), number_re) ? "yes" : "no") << std::endl;
    std::cout << "  \"42abc\" is integer: "
              << (std::regex_match(std::string("42abc"), number_re) ? "yes" : "no") << std::endl;

    // Capturing groups
    std::regex date_re(R"((\d{4})-(\d{2})-(\d{2}))");
    std::string date = "2024-03-15";
    std::smatch match;

    if (std::regex_match(date, match, date_re)) {
        std::cout << "\nDate parsing: \"" << date << "\"" << std::endl;
        std::cout << "  Full match: " << match[0] << std::endl;
        std::cout << "  Year:       " << match[1] << std::endl;
        std::cout << "  Month:      " << match[2] << std::endl;
        std::cout << "  Day:        " << match[3] << std::endl;
        std::cout << "  Groups:     " << match.size() << std::endl;
    }

    // Email validation with groups
    std::regex email_re(R"((\w+)@(\w+)\.(\w+))");
    std::string email = "user@example.com";
    if (std::regex_match(email, match, email_re)) {
        std::cout << "\nEmail parsing: \"" << email << "\"" << std::endl;
        std::cout << "  User:   " << match[1] << std::endl;
        std::cout << "  Domain: " << match[2] << std::endl;
        std::cout << "  TLD:    " << match[3] << std::endl;
    }

    // Validate a list of inputs
    std::regex ip_re(R"((\d{1,3})\.(\d{1,3})\.(\d{1,3})\.(\d{1,3}))");
    std::vector<std::string> ips = {
        "192.168.1.1", "10.0.0.255", "abc.def.ghi.jkl", "999.999.999.999"
    };

    std::cout << "\nIP address format validation:" << std::endl;
    for (const auto& ip : ips) {
        bool valid = std::regex_match(ip, ip_re);
        std::cout << "  \"" << ip << "\": " << (valid ? "valid format" : "invalid") << std::endl;
    }

    // Match with C-string (cmatch)
    std::cmatch cm;
    const char* cstr = "Hello123";
    std::regex alpha_num(R"([A-Za-z]+(\d+))");
    if (std::regex_match(cstr, cm, alpha_num)) {
        std::cout << "\nC-string match: \"" << cm[0] << "\"" << std::endl;
        std::cout << "  Digits part: " << cm[1] << std::endl;
    }

    // Optional groups
    std::regex opt_re(R"((\w+)(?::(\d+))?)");  // name optionally followed by :port
    std::string inputs[] = {"localhost", "server:8080"};
    std::cout << "\nOptional group matching:" << std::endl;
    for (const auto& s : inputs) {
        if (std::regex_match(s, match, opt_re)) {
            std::cout << "  \"" << s << "\" -> host=" << match[1];
            if (match[2].matched) std::cout << " port=" << match[2];
            std::cout << std::endl;
        }
    }

    return 0;
}

// Expected output:
// Full string matches:
//   "42" is integer:    yes
//   "42abc" is integer: no
//
// Date parsing: "2024-03-15"
//   Full match: 2024-03-15
//   Year:       2024
//   Month:      03
//   Day:        15
//   Groups:     4
//
// Email parsing: "user@example.com"
//   User:   user
//   Domain: example
//   TLD:    com
//
// IP address format validation:
//   "192.168.1.1": valid format
//   "10.0.0.255": valid format
//   "abc.def.ghi.jkl": invalid
//   "999.999.999.999": valid format
//
// C-string match: "Hello123"
//   Digits part: 123
//
// Optional group matching:
//   "localhost" -> host=localhost
//   "server:8080" -> host=server port=8080
