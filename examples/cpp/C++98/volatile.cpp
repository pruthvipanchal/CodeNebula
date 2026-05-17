// CodeNebula - C++98 Example: volatile Keyword
// Compile: g++ -std=c++98 -Wall -Wextra -o example volatile.cpp

// The 'volatile' keyword tells the compiler that a variable's value may
// change at any time without any action being taken by the code the compiler
// finds nearby. This prevents the compiler from optimizing away reads/writes.
//
// Common use cases:
//   - Memory-mapped hardware registers
//   - Variables shared with interrupt service routines
//   - Variables modified by signal handlers
//   - Preventing optimization of timing/benchmark loops
//
// Note: volatile does NOT provide atomicity or thread safety.

#include <iostream>
#include <ctime>
#include <csignal>

// ------------------------------------------------------------------
// 1. Simulating a hardware register
// ------------------------------------------------------------------
// In embedded systems, hardware registers are at fixed memory addresses.
// Reading them always returns the current hardware state.
struct HardwareDevice {
    volatile int statusRegister;   // May change due to hardware
    volatile int dataRegister;     // May change due to hardware
    int configRegister;            // Only changes through software

    HardwareDevice() : statusRegister(0), dataRegister(0), configRegister(0) {}
};

void checkHardwareStatus(HardwareDevice& dev) {
    // Without volatile, the compiler might read statusRegister once
    // and reuse the cached value, missing hardware updates.
    std::cout << "  Status: " << dev.statusRegister << std::endl;
    std::cout << "  Data:   " << dev.dataRegister << std::endl;

    // Simulate: The hardware "changes" the register
    // (In real code, hardware would do this independently)
    dev.statusRegister = 1;
    dev.dataRegister = 42;

    // The compiler MUST re-read because of volatile
    std::cout << "  Status after change: " << dev.statusRegister << std::endl;
    std::cout << "  Data after change:   " << dev.dataRegister << std::endl;
}

// ------------------------------------------------------------------
// 2. Signal handler example
// ------------------------------------------------------------------
volatile int signalReceived = 0;   // Modified by signal handler

void signalHandler(int signum) {
    // Signal handlers can modify volatile variables safely
    signalReceived = signum;
}

// ------------------------------------------------------------------
// 3. Volatile and const can coexist
//    const volatile = read-only from software, but hardware can change it
// ------------------------------------------------------------------
void demoConstVolatile() {
    // This models a read-only hardware status register
    const volatile int readOnlyRegister = 0xFF;

    // We can read it (compiler won't cache the value)
    std::cout << "  Read-only register: " << readOnlyRegister << std::endl;

    // We CANNOT write to it (const prevents modification)
    // readOnlyRegister = 0;  // Error: assignment of read-only variable
}

// ------------------------------------------------------------------
// 4. Volatile pointer vs pointer to volatile
// ------------------------------------------------------------------
void demoVolatilePointers() {
    int normalVar = 10;
    volatile int volVar = 20;

    // Pointer to volatile int: the pointed-to value may change unexpectedly
    volatile int* ptrToVol = &volVar;
    std::cout << "  *ptrToVol = " << *ptrToVol << std::endl;

    // Volatile pointer: the pointer itself may change unexpectedly
    int* volatile volPtr = &normalVar;
    std::cout << "  *volPtr = " << *volPtr << std::endl;

    // Volatile pointer to volatile int: both may change
    volatile int* volatile bothVol = &volVar;
    std::cout << "  *bothVol = " << *bothVol << std::endl;
}

// ------------------------------------------------------------------
// 5. Preventing loop optimization
// ------------------------------------------------------------------
void busyWait() {
    // Without volatile, the compiler might optimize this entire loop away
    // because it sees that 'i' is never "used" for anything meaningful.
    volatile int i;
    for (i = 0; i < 1000; ++i) {
        // Intentionally empty - simulating a delay
        // volatile ensures the loop actually executes
    }
    std::cout << "  Busy wait completed (" << i << " iterations)" << std::endl;
}

// ------------------------------------------------------------------
// 6. Volatile member in a class
// ------------------------------------------------------------------
class SensorReading {
private:
    volatile double temperature;   // May be updated by hardware/ISR
    volatile bool dataReady;

public:
    SensorReading() : temperature(0.0), dataReady(false) {}

    // Simulate sensor producing a reading
    void updateReading(double temp) {
        temperature = temp;
        dataReady = true;
    }

    // Check and consume the reading
    bool tryRead(double& outTemp) {
        if (dataReady) {
            outTemp = temperature;
            dataReady = false;
            return true;
        }
        return false;
    }

    bool isReady() const {
        // Each access re-reads the volatile variable
        return dataReady;
    }
};

// ------------------------------------------------------------------
// 7. Demonstrating that volatile forces memory reads
// ------------------------------------------------------------------
void demoForceRead() {
    volatile int counter = 0;

    // Each read of 'counter' generates an actual memory load instruction
    // The compiler cannot assume the value hasn't changed
    std::cout << "  Read 1: " << counter << std::endl;

    counter = 5;
    std::cout << "  Read 2: " << counter << std::endl;

    counter = counter + 1;
    std::cout << "  Read 3: " << counter << std::endl;

    // Without volatile, the compiler could replace all three prints
    // with constant values at compile time
}

int main() {
    std::cout << "=== C++98 volatile Keyword ===" << std::endl;

    // --- 1. Hardware register simulation ---
    std::cout << "\n--- 1. Hardware register simulation ---" << std::endl;
    HardwareDevice dev;
    checkHardwareStatus(dev);
    // Expected: Status changes from 0 to 1, Data from 0 to 42

    // --- 2. Signal handler ---
    std::cout << "\n--- 2. Signal handler with volatile ---" << std::endl;
    std::cout << "  signalReceived before: " << signalReceived << std::endl;

    // Install signal handler (SIGINT is portable across all platforms)
    std::signal(SIGINT, signalHandler);
    // Simulate: in a real program the OS sends the signal
    // We'll just demonstrate the variable
    signalReceived = 0;  // Reset
    std::cout << "  signalReceived after reset: " << signalReceived << std::endl;
    std::cout << "  (In real code, the signal handler modifies this)" << std::endl;

    // --- 3. const volatile ---
    std::cout << "\n--- 3. const volatile ---" << std::endl;
    demoConstVolatile();
    // Expected: Read-only register: 255

    // --- 4. Volatile pointers ---
    std::cout << "\n--- 4. Volatile pointers ---" << std::endl;
    demoVolatilePointers();
    // Expected: 20, 10, 20

    // --- 5. Preventing loop optimization ---
    std::cout << "\n--- 5. Busy wait (loop not optimized away) ---" << std::endl;
    busyWait();
    // Expected: Busy wait completed (1000 iterations)

    // --- 6. Volatile class member ---
    std::cout << "\n--- 6. Sensor reading class ---" << std::endl;
    SensorReading sensor;
    std::cout << "  Ready? " << (sensor.isReady() ? "yes" : "no") << std::endl;
    // Expected: no

    sensor.updateReading(23.5);
    std::cout << "  Ready? " << (sensor.isReady() ? "yes" : "no") << std::endl;
    // Expected: yes

    double temp = 0.0;
    if (sensor.tryRead(temp)) {
        std::cout << "  Temperature: " << temp << std::endl;
        // Expected: 23.5
    }
    std::cout << "  Ready after read? " << (sensor.isReady() ? "yes" : "no") << std::endl;
    // Expected: no

    // --- 7. Forced memory reads ---
    std::cout << "\n--- 7. Forced memory reads ---" << std::endl;
    demoForceRead();
    // Expected: 0, 5, 6

    // --- Summary ---
    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "volatile tells the compiler:" << std::endl;
    std::cout << "  - Do NOT cache this variable in a register" << std::endl;
    std::cout << "  - Do NOT optimize away reads or writes" << std::endl;
    std::cout << "  - Do NOT reorder accesses to this variable" << std::endl;
    std::cout << "  - Always read from / write to actual memory" << std::endl;
    std::cout << "\nvolatile does NOT provide:" << std::endl;
    std::cout << "  - Thread safety or atomicity" << std::endl;
    std::cout << "  - Memory ordering guarantees across threads" << std::endl;

    return 0;
}

/*
Expected Output:
=== C++98 volatile Keyword ===

--- 1. Hardware register simulation ---
  Status: 0
  Data:   0
  Status after change: 1
  Data after change:   42

--- 2. Signal handler with volatile ---
  signalReceived before: 0
  signalReceived after reset: 0
  (In real code, the signal handler modifies this)

--- 3. const volatile ---
  Read-only register: 255

--- 4. Volatile pointers ---
  *ptrToVol = 20
  *volPtr = 10
  *bothVol = 20

--- 5. Busy wait (loop not optimized away) ---
  Busy wait completed (1000 iterations)

--- 6. Sensor reading class ---
  Ready? no
  Ready? yes
  Temperature: 23.5
  Ready after read? no

--- 7. Forced memory reads ---
  Read 1: 0
  Read 2: 5
  Read 3: 6

--- Summary ---
volatile tells the compiler:
  - Do NOT cache this variable in a register
  - Do NOT optimize away reads or writes
  - Do NOT reorder accesses to this variable
  - Always read from / write to actual memory

volatile does NOT provide:
  - Thread safety or atomicity
  - Memory ordering guarantees across threads
*/
