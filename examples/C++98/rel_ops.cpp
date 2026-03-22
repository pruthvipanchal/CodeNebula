// CodeNebula - C++98 Example: std::rel_ops
// Compile: g++ -std=c++98 -Wall -Wextra -o example rel_ops.cpp

#include <iostream>
#include <utility>

// Define only operator== and operator<, rel_ops provides the rest
class Version {
    int major_, minor_;
public:
    Version(int maj, int min) : major_(maj), minor_(min) {}

    bool operator==(const Version& rhs) const {
        return major_ == rhs.major_ && minor_ == rhs.minor_;
    }
    bool operator<(const Version& rhs) const {
        if (major_ != rhs.major_) return major_ < rhs.major_;
        return minor_ < rhs.minor_;
    }

    friend std::ostream& operator<<(std::ostream& os, const Version& v) {
        return os << v.major_ << "." << v.minor_;
    }
};

int main() {
    using namespace std::rel_ops; // brings in !=, >, <=, >= from == and <

    Version v1(1, 0);
    Version v2(2, 3);
    Version v3(1, 0);

    std::cout << v1 << " == " << v3 << " : " << (v1 == v3) << std::endl;
    std::cout << v1 << " != " << v2 << " : " << (v1 != v2) << std::endl;
    std::cout << v1 << " <  " << v2 << " : " << (v1 < v2) << std::endl;
    std::cout << v2 << " >  " << v1 << " : " << (v2 > v1) << std::endl;
    std::cout << v1 << " <= " << v3 << " : " << (v1 <= v3) << std::endl;
    std::cout << v2 << " >= " << v1 << " : " << (v2 >= v1) << std::endl;

    return 0;
}

// Expected output:
// 1.0 == 1.0 : 1
// 1.0 != 2.3 : 1
// 1.0 <  2.3 : 1
// 2.3 >  1.0 : 1
// 1.0 <= 1.0 : 1
// 2.3 >= 1.0 : 1
