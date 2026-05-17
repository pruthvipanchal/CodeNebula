// CodeNebula - C++03 Example: Value Initialization (Refined Rules)
// Compile: g++ -std=c++03 -Wall -Wextra -o value_initialization value_initialization.cpp
//
// C++03 refined the rules for value initialization using T().
// Key guarantee: T() zero-initializes POD types and their members,
// even without a user-defined constructor.

#include <iostream>
#include <cstring>

// ============================================================
// 1. POD struct — no constructor
// ============================================================
struct SensorReading {
    int   id;
    float temperature;
    bool  active;
};

// ============================================================
// 2. Non-POD struct — has a constructor
// ============================================================
struct Config {
    int    timeout;
    double rate;
    bool   enabled;

    Config() : timeout(0), rate(0.0), enabled(false) {}
};

// ============================================================
// 3. Nested POD — struct containing another struct
// ============================================================
struct Point {
    int x;
    int y;
};

struct Rectangle {
    Point topLeft;
    Point bottomRight;
    int   color;
};

// Helper: print raw bytes of a memory region
void printBytes(const void* ptr, std::size_t size) {
    const unsigned char* bytes = static_cast<const unsigned char*>(ptr);
    bool allZero = true;
    for (std::size_t i = 0; i < size; ++i) {
        if (bytes[i] != 0) {
            allZero = false;
            break;
        }
    }
    std::cout << (allZero ? "all zeros" : "NOT all zeros") << std::endl;
}

int main() {
    std::cout << "=== C++03 Value Initialization ===" << std::endl;

    // --------------------------------------------------------
    // Demo 1: Value-initialized POD (guaranteed zero in C++03)
    // --------------------------------------------------------
    std::cout << "\n--- Demo 1: Value-Initialized POD ---" << std::endl;
    SensorReading sensor = SensorReading();  // value-initialization

    std::cout << "sensor.id:          " << sensor.id << std::endl;
    std::cout << "sensor.temperature: " << sensor.temperature << std::endl;
    std::cout << "sensor.active:      " << sensor.active << std::endl;
    std::cout << "Raw bytes: ";
    printBytes(&sensor, sizeof(sensor));

    // --------------------------------------------------------
    // Demo 2: Value-initialized built-in types
    // --------------------------------------------------------
    std::cout << "\n--- Demo 2: Value-Initialized Scalars ---" << std::endl;
    int    i = int();
    double d = double();
    bool   b = bool();
    char   c = char();

    std::cout << "int():    " << i << std::endl;
    std::cout << "double(): " << d << std::endl;
    std::cout << "bool():   " << b << std::endl;
    std::cout << "char():   " << static_cast<int>(c) << std::endl;

    // --------------------------------------------------------
    // Demo 3: Value-initialized array via new
    // --------------------------------------------------------
    std::cout << "\n--- Demo 3: Value-Initialized Dynamic Array ---" << std::endl;
    int* arr = new int[5]();  // all elements zero-initialized
    std::cout << "Dynamic array: ";
    for (int idx = 0; idx < 5; ++idx) {
        std::cout << arr[idx] << " ";
    }
    std::cout << std::endl;
    delete[] arr;

    // --------------------------------------------------------
    // Demo 4: Nested POD value-initialization
    // --------------------------------------------------------
    std::cout << "\n--- Demo 4: Nested POD ---" << std::endl;
    Rectangle rect = Rectangle();

    std::cout << "rect.topLeft.x:     " << rect.topLeft.x << std::endl;
    std::cout << "rect.topLeft.y:     " << rect.topLeft.y << std::endl;
    std::cout << "rect.bottomRight.x: " << rect.bottomRight.x << std::endl;
    std::cout << "rect.bottomRight.y: " << rect.bottomRight.y << std::endl;
    std::cout << "rect.color:         " << rect.color << std::endl;
    std::cout << "Raw bytes: ";
    printBytes(&rect, sizeof(rect));

    // --------------------------------------------------------
    // Demo 5: Non-POD with constructor (calls constructor)
    // --------------------------------------------------------
    std::cout << "\n--- Demo 5: Non-POD (constructor called) ---" << std::endl;
    Config cfg = Config();  // calls user-defined constructor

    std::cout << "cfg.timeout: " << cfg.timeout << std::endl;
    std::cout << "cfg.rate:    " << cfg.rate << std::endl;
    std::cout << "cfg.enabled: " << cfg.enabled << std::endl;

    // --------------------------------------------------------
    // Demo 6: Heap-allocated value-initialized object
    // --------------------------------------------------------
    std::cout << "\n--- Demo 6: Heap Value-Init ---" << std::endl;
    SensorReading* heapSensor = new SensorReading();  // zero-initialized
    std::cout << "heapSensor->id:          " << heapSensor->id << std::endl;
    std::cout << "heapSensor->temperature: " << heapSensor->temperature << std::endl;
    std::cout << "heapSensor->active:      " << heapSensor->active << std::endl;
    delete heapSensor;

    std::cout << "\n=== All value-initialized members are guaranteed zero ===" << std::endl;

    return 0;
}

// Expected Output:
// === C++03 Value Initialization ===
//
// --- Demo 1: Value-Initialized POD ---
// sensor.id:          0
// sensor.temperature: 0
// sensor.active:      0
// Raw bytes: all zeros
//
// --- Demo 2: Value-Initialized Scalars ---
// int():    0
// double(): 0
// bool():   0
// char():   0
//
// --- Demo 3: Value-Initialized Dynamic Array ---
// Dynamic array: 0 0 0 0 0
//
// --- Demo 4: Nested POD ---
// rect.topLeft.x:     0
// rect.topLeft.y:     0
// rect.bottomRight.x: 0
// rect.bottomRight.y: 0
// rect.color:         0
// Raw bytes: all zeros
//
// --- Demo 5: Non-POD (constructor called) ---
// cfg.timeout: 0
// cfg.rate:    0
// cfg.enabled: 0
//
// --- Demo 6: Heap Value-Init ---
// heapSensor->id:          0
// heapSensor->temperature: 0
// heapSensor->active:      0
//
// === All value-initialized members are guaranteed zero ===
