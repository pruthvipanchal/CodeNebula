// CodeNebula - C++11 Example: Raw String Literals
// Compile: g++ -std=c++11 -Wall -Wextra -o example raw_string_literals.cpp

// Demonstrates R"(...)" raw string literals. Raw strings preserve all
// characters literally -- no escape processing. Ideal for regex patterns,
// file paths, JSON, XML, SQL, and multi-line text.

#include <iostream>
#include <string>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic raw string vs regular string
    // ------------------------------------------------------------------
    std::string regular = "Line1\\nLine2\\tTabbed";
    std::string raw     = R"(Line1\nLine2\tTabbed)";

    std::cout << "=== Raw vs regular ===" << std::endl;
    std::cout << "  Regular: " << regular << std::endl;
    std::cout << "  Raw:     " << raw << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. File paths (no double backslashes needed)
    // ------------------------------------------------------------------
    std::string winPath = R"(C:\Users\Alice\Documents\report.txt)";
    std::string uncPath = R"(\\server\share\folder\file.dat)";

    std::cout << "=== File paths ===" << std::endl;
    std::cout << "  " << winPath << std::endl;
    std::cout << "  " << uncPath << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Regular expression patterns (no escape hell)
    // ------------------------------------------------------------------
    std::string emailRegex = R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z]{2,}\b)";
    std::string ipRegex    = R"(\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3})";

    std::cout << "=== Regex patterns ===" << std::endl;
    std::cout << "  Email: " << emailRegex << std::endl;
    std::cout << "  IP:    " << ipRegex << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Multi-line strings (preserved formatting)
    // ------------------------------------------------------------------
    std::string json = R"({
    "name": "Alice",
    "age": 30,
    "scores": [95, 87, 92],
    "address": {
        "city": "Wonderland"
    }
})";

    std::cout << "=== JSON ===" << std::endl;
    std::cout << json << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. SQL query
    // ------------------------------------------------------------------
    std::string sql = R"(SELECT u.name, u.email, COUNT(o.id)
FROM users u
LEFT JOIN orders o ON u.id = o.user_id
WHERE u.active = true
GROUP BY u.name, u.email
HAVING COUNT(o.id) > 5;)";

    std::cout << "=== SQL ===" << std::endl;
    std::cout << sql << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Custom delimiter: R"delim(...)delim"
    // ------------------------------------------------------------------
    // Use when the raw string itself contains )"
    std::string tricky = R"xyz(She said: "Use R"(...)" for raw strings!")xyz";

    std::cout << "=== Custom delimiter ===" << std::endl;
    std::cout << "  " << tricky << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. HTML template
    // ------------------------------------------------------------------
    std::string html = R"html(<!DOCTYPE html>
<html>
<head><title>Hello</title></head>
<body>
    <h1>Welcome, "User"!</h1>
    <p>Path: C:\Users\test</p>
</body>
</html>)html";

    std::cout << "=== HTML ===" << std::endl;
    std::cout << html << std::endl;

    return 0;
}

/*
Expected output:

=== Raw vs regular ===
  Regular: Line1\nLine2\tTabbed
  Raw:     Line1\nLine2\tTabbed

=== File paths ===
  C:\Users\Alice\Documents\report.txt
  \\server\share\folder\file.dat

=== Regex patterns ===
  Email: \b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Z]{2,}\b
  IP:    \d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}

=== JSON ===
{
    "name": "Alice",
    "age": 30,
    "scores": [95, 87, 92],
    "address": {
        "city": "Wonderland"
    }
}

=== SQL ===
SELECT u.name, u.email, COUNT(o.id)
FROM users u
LEFT JOIN orders o ON u.id = o.user_id
WHERE u.active = true
GROUP BY u.name, u.email
HAVING COUNT(o.id) > 5;

=== Custom delimiter ===
  She said: "Use R"(...)" for raw strings!"

=== HTML ===
<!DOCTYPE html>
<html>
<head><title>Hello</title></head>
<body>
    <h1>Welcome, "User"!</h1>
    <p>Path: C:\Users\test</p>
</body>
</html>
*/
