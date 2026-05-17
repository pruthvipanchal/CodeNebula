// CodeNebula - C++11 Example: smatch, cmatch, wsmatch Types
// Compile: g++ -std=c++11 -Wall -Wextra -o example regex_match_types.cpp

// C++11 provides several match_results specializations for different
// string types: smatch (string), cmatch (C-string), wsmatch (wstring),
// and wcmatch (wide C-string). Each stores sub_match objects.

#include <iostream>
#include <regex>
#include <string>

int main() {
    // === std::smatch: for std::string ===
    std::cout << "=== smatch (std::string) ===" << std::endl;
    std::string text = "John is 30 years old";
    std::regex pattern(R"((\w+) is (\d+) years old)");
    std::smatch sm;

    if (std::regex_match(text, sm, pattern)) {
        std::cout << "Full match: " << sm[0] << std::endl;
        std::cout << "Name:       " << sm[1] << std::endl;
        std::cout << "Age:        " << sm[2] << std::endl;
        std::cout << "Groups:     " << sm.size() << std::endl;

        // sub_match properties
        auto& sub = sm[1];
        std::cout << "sub_match[1]:" << std::endl;
        std::cout << "  str():    " << sub.str() << std::endl;
        std::cout << "  length(): " << sub.length() << std::endl;
        std::cout << "  matched:  " << (sub.matched ? "true" : "false") << std::endl;
    }

    // === std::cmatch: for const char* ===
    std::cout << "\n=== cmatch (const char*) ===" << std::endl;
    const char* cstr = "Error 404: Not Found";
    std::regex err_re(R"(Error (\d+): (.+))");
    std::cmatch cm;

    if (std::regex_match(cstr, cm, err_re)) {
        std::cout << "Full: " << cm[0] << std::endl;
        std::cout << "Code: " << cm[1] << std::endl;
        std::cout << "Msg:  " << cm[2] << std::endl;
    }

    // === std::wsmatch: for std::wstring ===
    std::cout << "\n=== wsmatch (std::wstring) ===" << std::endl;
    std::wstring wtext = L"Price: $42.50";
    std::wregex wprice_re(LR"(Price: \$(\d+\.\d{2}))");
    std::wsmatch wsm;

    if (std::regex_match(wtext, wsm, wprice_re)) {
        std::wcout << L"Full:  " << wsm[0].str() << std::endl;
        std::wcout << L"Price: " << wsm[1].str() << std::endl;
    }

    // === Iterating over all sub_matches ===
    std::cout << "\n=== Iterating sub_matches ===" << std::endl;
    std::string date = "2024-03-15";
    std::regex date_re(R"((\d{4})-(\d{2})-(\d{2}))");
    std::smatch dm;

    if (std::regex_match(date, dm, date_re)) {
        for (std::size_t i = 0; i < dm.size(); ++i) {
            std::cout << "  [" << i << "] "
                      << (dm[i].matched ? "matched" : "unmatched")
                      << ": \"" << dm[i] << "\" (len=" << dm[i].length()
                      << ")" << std::endl;
        }
    }

    // === Unmatched optional groups ===
    std::cout << "\n=== Optional groups ===" << std::endl;
    std::regex opt_re(R"((\w+)(?::(\d+))?)");
    std::string tests[] = {"host", "host:8080"};
    for (const auto& t : tests) {
        std::smatch om;
        if (std::regex_match(t, om, opt_re)) {
            std::cout << "\"" << t << "\":" << std::endl;
            std::cout << "  [1] " << om[1] << " (matched: "
                      << (om[1].matched ? "yes" : "no") << ")" << std::endl;
            std::cout << "  [2] " << om[2] << " (matched: "
                      << (om[2].matched ? "yes" : "no") << ")" << std::endl;
        }
    }

    // === prefix() and suffix() ===
    std::cout << "\n=== prefix/suffix ===" << std::endl;
    std::string haystack = "abc 123 def";
    std::regex num_re(R"(\d+)");
    std::smatch fm;
    if (std::regex_search(haystack, fm, num_re)) {
        std::cout << "Match:   \"" << fm[0] << "\"" << std::endl;
        std::cout << "Prefix:  \"" << fm.prefix() << "\"" << std::endl;
        std::cout << "Suffix:  \"" << fm.suffix() << "\"" << std::endl;
    }

    return 0;
}

// Expected output:
// === smatch (std::string) ===
// Full match: John is 30 years old
// Name:       John
// Age:        30
// Groups:     3
// sub_match[1]:
//   str():    John
//   length(): 4
//   matched:  true
//
// === cmatch (const char*) ===
// Full: Error 404: Not Found
// Code: 404
// Msg:  Not Found
//
// === wsmatch (std::wstring) ===
// Full:  Price: $42.50
// Price: 42.50
//
// === Iterating sub_matches ===
//   [0] matched: "2024-03-15" (len=10)
//   [1] matched: "2024" (len=4)
//   [2] matched: "03" (len=2)
//   [3] matched: "15" (len=2)
//
// === Optional groups ===
// "host":
//   [1] host (matched: yes)
//   [2]  (matched: no)
// "host:8080":
//   [1] host (matched: yes)
//   [2] 8080 (matched: yes)
//
// === prefix/suffix ===
// Match:   "123"
// Prefix:  "abc "
// Suffix:  " def"
