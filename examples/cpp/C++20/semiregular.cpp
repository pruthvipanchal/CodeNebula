// CodeNebula - C++20 Example: std::semiregular Concept
// Compile: g++ -std=c++20 -Wall -Wextra -o example semiregular.cpp

// std::semiregular<T> requires copyable and default_initializable.
// A semiregular type can be created, copied, moved, and assigned,
// but does not require equality comparison (unlike regular).

#include <concepts>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// A semiregular type (no operator== needed)
struct Transform {
    double scale;
    double offset;
    Transform() : scale(1.0), offset(0.0) {}
    Transform(double s, double o) : scale(s), offset(o) {}
    double apply(double x) const { return x * scale + offset; }
};

// Not semiregular: no default constructor
struct MustInit {
    int value;
    MustInit(int v) : value(v) {}
};

// Not semiregular: not copyable
struct MoveOnly {
    std::unique_ptr<int> ptr;
    MoveOnly() : ptr(std::make_unique<int>(0)) {}
};

// Pipeline that stores semiregular function objects
template <std::semiregular T>
class Pipeline {
    std::vector<T> stages_;
public:
    void add(const T& stage) { stages_.push_back(stage); }
    double run(double input) const {
        double result = input;
        for (const auto& stage : stages_)
            result = stage.apply(result);
        return result;
    }
    std::size_t size() const { return stages_.size(); }
};

template <typename T>
void check_semiregular(const char* name) {
    std::cout << name << " - semiregular: " << std::semiregular<T>
              << ", copyable: " << std::copyable<T>
              << ", default_init: " << std::default_initializable<T> << "\n";
}

int main() {
    // Build a transform pipeline
    Pipeline<Transform> pipe;
    pipe.add(Transform(2.0, 0.0));   // double the value
    pipe.add(Transform(1.0, 10.0));  // add 10
    pipe.add(Transform(0.5, 0.0));   // halve the value

    std::cout << "Pipeline with " << pipe.size() << " stages:\n";
    std::cout << "  run(5)  = " << pipe.run(5) << "\n";
    std::cout << "  run(10) = " << pipe.run(10) << "\n";
    std::cout << "  run(0)  = " << pipe.run(0) << "\n";

    // Default construction and copy
    Transform t1(3.0, 1.0);
    Transform t2 = t1;  // copy
    Transform t3;        // default
    std::cout << "\nt1.apply(5) = " << t1.apply(5) << "\n";
    std::cout << "t2.apply(5) = " << t2.apply(5) << " (copy of t1)\n";
    std::cout << "t3.apply(5) = " << t3.apply(5) << " (default)\n";

    // Concept checks
    std::cout << "\nSemiregular checks:\n";
    check_semiregular<int>("int");
    check_semiregular<Transform>("Transform");
    check_semiregular<MustInit>("MustInit");
    check_semiregular<MoveOnly>("MoveOnly");

    return 0;
}

// Expected output:
// Pipeline with 3 stages:
//   run(5)  = 10
//   run(10) = 15
//   run(0)  = 5
//
// t1.apply(5) = 16
// t2.apply(5) = 16 (copy of t1)
// t3.apply(5) = 5 (default)
//
// Semiregular checks:
// int - semiregular: 1, copyable: 1, default_init: 1
// Transform - semiregular: 1, copyable: 1, default_init: 1
// MustInit - semiregular: 0, copyable: 1, default_init: 0
// MoveOnly - semiregular: 0, copyable: 0, default_init: 1
