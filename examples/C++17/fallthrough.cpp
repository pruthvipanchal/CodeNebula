// CodeNebula - C++17 Example: [[fallthrough]] Attribute
// Compile: g++ -std=c++17 -Wall -Wextra -o example fallthrough.cpp

// Demonstrates [[fallthrough]] in switch statements. This attribute explicitly
// indicates that a case label intentionally falls through to the next, silencing
// compiler warnings about missing break statements.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Basic fallthrough: days until weekend
// ------------------------------------------------------------------
std::string days_until_weekend(int day) {
    std::string result;
    switch (day) {
        case 1:  // Monday
            result += "Mon -> ";
            [[fallthrough]];
        case 2:  // Tuesday
            result += "Tue -> ";
            [[fallthrough]];
        case 3:  // Wednesday
            result += "Wed -> ";
            [[fallthrough]];
        case 4:  // Thursday
            result += "Thu -> ";
            [[fallthrough]];
        case 5:  // Friday
            result += "Fri -> Weekend!";
            break;
        case 6:
        case 7:
            result = "Already weekend!";
            break;
        default:
            result = "Invalid day";
    }
    return result;
}

// ------------------------------------------------------------------
// 2. Permission levels with cumulative access
// ------------------------------------------------------------------
void show_permissions(int level) {
    std::cout << "  Level " << level << " permissions:" << std::endl;
    switch (level) {
        case 3:  // Admin
            std::cout << "    - Delete users" << std::endl;
            std::cout << "    - Modify settings" << std::endl;
            [[fallthrough]];
        case 2:  // Editor
            std::cout << "    - Edit content" << std::endl;
            std::cout << "    - Publish articles" << std::endl;
            [[fallthrough]];
        case 1:  // Viewer
            std::cout << "    - Read content" << std::endl;
            std::cout << "    - View dashboard" << std::endl;
            break;
        default:
            std::cout << "    - No permissions" << std::endl;
    }
}

// ------------------------------------------------------------------
// 3. Character classification with fallthrough
// ------------------------------------------------------------------
std::string classify_char(char c) {
    switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            return "digit";
        case 'a': case 'e': case 'i': case 'o': case 'u':
        case 'A': case 'E': case 'I': case 'O': case 'U':
            return "vowel";
        case '+': case '-':
            // These are both signs AND operators
            [[fallthrough]];
        case '*': case '/':
            return "operator";
        default:
            return "other";
    }
}

int main()
{
    // Days until weekend
    std::cout << "=== days until weekend ===" << std::endl;
    for (int d = 1; d <= 7; ++d) {
        std::cout << "  Day " << d << ": " << days_until_weekend(d) << std::endl;
    }

    // Cumulative permissions
    std::cout << "\n=== cumulative permissions ===" << std::endl;
    for (int level = 1; level <= 3; ++level) {
        show_permissions(level);
        std::cout << std::endl;
    }

    // Character classification
    std::cout << "=== character classification ===" << std::endl;
    for (char c : {'5', 'a', '+', '*', 'Z'}) {
        std::cout << "  '" << c << "' -> " << classify_char(c) << std::endl;
    }

    return 0;
}

/*
Expected output:

=== days until weekend ===
  Day 1: Mon -> Tue -> Wed -> Thu -> Fri -> Weekend!
  Day 2: Tue -> Wed -> Thu -> Fri -> Weekend!
  Day 3: Wed -> Thu -> Fri -> Weekend!
  Day 4: Thu -> Fri -> Weekend!
  Day 5: Fri -> Weekend!
  Day 6: Already weekend!
  Day 7: Already weekend!

=== cumulative permissions ===
  Level 1 permissions:
    - Read content
    - View dashboard

  Level 2 permissions:
    - Edit content
    - Publish articles
    - Read content
    - View dashboard

  Level 3 permissions:
    - Delete users
    - Modify settings
    - Edit content
    - Publish articles
    - Read content
    - View dashboard

=== character classification ===
  '5' -> digit
  'a' -> vowel
  '+' -> operator
  '*' -> operator
  'Z' -> other
*/
