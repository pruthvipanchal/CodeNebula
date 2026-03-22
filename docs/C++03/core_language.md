# C++03 Core Language Concepts

This document covers new or evolved C++03 core language concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++03/). Only additions from C++98 are included.

## Value Initialization (Refined Rules)
**Explanation**: C++03 refined the rules for value initialization, establishing a clear three-step process: if a type has a user-declared constructor, that constructor is called; if it is a non-union class without a user-declared constructor, every member is value-initialized; otherwise, the object is zero-initialized. This eliminated inconsistencies in C++98 where the behavior of `T()` was ambiguous for certain class types, giving developers a reliable way to guarantee clean initial state.
**Real-World Scenario**: In an embedded sensor monitoring system, a telemetry struct accumulates readings over time. When resetting between sampling windows, value initialization guarantees every numeric field starts at zero and every nested object is properly default-constructed, preventing stale data from leaking between measurement cycles.
**Snippet**:
```cpp
#include <iostream>

struct SensorReading {
    double temperature;
    double humidity;
    int    sampleCount;
};

int main() {
    // Value initialization: all members guaranteed zero-initialized
    SensorReading baseline = SensorReading();

    std::cout << "Temperature: " << baseline.temperature  << "\n";  // 0.0
    std::cout << "Humidity:    " << baseline.humidity      << "\n";  // 0.0
    std::cout << "Samples:     " << baseline.sampleCount   << "\n";  // 0

    // Also works with new-expressions
    SensorReading* heapReading = new SensorReading();
    std::cout << "Heap temp:   " << heapReading->temperature << "\n"; // 0.0
    delete heapReading;

    return 0;
}
```
**Example**: [value_initialization.cpp](../examples/C++03/value_initialization.cpp)

## Explicit Template Argument Specification for Constructors
**Explanation**: C++03 clarified that template arguments can be explicitly specified for constructor templates during object creation. This matters when the compiler cannot deduce the template parameters from the constructor arguments alone, allowing developers to disambiguate or force a particular conversion path at construction time.
**Real-World Scenario**: A data pipeline ingests values from heterogeneous sources (files, network, user input) where the raw bytes need to be reinterpreted as specific numeric types. A conversion wrapper with a templated constructor lets callers explicitly state the desired source interpretation, preventing silent narrowing or mismatched type deductions.
**Snippet**:
```cpp
#include <iostream>

class DataConverter {
    double value_;
public:
    // Templated constructor: SourceType may not always be deducible
    template <typename SourceType>
    explicit DataConverter(SourceType raw) : value_(static_cast<double>(raw)) {
        std::cout << "Converted from source value: " << raw
                  << " -> " << value_ << "\n";
    }

    double getValue() const { return value_; }
};

int main() {
    int rawSensor = 1023;

    // Explicit template argument tells the constructor to treat
    // the argument as a float before converting to double
    DataConverter reading = DataConverter(static_cast<float>(rawSensor));

    // Without explicit guidance, deduction uses int directly
    DataConverter directReading(rawSensor);

    std::cout << "Float-path value:  " << reading.getValue()       << "\n";
    std::cout << "Direct-path value: " << directReading.getValue() << "\n";

    return 0;
}
```
**Example**: [explicit_template_constructors.cpp](../examples/C++03/explicit_template_constructors.cpp)

## POD (Plain Old Data) Type Definition Refinement
**Explanation**: C++03 tightened the definition of POD types to remove ambiguities from the C++98 standard. A POD-struct must be an aggregate class with no non-static members of non-POD type, no user-defined assignment operator or destructor, and no non-static reference members. These refined rules ensured that POD types are layout-compatible with equivalent C structs, making them safe for low-level operations such as `memcpy`, binary serialization, and hardware register mapping.
**Real-World Scenario**: In a network protocol library, packet headers must be laid out exactly as the wire format specifies. By keeping the header struct within POD constraints, the developer can safely cast raw byte buffers directly to the struct type, use `memcmp` for equality checks, and pass the struct across a C API boundary with guaranteed layout fidelity.
**Snippet**:
```cpp
#include <cstring>
#include <iostream>

// POD-compliant packet header — safe for memcpy and binary I/O
struct PacketHeader {
    unsigned int  sourceAddr;
    unsigned int  destAddr;
    unsigned short payloadLen;
    unsigned char  flags;
    unsigned char  checksum;
};

int main() {
    // Build a header from a raw byte buffer (simulating network receive)
    unsigned char buffer[sizeof(PacketHeader)];
    std::memset(buffer, 0, sizeof(buffer));

    // Simulate filling in fields via the wire
    PacketHeader outgoing;
    outgoing.sourceAddr = 0xC0A80001;  // 192.168.0.1
    outgoing.destAddr   = 0xC0A80002;  // 192.168.0.2
    outgoing.payloadLen = 512;
    outgoing.flags      = 0x02;
    outgoing.checksum   = 0xAB;

    // Safe because PacketHeader is POD
    std::memcpy(buffer, &outgoing, sizeof(PacketHeader));

    // On the receiving end, cast back
    PacketHeader incoming;
    std::memcpy(&incoming, buffer, sizeof(PacketHeader));

    std::cout << "Source: 0x" << std::hex << incoming.sourceAddr << "\n";
    std::cout << "Dest:   0x" << incoming.destAddr   << "\n";
    std::cout << "Length: "   << std::dec << incoming.payloadLen << "\n";

    return 0;
}
```
**Example**: [pod_type_refinement.cpp](../examples/C++03/pod_type_refinement.cpp)