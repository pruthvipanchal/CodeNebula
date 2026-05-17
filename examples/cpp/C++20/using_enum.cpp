// CodeNebula - C++20 Example: Using Enum
// Compile: g++ -std=c++20 -Wall -Wextra -o example using_enum.cpp

// Demonstrates the C++20 'using enum' declaration that brings scoped enum
// members into the enclosing scope, reducing verbose qualification.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Basic scoped enum
// ------------------------------------------------------------------
enum class Color { Red, Green, Blue, Yellow, Cyan, Magenta };

std::string color_name(Color c) {
    using enum Color;  // Bring all Color enumerators into scope
    switch (c) {
        case Red:     return "Red";
        case Green:   return "Green";
        case Blue:    return "Blue";
        case Yellow:  return "Yellow";
        case Cyan:    return "Cyan";
        case Magenta: return "Magenta";
    }
    return "Unknown";
}

// ------------------------------------------------------------------
// 2. Without using enum (verbose)
// ------------------------------------------------------------------
enum class Direction { North, South, East, West };

std::string direction_name_verbose(Direction d) {
    switch (d) {
        case Direction::North: return "North";
        case Direction::South: return "South";
        case Direction::East:  return "East";
        case Direction::West:  return "West";
    }
    return "Unknown";
}

// ------------------------------------------------------------------
// 3. Using enum inside a class
// ------------------------------------------------------------------
enum class LogLevel { Debug, Info, Warning, Error, Fatal };

class Logger {
public:
    using enum LogLevel;  // Members accessible as Logger::Debug etc.

    void log(LogLevel level, const std::string& msg) const {
        using enum LogLevel;
        const char* prefix = "";
        switch (level) {
            case Debug:   prefix = "[DEBUG]  "; break;
            case Info:    prefix = "[INFO]   "; break;
            case Warning: prefix = "[WARN]   "; break;
            case Error:   prefix = "[ERROR]  "; break;
            case Fatal:   prefix = "[FATAL]  "; break;
        }
        std::cout << "  " << prefix << msg << std::endl;
    }
};

// ------------------------------------------------------------------
// 4. Using enum in limited scope
// ------------------------------------------------------------------
enum class Suit { Hearts, Diamonds, Clubs, Spades };
enum class Rank { Ace = 1, Two, Three, Four, Five, Six, Seven,
                  Eight, Nine, Ten, Jack, Queen, King };

struct Card {
    Suit suit;
    Rank rank;

    void print() const {
        // using enum only in this function's scope
        using enum Suit;
        using enum Rank;

        // Rank names
        const char* rankStr = "";
        switch (rank) {
            case Ace: rankStr = "Ace"; break;
            case Jack: rankStr = "Jack"; break;
            case Queen: rankStr = "Queen"; break;
            case King: rankStr = "King"; break;
            default: break;
        }

        // Suit names
        const char* suitStr = "";
        switch (suit) {
            case Hearts:   suitStr = "Hearts"; break;
            case Diamonds: suitStr = "Diamonds"; break;
            case Clubs:    suitStr = "Clubs"; break;
            case Spades:   suitStr = "Spades"; break;
        }

        if (rankStr[0])
            std::cout << "  " << rankStr << " of " << suitStr << std::endl;
        else
            std::cout << "  " << static_cast<int>(rank)
                      << " of " << suitStr << std::endl;
    }
};

int main()
{
    std::cout << "=== Using Enum in Switch ===" << std::endl;
    std::cout << "  " << color_name(Color::Red) << std::endl;
    std::cout << "  " << color_name(Color::Cyan) << std::endl;

    std::cout << "\n=== Without Using Enum (verbose) ===" << std::endl;
    std::cout << "  " << direction_name_verbose(Direction::North) << std::endl;
    std::cout << "  " << direction_name_verbose(Direction::West) << std::endl;

    std::cout << "\n=== Using Enum in Class ===" << std::endl;
    Logger logger;
    logger.log(Logger::Info, "Application started");
    logger.log(Logger::Warning, "Low memory");
    logger.log(Logger::Error, "File not found");
    logger.log(Logger::Debug, "x = 42");

    std::cout << "\n=== Using Enum in Limited Scope ===" << std::endl;
    Card c1{Suit::Spades, Rank::Ace};
    Card c2{Suit::Hearts, Rank::Queen};
    Card c3{Suit::Diamonds, Rank::Seven};
    c1.print();
    c2.print();
    c3.print();

    return 0;
}

/*
Expected output:

=== Using Enum in Switch ===
  Red
  Cyan

=== Without Using Enum (verbose) ===
  North
  West

=== Using Enum in Class ===
  [INFO]   Application started
  [WARN]   Low memory
  [ERROR]  File not found
  [DEBUG]  x = 42

=== Using Enum in Limited Scope ===
  Ace of Spades
  Queen of Hearts
  7 of Diamonds
*/
