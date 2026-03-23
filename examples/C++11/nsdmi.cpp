// CodeNebula - C++11 Example: Non-Static Data Member Initializers (NSDMI)
// Compile: g++ -std=c++11 -Wall -Wextra -o example nsdmi.cpp

// Demonstrates non-static data member initializers (NSDMI): default values
// specified directly at the point of declaration. This reduces constructor
// boilerplate and ensures members always have sensible defaults.

#include <iostream>
#include <string>
#include <vector>

// Real-world scenario: configuration with sensible defaults
class ServerConfig {
public:
    // NSDMI: defaults right where members are declared
    std::string host    = "0.0.0.0";
    int         port    = 8080;
    int         workers = 4;
    bool        ssl     = false;
    std::string logFile = "/var/log/server.log";

    // Default constructor uses all NSDMIs automatically
    ServerConfig() = default;

    // Custom constructor overrides some defaults
    ServerConfig(const std::string& h, int p)
        : host(h), port(p)    // only override host and port
    {                          // workers, ssl, logFile keep defaults
    }

    void print() const
    {
        std::cout << "  host:    " << host << std::endl;
        std::cout << "  port:    " << port << std::endl;
        std::cout << "  workers: " << workers << std::endl;
        std::cout << "  ssl:     " << (ssl ? "true" : "false") << std::endl;
        std::cout << "  logFile: " << logFile << std::endl;
    }
};

// NSDMI with various types and expressions
class Particle {
public:
    double x      = 0.0;
    double y      = 0.0;
    double vx     = 0.0;
    double vy     = -9.8;     // default: falling due to gravity
    double mass   = 1.0;
    bool   active = true;
    std::string label = "particle";

    // Constructor can still override
    Particle(double px, double py, const std::string& name)
        : x(px), y(py), label(name)
    {
        // vx, vy, mass, active all keep their NSDMI defaults
    }

    void print() const
    {
        std::cout << "  " << label << " at (" << x << "," << y
                  << ") v=(" << vx << "," << vy << ") m=" << mass
                  << (active ? " [active]" : " [inactive]") << std::endl;
    }
};

// NSDMI with brace initialization
struct Rect {
    int left   {0};
    int top    {0};
    int width  {100};
    int height {100};

    void print() const
    {
        std::cout << "  Rect(" << left << "," << top
                  << "," << width << "," << height << ")" << std::endl;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // 1. Default-constructed uses all NSDMIs
    // ------------------------------------------------------------------
    ServerConfig defaults;

    std::cout << "=== Default ServerConfig ===" << std::endl;
    defaults.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Partial override in constructor
    // ------------------------------------------------------------------
    ServerConfig custom("api.example.com", 443);

    std::cout << "=== Custom ServerConfig ===" << std::endl;
    custom.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Particle with mixed defaults
    // ------------------------------------------------------------------
    Particle p(5.0, 10.0, "bullet");

    std::cout << "=== Particle ===" << std::endl;
    p.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Brace-style NSDMI
    // ------------------------------------------------------------------
    Rect r1;
    Rect r2{10, 20, 200, 150};

    std::cout << "=== Rect with NSDMI ===" << std::endl;
    r1.print();
    r2.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. NSDMI reduces constructor count
    // ------------------------------------------------------------------
    std::cout << "=== Benefit summary ===" << std::endl;
    std::cout << "  Before NSDMI: each constructor must init every member" << std::endl;
    std::cout << "  With NSDMI:   constructors only set non-default values" << std::endl;
    std::cout << "  Result: fewer constructors, less duplicated code" << std::endl;

    return 0;
}

/*
Expected output:

=== Default ServerConfig ===
  host:    0.0.0.0
  port:    8080
  workers: 4
  ssl:     false
  logFile: /var/log/server.log

=== Custom ServerConfig ===
  host:    api.example.com
  port:    443
  workers: 4
  ssl:     false
  logFile: /var/log/server.log

=== Particle ===
  bullet at (5,10) v=(0,-9.8) m=1 [active]

=== Rect with NSDMI ===
  Rect(0,0,100,100)
  Rect(10,20,200,150)

=== Benefit summary ===
  Before NSDMI: each constructor must init every member
  With NSDMI:   constructors only set non-default values
  Result: fewer constructors, less duplicated code
*/
