// CodeNebula - C++98 Example: Enumerations
// Compile: g++ -std=c++98 -Wall -Wextra -o example enumerations.cpp

// Demonstrates unscoped enums in C++98: declaration, implicit conversion to
// int, explicit value assignment, use in switch statements, and combining
// enums with arrays for lookup tables.

#include <iostream>

// ------------------------------------------------------------------
// 1. Basic enum - compiler assigns values 0, 1, 2, ...
// ------------------------------------------------------------------
enum Color {
    RED,        // 0
    GREEN,      // 1
    BLUE        // 2
};

// ------------------------------------------------------------------
// 2. Enum with explicit values
// ------------------------------------------------------------------
enum HttpStatus {
    HTTP_OK            = 200,
    HTTP_CREATED       = 201,
    HTTP_BAD_REQUEST   = 400,
    HTTP_NOT_FOUND     = 404,
    HTTP_SERVER_ERROR   = 500
};

// ------------------------------------------------------------------
// 3. Enum used as bit flags (powers of two)
// ------------------------------------------------------------------
enum Permission {
    PERM_NONE    = 0,
    PERM_READ    = 1,   // 0001
    PERM_WRITE   = 2,   // 0010
    PERM_EXECUTE = 4    // 0100
};

// Helper: print a Color name
const char* colorToString(Color c)
{
    switch (c) {
        case RED:   return "RED";
        case GREEN: return "GREEN";
        case BLUE:  return "BLUE";
    }
    return "UNKNOWN";
}

// Helper: print an HttpStatus name
const char* statusToString(HttpStatus s)
{
    switch (s) {
        case HTTP_OK:           return "OK";
        case HTTP_CREATED:      return "Created";
        case HTTP_BAD_REQUEST:  return "Bad Request";
        case HTTP_NOT_FOUND:    return "Not Found";
        case HTTP_SERVER_ERROR: return "Internal Server Error";
    }
    return "Unknown Status";
}

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Basic enum and implicit int conversion
    // ------------------------------------------------------------------
    std::cout << "=== Basic enum ===" << std::endl;

    Color c = GREEN;
    std::cout << "  Color c = GREEN" << std::endl;
    std::cout << "  Integer value: " << c << std::endl;       // implicit conversion
    std::cout << "  Name         : " << colorToString(c) << std::endl;

    // Enums implicitly convert to int, so arithmetic works
    int colorVal = c + 10;
    std::cout << "  c + 10       : " << colorVal << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Iterating over sequential enum values
    // ------------------------------------------------------------------
    std::cout << "=== Iterating over Color ===" << std::endl;
    for (int i = RED; i <= BLUE; ++i) {
        // Cast int back to enum (valid because values are sequential 0..2)
        Color current = static_cast<Color>(i);
        std::cout << "  " << colorToString(current)
                  << " = " << current << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Enum in a switch statement
    // ------------------------------------------------------------------
    std::cout << "=== Switch on Color ===" << std::endl;
    Color chosen = BLUE;
    switch (chosen) {
        case RED:
            std::cout << "  You chose red - the color of passion." << std::endl;
            break;
        case GREEN:
            std::cout << "  You chose green - the color of nature." << std::endl;
            break;
        case BLUE:
            std::cout << "  You chose blue - the color of the sky." << std::endl;
            break;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Enum with explicit values (HTTP status codes)
    // ------------------------------------------------------------------
    std::cout << "=== HTTP status codes ===" << std::endl;
    HttpStatus codes[] = {
        HTTP_OK, HTTP_CREATED, HTTP_BAD_REQUEST,
        HTTP_NOT_FOUND, HTTP_SERVER_ERROR
    };
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << codes[i] << " "
                  << statusToString(codes[i]) << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Bit-flag enum with bitwise operations
    // ------------------------------------------------------------------
    std::cout << "=== Permission flags ===" << std::endl;

    // Combine flags using bitwise OR
    int userPerms = PERM_READ | PERM_WRITE;
    std::cout << "  userPerms = PERM_READ | PERM_WRITE = " << userPerms << std::endl;

    // Test individual flags using bitwise AND
    std::cout << "  Has READ?    : " << ((userPerms & PERM_READ)    ? "yes" : "no") << std::endl;
    std::cout << "  Has WRITE?   : " << ((userPerms & PERM_WRITE)   ? "yes" : "no") << std::endl;
    std::cout << "  Has EXECUTE? : " << ((userPerms & PERM_EXECUTE) ? "yes" : "no") << std::endl;

    // Add EXECUTE permission
    userPerms |= PERM_EXECUTE;
    std::cout << "  After adding EXECUTE: " << userPerms << std::endl;
    std::cout << "  Has EXECUTE? : " << ((userPerms & PERM_EXECUTE) ? "yes" : "no") << std::endl;

    // Remove WRITE permission
    userPerms &= ~PERM_WRITE;
    std::cout << "  After removing WRITE: " << userPerms << std::endl;
    std::cout << "  Has WRITE?   : " << ((userPerms & PERM_WRITE) ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Enum as array index (lookup table pattern)
    // ------------------------------------------------------------------
    std::cout << "=== Enum as array index ===" << std::endl;
    const char* colorNames[] = { "Red", "Green", "Blue" };
    for (int i = RED; i <= BLUE; ++i) {
        std::cout << "  colorNames[" << i << "] = " << colorNames[i] << std::endl;
    }

    return 0;
}

/*
Expected output:

=== Basic enum ===
  Color c = GREEN
  Integer value: 1
  Name         : GREEN
  c + 10       : 11

=== Iterating over Color ===
  RED = 0
  GREEN = 1
  BLUE = 2

=== Switch on Color ===
  You chose blue - the color of the sky.

=== HTTP status codes ===
  200 OK
  201 Created
  400 Bad Request
  404 Not Found
  500 Internal Server Error

=== Permission flags ===
  userPerms = PERM_READ | PERM_WRITE = 3
  Has READ?    : yes
  Has WRITE?   : yes
  Has EXECUTE? : no
  After adding EXECUTE: 7
  Has EXECUTE? : yes
  After removing WRITE: 5
  Has WRITE?   : no

=== Enum as array index ===
  colorNames[0] = Red
  colorNames[1] = Green
  colorNames[2] = Blue
*/
