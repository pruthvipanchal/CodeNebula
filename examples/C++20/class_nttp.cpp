// CodeNebula - C++20 Example: Class Types as Non-Type Template Parameters
// Compile: g++ -std=c++20 -Wall -Wextra -o example class_nttp.cpp

// C++20 allows class types (structs) as non-type template parameters,
// provided they are structural types: all members are public, and
// the type has a constexpr destructor and no mutable/volatile members.

#include <iostream>
#include <algorithm>
#include <cstddef>

// A structural type usable as an NTTP
struct Dimensions {
    int width;
    int height;

    constexpr int area() const { return width * height; }

    // operator<=> is auto-generated for structural types
    friend constexpr bool operator==(const Dimensions&, const Dimensions&) = default;
};

// Template parameterized by a Dimensions value
template <Dimensions D>
struct Screen {
    char pixels[D.area()];

    void print_info() const {
        std::cout << "Screen " << D.width << "x" << D.height
                  << " (" << D.area() << " pixels)\n";
    }
};

// A fixed-length string usable as an NTTP
template <std::size_t N>
struct FixedString {
    char data[N]{};

    constexpr FixedString(const char (&str)[N]) {
        std::copy_n(str, N, data);
    }

    friend std::ostream& operator<<(std::ostream& os, const FixedString& fs) {
        os << fs.data;
        return os;
    }
};

// Template parameterized by a string literal
template <FixedString Name>
struct NamedEntity {
    void greet() const {
        std::cout << "Hello from entity: " << Name << "\n";
    }
};

// Color as NTTP
struct Color {
    unsigned char r, g, b;
    friend constexpr bool operator==(const Color&, const Color&) = default;
};

template <Color C>
void print_color() {
    std::cout << "RGB(" << (int)C.r << ", " << (int)C.g << ", " << (int)C.b << ")\n";
}

// A range specification as NTTP
struct Range {
    int min;
    int max;

    constexpr bool contains(int v) const { return v >= min && v <= max; }
};

template <Range R>
bool in_range(int value) {
    return R.contains(value);
}

int main() {
    std::cout << "=== Class Types as Non-Type Template Parameters ===\n\n";

    // Dimensions as NTTP
    Screen<Dimensions{80, 24}> terminal;
    Screen<Dimensions{1920, 1080}> monitor;
    terminal.print_info();
    monitor.print_info();
    std::cout << "\n";

    // String literal as NTTP via FixedString
    NamedEntity<"Player"> player;
    NamedEntity<"Enemy"> enemy;
    NamedEntity<"NPC"> npc;
    player.greet();
    enemy.greet();
    npc.greet();
    std::cout << "\n";

    // Color as NTTP
    std::cout << "Red:   "; print_color<Color{255, 0, 0}>();
    std::cout << "Green: "; print_color<Color{0, 255, 0}>();
    std::cout << "Blue:  "; print_color<Color{0, 0, 255}>();
    std::cout << "\n";

    // Range as NTTP
    constexpr Range valid_age{0, 150};
    std::cout << "in_range<{0,150}>(25):  " << std::boolalpha
              << in_range<valid_age>(25) << "\n";
    std::cout << "in_range<{0,150}>(200): "
              << in_range<valid_age>(200) << "\n";

    return 0;
}

// Expected output:
// === Class Types as Non-Type Template Parameters ===
//
// Screen 80x24 (1920 pixels)
// Screen 1920x1080 (2073600 pixels)
//
// Hello from entity: Player
// Hello from entity: Enemy
// Hello from entity: NPC
//
// Red:   RGB(255, 0, 0)
// Green: RGB(0, 255, 0)
// Blue:  RGB(0, 0, 255)
//
// in_range<{0,150}>(25):  true
// in_range<{0,150}>(200): false
