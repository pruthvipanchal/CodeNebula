// CodeNebula - C++11 Example: Extern Template
// Compile: g++ -std=c++11 -Wall -Wextra -o example extern_template.cpp
//
// This example demonstrates:
// - extern template to suppress implicit instantiation
// - How it reduces compile time by avoiding duplicate instantiations
// - Explicit instantiation definition vs extern template declaration
// - Practical usage pattern across translation units

#include <iostream>
#include <string>
#include <vector>

// ============================================================
// 1. A template class that would normally be instantiated
//    in every translation unit that uses it
// ============================================================
template <typename T>
class Accumulator {
    T total_;
    int count_;
public:
    Accumulator() : total_(T()), count_(0) {}

    void add(const T& value) {
        total_ += value;
        ++count_;
    }

    T getTotal() const { return total_; }
    int getCount() const { return count_; }
    double getAverage() const {
        return (count_ > 0) ? static_cast<double>(total_) / count_ : 0.0;
    }

    void print(const std::string& label) const {
        std::cout << label << ": total=" << total_
                  << ", count=" << count_
                  << ", avg=" << getAverage() << std::endl;
    }
};

// ============================================================
// 2. Extern template declaration
// ============================================================
// In a real multi-file project, this would go in a header:
//   extern template class Accumulator<int>;
//   extern template class Accumulator<double>;
//
// And one .cpp file would contain the explicit instantiation:
//   template class Accumulator<int>;
//   template class Accumulator<double>;
//
// This prevents the compiler from instantiating these
// specializations in every translation unit that includes
// the header, reducing compile time and object file size.

// For this single-file demo, we use explicit instantiation:
template class Accumulator<int>;
template class Accumulator<double>;

// ============================================================
// 3. Template function with extern template
// ============================================================
template <typename T>
T clamp(T value, T low, T high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

// Explicit instantiation for common types
template int clamp<int>(int, int, int);
template double clamp<double>(double, double, double);

// In other translation units, you would write:
//   extern template int clamp<int>(int, int, int);
//   extern template double clamp<double>(double, double, double);

// ============================================================
// 4. std::vector extern template (common real-world usage)
// ============================================================
// Many standard library implementations use this internally:
//   extern template class std::vector<int>;
// to speed up compilation of commonly-used instantiations.

int main() {
    std::cout << "=== Extern Template ===" << std::endl;

    // Using explicitly instantiated class template
    Accumulator<int> intAcc;
    intAcc.add(10);
    intAcc.add(20);
    intAcc.add(30);
    intAcc.print("int accumulator");

    Accumulator<double> dblAcc;
    dblAcc.add(1.5);
    dblAcc.add(2.5);
    dblAcc.add(3.5);
    dblAcc.print("double accumulator");

    // Using explicitly instantiated function template
    std::cout << "clamp(15, 0, 10) = " << clamp(15, 0, 10) << std::endl;
    std::cout << "clamp(-5, 0, 10) = " << clamp(-5, 0, 10) << std::endl;
    std::cout << "clamp(5, 0, 10) = " << clamp(5, 0, 10) << std::endl;
    std::cout << "clamp(3.7, 1.0, 3.0) = " << clamp(3.7, 1.0, 3.0) << std::endl;

    // Summary of the pattern
    std::cout << "\n--- Extern Template Pattern ---" << std::endl;
    std::cout << "Header:  extern template class Foo<int>;" << std::endl;
    std::cout << "One .cpp: template class Foo<int>;" << std::endl;
    std::cout << "Result:  Faster compilation, smaller object files" << std::endl;

    return 0;
}

// Expected output:
// === Extern Template ===
// int accumulator: total=60, count=3, avg=20
// double accumulator: total=7.5, count=3, avg=2.5
// clamp(15, 0, 10) = 10
// clamp(-5, 0, 10) = 0
// clamp(5, 0, 10) = 5
// clamp(3.7, 1.0, 3.0) = 3
//
// --- Extern Template Pattern ---
// Header:  extern template class Foo<int>;
// One .cpp: template class Foo<int>;
// Result:  Faster compilation, smaller object files
