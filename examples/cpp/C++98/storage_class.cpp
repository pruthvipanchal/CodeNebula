// CodeNebula - C++98 Example: Storage Classes
// Compile: g++ -std=c++98 -Wall -Wextra -o example storage_class.cpp

// Storage classes control the lifetime, visibility, and linkage of variables:
//   - auto     : (default) local scope, automatic lifetime
//   - static   : persists across function calls / limits linkage
//   - extern   : declares a variable defined elsewhere
//   - register : hints at register storage (compiler may ignore)
//   - mutable  : (covered separately in mutable.cpp)
//
// This example focuses on static (local, global, and class member) and extern.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. static local variable: retains value between function calls
// ------------------------------------------------------------------
int callCounter() {
    static int count = 0;  // Initialized only once, persists across calls
    ++count;
    return count;
}

// ------------------------------------------------------------------
// 2. static local for one-time initialization
// ------------------------------------------------------------------
const std::string& getConfig() {
    // This string is created only on the first call
    static std::string config = "DefaultConfig_v1";
    return config;
}

// ------------------------------------------------------------------
// 3. static global variable: internal linkage (file scope only)
//    Cannot be accessed from other translation units.
// ------------------------------------------------------------------
static int fileLocalVar = 42;

static void fileLocalFunction() {
    std::cout << "  fileLocalFunction: fileLocalVar = " << fileLocalVar << std::endl;
}

// ------------------------------------------------------------------
// 4. extern variable: defined in this file, could be accessed from
//    another translation unit via 'extern int sharedVar;'
// ------------------------------------------------------------------
int sharedVar = 999;  // Definition (extern by default for global vars)

// In another .cpp file, you would write:
//   extern int sharedVar;  // Declaration only, uses the one defined above

// ------------------------------------------------------------------
// 5. static class members: shared across all instances
// ------------------------------------------------------------------
class Player {
private:
    std::string name;
    int score;

    static int totalPlayers;     // Shared counter
    static int totalScore;       // Shared score accumulator

public:
    Player(const std::string& n, int s) : name(n), score(s) {
        ++totalPlayers;
        totalScore += s;
    }

    ~Player() {
        --totalPlayers;
        totalScore -= score;
    }

    void print() const {
        std::cout << "  " << name << " (score: " << score << ")" << std::endl;
    }

    // Static member functions: can be called without an instance
    static int getTotalPlayers() { return totalPlayers; }
    static int getTotalScore() { return totalScore; }

    static double getAverageScore() {
        if (totalPlayers == 0) return 0.0;
        return static_cast<double>(totalScore) / totalPlayers;
    }

    static void printStats() {
        std::cout << "  Total players: " << totalPlayers
                  << ", Total score: " << totalScore
                  << ", Average: " << getAverageScore() << std::endl;
    }
};

// Static member definitions (must be outside the class in C++98)
int Player::totalPlayers = 0;
int Player::totalScore = 0;

// ------------------------------------------------------------------
// 6. static in a class: constant (integral types only in C++98)
// ------------------------------------------------------------------
class Config {
public:
    static const int MAX_CONNECTIONS = 100;   // OK in C++98 for integral const
    static const int TIMEOUT = 30;

    // Non-integral static const must be defined outside
    static const double PI;
};

// Definition for non-integral static const
const double Config::PI = 3.14159265;

// ------------------------------------------------------------------
// 7. register keyword: a hint to the compiler
// ------------------------------------------------------------------
int sumWithRegister(int n) {
    register int sum = 0;   // Hint: keep 'sum' in a CPU register
    register int i;         // Hint: keep 'i' in a register
    for (i = 1; i <= n; ++i) {
        sum += i;
    }
    return sum;
    // Note: Modern compilers ignore 'register' and optimize automatically.
}

// ------------------------------------------------------------------
// 8. Demonstrating static local in a recursive context
// ------------------------------------------------------------------
void recursiveCounter(int depth) {
    static int callCount = 0;
    ++callCount;
    std::cout << "  depth=" << depth << ", total calls so far=" << callCount << std::endl;
    if (depth > 0) {
        recursiveCounter(depth - 1);
    }
}

int main() {
    std::cout << "=== C++98 Storage Classes ===" << std::endl;

    // --- 1. static local variable ---
    std::cout << "\n--- 1. Static local variable ---" << std::endl;
    for (int i = 0; i < 5; ++i) {
        std::cout << "  callCounter() = " << callCounter() << std::endl;
    }
    // Expected: 1, 2, 3, 4, 5 (persists across calls)

    // --- 2. static local for lazy initialization ---
    std::cout << "\n--- 2. Static local (lazy init) ---" << std::endl;
    std::cout << "  Config: " << getConfig() << std::endl;
    std::cout << "  Config: " << getConfig() << std::endl;
    // Expected: Same string both times, initialized only once

    // --- 3. static global (file scope) ---
    std::cout << "\n--- 3. Static global (file scope) ---" << std::endl;
    fileLocalFunction();
    // Expected: fileLocalVar = 42
    std::cout << "  fileLocalVar cannot be accessed from other .cpp files" << std::endl;

    // --- 4. extern ---
    std::cout << "\n--- 4. extern variable ---" << std::endl;
    std::cout << "  sharedVar = " << sharedVar << std::endl;
    // Expected: 999
    std::cout << "  Other files can use: extern int sharedVar;" << std::endl;

    // --- 5. static class members ---
    std::cout << "\n--- 5. Static class members ---" << std::endl;
    std::cout << "Before creating players:" << std::endl;
    Player::printStats();
    // Expected: Total players: 0, Total score: 0, Average: 0

    Player p1("Alice", 100);
    Player p2("Bob", 85);
    Player p3("Charlie", 92);

    p1.print();
    p2.print();
    p3.print();

    std::cout << "After creating 3 players:" << std::endl;
    Player::printStats();
    // Expected: Total players: 3, Total score: 277, Average: 92.3333

    {
        Player p4("Diana", 110);
        std::cout << "After adding Diana:" << std::endl;
        Player::printStats();
        // Expected: Total players: 4, Total score: 387
    }
    // p4 destroyed here
    std::cout << "After Diana goes out of scope:" << std::endl;
    Player::printStats();
    // Expected: Total players: 3, Total score: 277

    // Accessing static members through class name
    std::cout << "\nAccess via class name: Player::getTotalPlayers() = "
              << Player::getTotalPlayers() << std::endl;

    // --- 6. static const class members ---
    std::cout << "\n--- 6. Static const members ---" << std::endl;
    std::cout << "  Config::MAX_CONNECTIONS = " << Config::MAX_CONNECTIONS << std::endl;
    std::cout << "  Config::TIMEOUT = " << Config::TIMEOUT << std::endl;
    std::cout << "  Config::PI = " << Config::PI << std::endl;
    // Expected: 100, 30, 3.14159

    // --- 7. register keyword ---
    std::cout << "\n--- 7. register keyword ---" << std::endl;
    std::cout << "  sum(100) = " << sumWithRegister(100) << std::endl;
    // Expected: 5050
    std::cout << "  (register is just a hint, compiler may ignore it)" << std::endl;

    // --- 8. static in recursive context ---
    std::cout << "\n--- 8. Static in recursion ---" << std::endl;
    recursiveCounter(3);
    // Expected: depth=3 calls=1, depth=2 calls=2, depth=1 calls=3, depth=0 calls=4

    return 0;
}

/*
Expected Output:
=== C++98 Storage Classes ===

--- 1. Static local variable ---
  callCounter() = 1
  callCounter() = 2
  callCounter() = 3
  callCounter() = 4
  callCounter() = 5

--- 2. Static local (lazy init) ---
  Config: DefaultConfig_v1
  Config: DefaultConfig_v1

--- 3. Static global (file scope) ---
  fileLocalFunction: fileLocalVar = 42
  fileLocalVar cannot be accessed from other .cpp files

--- 4. extern variable ---
  sharedVar = 999
  Other files can use: extern int sharedVar;

--- 5. Static class members ---
Before creating players:
  Total players: 0, Total score: 0, Average: 0
  Alice (score: 100)
  Bob (score: 85)
  Charlie (score: 92)
After creating 3 players:
  Total players: 3, Total score: 277, Average: 92.3333
After adding Diana:
  Total players: 4, Total score: 387, Average: 96.75
After Diana goes out of scope:
  Total players: 3, Total score: 277, Average: 92.3333

Access via class name: Player::getTotalPlayers() = 3

--- 6. Static const members ---
  Config::MAX_CONNECTIONS = 100
  Config::TIMEOUT = 30
  Config::PI = 3.14159

--- 7. register keyword ---
  sum(100) = 5050
  (register is just a hint, compiler may ignore it)

--- 8. Static in recursion ---
  depth=3, total calls so far=1
  depth=2, total calls so far=2
  depth=1, total calls so far=3
  depth=0, total calls so far=4
*/
