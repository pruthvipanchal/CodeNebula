// CodeNebula - C++23 Example: std::unreachable
// Compile: g++ -std=c++23 -Wall -Wextra -o example unreachable.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <utility>

// std::unreachable() marks code paths that should never execute.
// It is undefined behavior if reached, but enables compiler optimizations
// (e.g., eliminating dead branches, removing bounds checks).

enum class Direction { North, South, East, West };

// The compiler can optimize this knowing all cases are covered
const char* direction_name(Direction d) {
    switch (d) {
        case Direction::North: return "North";
        case Direction::South: return "South";
        case Direction::East:  return "East";
        case Direction::West:  return "West";
    }
    std::unreachable();  // All enum values handled above
}

// Fast modular mapping: compiler can elide the default path
int map_to_quadrant(int angle) {
    // Assume angle is already normalized to [0, 360)
    if (angle < 90)  return 1;
    if (angle < 180) return 2;
    if (angle < 270) return 3;
    if (angle < 360) return 4;
    std::unreachable();  // Caller guarantees angle in [0, 360)
}

// Index lookup with contract: index is always valid
int fast_lookup(const int* table, int index, int size) {
    if (index >= 0 && index < size) {
        return table[index];
    }
    std::unreachable();  // Contract: caller ensures valid index
}

int main() {
    std::cout << "=== std::unreachable optimization hint ===\n\n";

    // Enum switch with unreachable default
    std::cout << "Direction::North -> " << direction_name(Direction::North) << "\n";
    std::cout << "Direction::East  -> " << direction_name(Direction::East) << "\n";
    std::cout << "Direction::West  -> " << direction_name(Direction::West) << "\n\n";

    // Quadrant mapping
    std::cout << "Angle  45 -> Quadrant " << map_to_quadrant(45) << "\n";
    std::cout << "Angle 135 -> Quadrant " << map_to_quadrant(135) << "\n";
    std::cout << "Angle 270 -> Quadrant " << map_to_quadrant(270) << "\n\n";

    // Fast lookup
    int data[] = {10, 20, 30, 40, 50};
    std::cout << "Lookup index 2: " << fast_lookup(data, 2, 5) << "\n";
    std::cout << "Lookup index 4: " << fast_lookup(data, 4, 5) << "\n";

    std::cout << "\nNote: std::unreachable() is UB if actually reached.\n";
    std::cout << "Use only when the code path is provably impossible.\n";

    return 0;
}

// Expected output:
// === std::unreachable optimization hint ===
//
// Direction::North -> North
// Direction::East  -> East
// Direction::West  -> West
//
// Angle  45 -> Quadrant 1
// Angle 135 -> Quadrant 2
// Angle 270 -> Quadrant 3
//
// Lookup index 2: 30
// Lookup index 4: 50
//
// Note: std::unreachable() is UB if actually reached.
// Use only when the code path is provably impossible.
