// CodeNebula - C++14 Example: std::quoted
// Compile: g++ -std=c++14 -Wall -Wextra -o example quoted.cpp

// Demonstrates std::quoted for stream I/O with embedded quotes and spaces.
// It adds delimiters on output and removes them on input, handling escape
// characters properly. Real-world use: serializing/deserializing strings
// with spaces in text formats, CSV-like output, and configuration files.

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

int main()
{
    // ------------------------------------------------------------------
    // 1. Basic quoted output - wraps string in double quotes
    // ------------------------------------------------------------------
    std::string greeting = "Hello, World!";

    std::cout << "=== Basic Quoted Output ===" << std::endl;
    std::cout << "  Without quoted: " << greeting << std::endl;
    std::cout << "  With quoted   : " << std::quoted(greeting) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Strings with embedded spaces survive round-trip through streams
    // ------------------------------------------------------------------
    std::string path = "Program Files/My App/data.txt";

    std::stringstream ss;
    ss << std::quoted(path);

    std::string recovered;
    ss >> std::quoted(recovered);

    std::cout << "=== Round-Trip with Spaces ===" << std::endl;
    std::cout << "  Original : " << path << std::endl;
    std::cout << "  In stream: " << ss.str() << std::endl;
    std::cout << "  Recovered: " << recovered << std::endl;
    std::cout << "  Match    : " << std::boolalpha << (path == recovered) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Without quoted, >> stops at first space
    // ------------------------------------------------------------------
    std::string with_spaces = "Code Nebula Project";

    std::stringstream ss_bad;
    ss_bad << with_spaces;
    std::string bad_read;
    ss_bad >> bad_read;

    std::stringstream ss_good;
    ss_good << std::quoted(with_spaces);
    std::string good_read;
    ss_good >> std::quoted(good_read);

    std::cout << "=== Why quoted Matters ===" << std::endl;
    std::cout << "  Original      : " << with_spaces << std::endl;
    std::cout << "  Without quoted: " << bad_read << " (truncated!)" << std::endl;
    std::cout << "  With quoted   : " << good_read << " (preserved)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Strings with embedded quotes (escape handling)
    // ------------------------------------------------------------------
    std::string has_quotes = "She said \"hello\"";

    std::stringstream ss2;
    ss2 << std::quoted(has_quotes);

    std::string result;
    ss2 >> std::quoted(result);

    std::cout << "=== Embedded Quotes ===" << std::endl;
    std::cout << "  Original   : " << has_quotes << std::endl;
    std::cout << "  Serialized : " << ss2.str() << std::endl;
    std::cout << "  Deserialized: " << result << std::endl;
    std::cout << "  Match      : " << (has_quotes == result) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Custom delimiter and escape character
    // ------------------------------------------------------------------
    std::string data = "field*value";

    std::stringstream ss3;
    ss3 << std::quoted(data, '*', '\\');   // delimiter=*, escape=backslash

    std::string custom_result;
    ss3 >> std::quoted(custom_result, '*', '\\');

    std::cout << "=== Custom Delimiters ===" << std::endl;
    std::cout << "  Original   : " << data << std::endl;
    std::cout << "  Serialized : " << ss3.str() << std::endl;
    std::cout << "  Deserialized: " << custom_result << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Practical: multiple fields in one line
    // ------------------------------------------------------------------
    std::string name = "John Doe";
    std::string city = "New York";
    std::string role = "Software Engineer";

    std::stringstream record;
    record << std::quoted(name) << " "
           << std::quoted(city) << " "
           << std::quoted(role);

    std::string r_name, r_city, r_role;
    record >> std::quoted(r_name) >> std::quoted(r_city) >> std::quoted(r_role);

    std::cout << "=== Multi-Field Record ===" << std::endl;
    std::cout << "  Raw record: " << record.str() << std::endl;
    std::cout << "  Name: " << r_name << std::endl;
    std::cout << "  City: " << r_city << std::endl;
    std::cout << "  Role: " << r_role << std::endl;

    return 0;
}

/*
Expected output:

=== Basic Quoted Output ===
  Without quoted: Hello, World!
  With quoted   : "Hello, World!"

=== Round-Trip with Spaces ===
  Original : Program Files/My App/data.txt
  In stream: "Program Files/My App/data.txt"
  Recovered: Program Files/My App/data.txt
  Match    : true

=== Why quoted Matters ===
  Original      : Code Nebula Project
  Without quoted: Code (truncated!)
  With quoted   : Code Nebula Project (preserved)

=== Embedded Quotes ===
  Original   : She said "hello"
  Serialized : "She said \"hello\""
  Deserialized: She said "hello"
  Match      : true

=== Custom Delimiters ===
  Original   : field*value
  Serialized : *field\*value*
  Deserialized: field*value

=== Multi-Field Record ===
  Raw record: "John Doe" "New York" "Software Engineer"
  Name: John Doe
  City: New York
  Role: Software Engineer
*/
