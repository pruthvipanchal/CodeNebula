// CodeNebula - C++14 Example: Aggregate Member Initialization
// Compile: g++ -std=c++14 -Wall -Wextra -o example aggregate_member_init.cpp

// Demonstrates relaxed aggregate initialization rules in C++14. Aggregates
// can now have default member initializers (NSDMIs) and still be initialized
// with brace syntax. In C++11, having a default member initializer made a
// class non-aggregate. Real-world use: configuration structs with sensible
// defaults, POD-like types with partial initialization.

#include <iostream>
#include <string>

// ------------------------------------------------------------------
// 1. Aggregate with default member initializers (C++14 allows this)
// ------------------------------------------------------------------
struct NetworkConfig
{
    std::string host = "localhost";
    int port = 8080;
    int max_retries = 3;
    bool use_ssl = false;
};

// ------------------------------------------------------------------
// 2. Nested aggregates with defaults
// ------------------------------------------------------------------
struct Point
{
    double x = 0.0;
    double y = 0.0;
};

struct Rectangle
{
    Point top_left;
    Point bottom_right;
    std::string label = "unnamed";
};

// ------------------------------------------------------------------
// 3. Array member with default init
// ------------------------------------------------------------------
struct Sensor
{
    int id = -1;
    double readings[3] = {0.0, 0.0, 0.0};
    bool active = true;
};

void print_config(const NetworkConfig& cfg)
{
    std::cout << "  host=" << cfg.host
              << " port=" << cfg.port
              << " retries=" << cfg.max_retries
              << " ssl=" << std::boolalpha << cfg.use_ssl << std::endl;
}

void print_rect(const Rectangle& r)
{
    std::cout << "  [" << r.label << "] ("
              << r.top_left.x << "," << r.top_left.y << ") -> ("
              << r.bottom_right.x << "," << r.bottom_right.y << ")" << std::endl;
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Using all defaults (empty braces)
    // ------------------------------------------------------------------
    NetworkConfig default_cfg{};

    std::cout << "=== All Defaults ===" << std::endl;
    print_config(default_cfg);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Overriding some members, rest keep defaults
    // ------------------------------------------------------------------
    NetworkConfig custom_cfg{"api.example.com", 443};
    // max_retries=3, use_ssl=false come from defaults

    std::cout << "=== Partial Override ===" << std::endl;
    print_config(custom_cfg);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Overriding all members
    // ------------------------------------------------------------------
    NetworkConfig full_cfg{"db.internal", 5432, 5, true};

    std::cout << "=== Full Override ===" << std::endl;
    print_config(full_cfg);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Nested aggregates with defaults
    // ------------------------------------------------------------------
    Rectangle r1{};                                     // all defaults
    Rectangle r2{{1.0, 2.0}, {10.0, 20.0}};           // label defaults
    Rectangle r3{{0.0, 0.0}, {5.0, 5.0}, "square"};   // all specified

    std::cout << "=== Nested Aggregates ===" << std::endl;
    print_rect(r1);
    print_rect(r2);
    print_rect(r3);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Array member defaults
    // ------------------------------------------------------------------
    Sensor s1{};                              // all defaults
    Sensor s2{42, {1.5, 2.5, 3.5}};         // active defaults to true
    Sensor s3{99, {0.0, 0.0, 0.0}, false};  // fully specified

    std::cout << "=== Array Member Defaults ===" << std::endl;
    std::cout << "  s1: id=" << s1.id << " active=" << s1.active
              << " readings=[" << s1.readings[0] << "," << s1.readings[1]
              << "," << s1.readings[2] << "]" << std::endl;
    std::cout << "  s2: id=" << s2.id << " active=" << s2.active
              << " readings=[" << s2.readings[0] << "," << s2.readings[1]
              << "," << s2.readings[2] << "]" << std::endl;
    std::cout << "  s3: id=" << s3.id << " active=" << s3.active
              << " readings=[" << s3.readings[0] << "," << s3.readings[1]
              << "," << s3.readings[2] << "]" << std::endl;

    return 0;
}

/*
Expected output:

=== All Defaults ===
  host=localhost port=8080 retries=3 ssl=false

=== Partial Override ===
  host=api.example.com port=443 retries=3 ssl=false

=== Full Override ===
  host=db.internal port=5432 retries=5 ssl=true

=== Nested Aggregates ===
  [unnamed] (0,0) -> (0,0)
  [unnamed] (1,2) -> (10,20)
  [square] (0,0) -> (5,5)

=== Array Member Defaults ===
  s1: id=-1 active=true readings=[0,0,0]
  s2: id=42 active=true readings=[1.5,2.5,3.5]
  s3: id=99 active=false readings=[0,0,0]
*/
