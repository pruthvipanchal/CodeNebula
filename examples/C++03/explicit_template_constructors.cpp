// CodeNebula - C++03 Example: Explicit Template Argument Specification for Constructors
// Compile: g++ -std=c++03 -Wall -Wextra -o explicit_template_constructors explicit_template_constructors.cpp
//
// C++03 clarified that constructor templates can have their template
// arguments explicitly specified, enabling type-safe conversions and
// multi-type construction patterns.

#include <iostream>
#include <string>
#include <sstream>
#include <typeinfo>

// ============================================================
// 1. DataConverter — constructor with explicit template arg
//    for input type (Output type is the class template param)
// ============================================================
template <typename OutputType>
class DataConverter {
public:
    // Constructor template: InputType must be explicitly specified
    // when it can't be deduced from arguments
    template <typename InputType>
    explicit DataConverter(InputType input) {
        std::stringstream ss;
        ss << input;
        ss >> value_;
        std::cout << "  Converted " << typeid(InputType).name()
                  << " -> " << typeid(OutputType).name()
                  << ": " << value_ << std::endl;
    }

    OutputType get() const { return value_; }

private:
    OutputType value_;
};

// ============================================================
// 2. TypedFactory — explicit template arg chooses strategy
// ============================================================
class Widget {
public:
    explicit Widget(int id) : id_(id), label_("default") {}
    Widget(int id, const std::string& label) : id_(id), label_(label) {}

    void print() const {
        std::cout << "  Widget[id=" << id_ << ", label=" << label_ << "]" << std::endl;
    }

private:
    int id_;
    std::string label_;
};

// ============================================================
// 3. Pair-like construction with explicit template args
// ============================================================
template <typename T>
class Holder {
public:
    template <typename U>
    explicit Holder(U val) : data_(static_cast<T>(val)) {
        std::cout << "  Holder<" << typeid(T).name() << "> constructed from "
                  << typeid(U).name() << std::endl;
    }

    T get() const { return data_; }

private:
    T data_;
};

// ============================================================
// 4. Multi-type construction
// ============================================================
class Pipeline {
public:
    // Constructor that processes two different types
    template <typename Source, typename Filter>
    Pipeline(Source src, Filter flt) {
        std::stringstream ss;
        ss << "source=" << src << ", filter=" << flt;
        description_ = ss.str();
    }

    void describe() const {
        std::cout << "  Pipeline: " << description_ << std::endl;
    }

private:
    std::string description_;
};

int main() {
    std::cout << "=== Explicit Template Argument Specification for Constructors ===" << std::endl;

    // --------------------------------------------------------
    // Demo 1: DataConverter with explicit input type
    // --------------------------------------------------------
    std::cout << "\n--- Demo 1: DataConverter ---" << std::endl;

    // Convert int to double
    DataConverter<double> d1(42);
    std::cout << "  Result: " << d1.get() << std::endl;

    // Convert double to int
    DataConverter<int> d2(3.14);
    std::cout << "  Result: " << d2.get() << std::endl;

    // Convert string to int
    DataConverter<int> d3(std::string("99"));
    std::cout << "  Result: " << d3.get() << std::endl;

    // --------------------------------------------------------
    // Demo 2: Holder with cross-type construction
    // --------------------------------------------------------
    std::cout << "\n--- Demo 2: Holder Cross-Type ---" << std::endl;

    // int stored in double Holder
    Holder<double> h1(42);
    std::cout << "  Value: " << h1.get() << std::endl;

    // char stored in int Holder
    Holder<int> h2('A');
    std::cout << "  Value: " << h2.get() << " (char 'A' = 65)" << std::endl;

    // float stored in int Holder
    Holder<int> h3(3.7f);
    std::cout << "  Value: " << h3.get() << " (truncated from 3.7)" << std::endl;

    // --------------------------------------------------------
    // Demo 3: Pipeline with deduced template args
    // --------------------------------------------------------
    std::cout << "\n--- Demo 3: Pipeline (deduced args) ---" << std::endl;

    Pipeline p1(100, 0.5);
    p1.describe();

    Pipeline p2(std::string("sensor_data"), 42);
    p2.describe();

    // --------------------------------------------------------
    // Demo 4: Array of Holders with different source types
    // --------------------------------------------------------
    std::cout << "\n--- Demo 4: Multiple Conversions ---" << std::endl;

    Holder<double> values[] = {
        Holder<double>(10),       // from int
        Holder<double>(20L),      // from long
        Holder<double>(3.14f)     // from float
    };

    std::cout << "  Values: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << values[i].get();
        if (i < 2) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "\n=== Constructor templates enable flexible type-safe construction ===" << std::endl;

    return 0;
}

// Expected Output:
// === Explicit Template Argument Specification for Constructors ===
//
// --- Demo 1: DataConverter ---
//   Converted i -> d: 42
//   Result: 42
//   Converted d -> i: 3
//   Result: 3
//   Converted Ss -> i: 99
//   Result: 99
//
// --- Demo 2: Holder Cross-Type ---
//   Holder<d> constructed from i
//   Value: 42
//   Holder<i> constructed from c
//   Value: 65 (char 'A' = 65)
//   Holder<i> constructed from f
//   Value: 3 (truncated from 3.7)
//
// --- Demo 3: Pipeline (deduced args) ---
//   Pipeline: source=100, filter=0.5
//   Pipeline: source=sensor_data, filter=42
//
// --- Demo 4: Multiple Conversions ---
//   Holder<d> constructed from i
//   Holder<d> constructed from l
//   Holder<d> constructed from f
//   Values: 10, 20, 3.14
//
// === Constructor templates enable flexible type-safe construction ===
