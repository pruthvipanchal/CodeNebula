// CodeNebula - C++17 Example: std::launder
// Compile: g++ -std=c++17 -Wall -Wextra -o example launder.cpp

// Demonstrates std::launder, a pointer optimization barrier. It is needed when
// accessing an object created via placement new in storage that previously held
// a different object, especially when const or reference members are involved.
// std::launder prevents the compiler from assuming the pointer still refers to
// the original object.

#include <iostream>
#include <new>       // std::launder
#include <cstring>
#include <type_traits>

// ------------------------------------------------------------------
// 1. The problem: const member prevents reuse through old pointer
// ------------------------------------------------------------------
struct Widget {
    const int id;    // const member: compiler may cache this value
    double value;

    Widget(int i, double v) : id(i), value(v) {}
};

// ------------------------------------------------------------------
// 2. Simple type demonstrating the concept
// ------------------------------------------------------------------
struct Data {
    const int tag;
    int payload;

    Data(int t, int p) : tag(t), payload(p) {}
};

int main()
{
    // ------------------------------------------------------------------
    // Scenario 1: Placement new over a const-member object
    // ------------------------------------------------------------------
    std::cout << "=== std::launder with const members ===" << std::endl;

    // Allocate aligned storage for Widget
    alignas(Widget) unsigned char buffer[sizeof(Widget)];

    // Construct first widget
    Widget* w1 = new (buffer) Widget{1, 3.14};
    std::cout << "  Original: id=" << w1->id << ", value=" << w1->value << std::endl;

    // Destroy and reconstruct in the same storage
    w1->~Widget();
    Widget* w2_raw = new (buffer) Widget{2, 6.28};

    // w1 still points to the storage, but the object has changed.
    // Because 'id' is const, the compiler might assume w1->id == 1.
    // std::launder tells the compiler: "re-examine the pointer."
    Widget* w2 = std::launder(w2_raw);
    std::cout << "  Laundered: id=" << w2->id << ", value=" << w2->value << std::endl;

    w2->~Widget();

    // ------------------------------------------------------------------
    // Scenario 2: Placement new with Data
    // ------------------------------------------------------------------
    std::cout << "\n=== placement new reuse with launder ===" << std::endl;

    alignas(Data) unsigned char storage[sizeof(Data)];

    Data* d1 = new (storage) Data{100, 42};
    std::cout << "  First : tag=" << d1->tag << ", payload=" << d1->payload << std::endl;

    d1->~Data();
    new (storage) Data{200, 99};

    // Must launder to safely access the new object through a pointer to storage
    Data* d2 = std::launder(reinterpret_cast<Data*>(storage));
    std::cout << "  Second: tag=" << d2->tag << ", payload=" << d2->payload << std::endl;

    d2->~Data();

    // ------------------------------------------------------------------
    // Scenario 3: std::launder with arrays
    // ------------------------------------------------------------------
    std::cout << "\n=== std::launder with array element ===" << std::endl;

    alignas(int) unsigned char arr_buf[sizeof(int) * 3];
    int* arr = new (arr_buf) int[3]{10, 20, 30};
    std::cout << "  arr[0]=" << arr[0] << ", arr[1]=" << arr[1]
              << ", arr[2]=" << arr[2] << std::endl;

    // Rewrite element via launder
    int* elem = std::launder(arr + 1);
    std::cout << "  laundered arr[1] = " << *elem << std::endl;

    // ------------------------------------------------------------------
    // Key takeaway
    // ------------------------------------------------------------------
    std::cout << "\n=== summary ===" << std::endl;
    std::cout << "  std::launder is a pointer optimization barrier." << std::endl;
    std::cout << "  Use it when placement-new replaces an object" << std::endl;
    std::cout << "  with const/reference members in existing storage." << std::endl;

    return 0;
}

/*
Expected output:

=== std::launder with const members ===
  Original: id=1, value=3.14
  Laundered: id=2, value=6.28

=== placement new reuse with launder ===
  First : tag=100, payload=42
  Second: tag=200, payload=99

=== std::launder with array element ===
  arr[0]=10, arr[1]=20, arr[2]=30
  laundered arr[1] = 20

=== summary ===
  std::launder is a pointer optimization barrier.
  Use it when placement-new replaces an object
  with const/reference members in existing storage.
*/
