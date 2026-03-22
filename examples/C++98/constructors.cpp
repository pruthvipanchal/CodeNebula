// CodeNebula - C++98 Example: Constructors
// Compile: g++ -std=c++98 -Wall -Wextra -o example constructors.cpp

// Demonstrates constructors in C++98: default constructors, parameterized
// constructors, overloaded constructors, copy constructors, member initializer
// lists, constructor delegation patterns, and destructor basics.

#include <iostream>
#include <cstring>
#include <cmath>

// ------------------------------------------------------------------
// 1. Class with default, parameterized, and overloaded constructors
// ------------------------------------------------------------------
class Point {
private:
    double x_;
    double y_;

public:
    // Default constructor - no parameters
    Point() : x_(0.0), y_(0.0)
    {
        std::cout << "    Point() default constructor -> ("
                  << x_ << ", " << y_ << ")" << std::endl;
    }

    // Parameterized constructor - two parameters
    Point(double x, double y) : x_(x), y_(y)
    {
        std::cout << "    Point(" << x << ", " << y
                  << ") parameterized constructor" << std::endl;
    }

    // Overloaded constructor - single value for both x and y
    Point(double val) : x_(val), y_(val)
    {
        std::cout << "    Point(" << val
                  << ") single-value constructor" << std::endl;
    }

    // Copy constructor
    Point(const Point& other) : x_(other.x_), y_(other.y_)
    {
        std::cout << "    Point(copy) copy constructor -> ("
                  << x_ << ", " << y_ << ")" << std::endl;
    }

    double getX() const { return x_; }
    double getY() const { return y_; }

    void print() const
    {
        std::cout << "(" << x_ << ", " << y_ << ")";
    }
};

// ------------------------------------------------------------------
// 2. Class showing constructor with member initializer list importance
// ------------------------------------------------------------------
class Student {
private:
    char name_[50];
    int age_;
    double gpa_;
    const int id_;            // const member MUST be initialized in init list
    int& gradeRef_;           // reference member MUST be initialized in init list

    static int nextId_;

public:
    // Constructor using member initializer list
    // const and reference members can ONLY be initialized here, not in the body
    Student(const char* name, int age, double gpa, int& gradeStorage)
        : age_(age),
          gpa_(gpa),
          id_(nextId_++),
          gradeRef_(gradeStorage)
    {
        std::strncpy(name_, name, 49);
        name_[49] = '\0';
    }

    void print() const
    {
        std::cout << "    ID:" << id_ << " " << name_
                  << " Age:" << age_ << " GPA:" << gpa_ << std::endl;
    }
};

int Student::nextId_ = 1001;

// ------------------------------------------------------------------
// 3. Class demonstrating constructor/destructor lifecycle
// ------------------------------------------------------------------
class LifecycleDemo {
private:
    char label_[20];

public:
    LifecycleDemo(const char* label)
    {
        std::strncpy(label_, label, 19);
        label_[19] = '\0';
        std::cout << "    [CONSTRUCT] " << label_ << std::endl;
    }

    // Copy constructor
    LifecycleDemo(const LifecycleDemo& other)
    {
        std::strncpy(label_, other.label_, 19);
        label_[19] = '\0';
        std::strncat(label_, "(cpy)", 19 - std::strlen(label_));
        std::cout << "    [COPY]      " << label_ << std::endl;
    }

    ~LifecycleDemo()
    {
        std::cout << "    [DESTROY]   " << label_ << std::endl;
    }
};

// ------------------------------------------------------------------
// 4. Class with resource management (dynamic memory)
// ------------------------------------------------------------------
class DynamicArray {
private:
    int* data_;
    int size_;
    int capacity_;

public:
    // Default constructor
    DynamicArray() : data_(new int[4]), size_(0), capacity_(4)
    {
        std::cout << "    DynamicArray() - capacity 4" << std::endl;
    }

    // Parameterized constructor
    DynamicArray(int capacity) : data_(new int[capacity]), size_(0), capacity_(capacity)
    {
        std::cout << "    DynamicArray(" << capacity << ")" << std::endl;
    }

    // Constructor with initial values
    DynamicArray(const int arr[], int count)
        : data_(new int[count]), size_(count), capacity_(count)
    {
        for (int i = 0; i < count; ++i) {
            data_[i] = arr[i];
        }
        std::cout << "    DynamicArray(array, " << count << ")" << std::endl;
    }

    // Copy constructor (deep copy)
    DynamicArray(const DynamicArray& other)
        : data_(new int[other.capacity_]),
          size_(other.size_),
          capacity_(other.capacity_)
    {
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
        std::cout << "    DynamicArray(copy) - deep copy" << std::endl;
    }

    // Destructor - frees dynamic memory
    ~DynamicArray()
    {
        std::cout << "    ~DynamicArray() - freeing "
                  << capacity_ << " ints" << std::endl;
        delete[] data_;
    }

    void push(int value)
    {
        if (size_ < capacity_) {
            data_[size_++] = value;
        }
    }

    void print() const
    {
        std::cout << "[";
        for (int i = 0; i < size_; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << data_[i];
        }
        std::cout << "] (size=" << size_ << ", cap=" << capacity_ << ")";
    }
};

// ------------------------------------------------------------------
// 5. Class with many constructor overloads (Rectangle)
// ------------------------------------------------------------------
class Rectangle {
private:
    double x_, y_;        // position
    double width_, height_;
    char name_[20];

public:
    // Default: unit square at origin
    Rectangle()
        : x_(0), y_(0), width_(1), height_(1)
    {
        std::strcpy(name_, "default");
    }

    // Square at origin
    Rectangle(double side)
        : x_(0), y_(0), width_(side), height_(side)
    {
        std::strcpy(name_, "square");
    }

    // Rectangle at origin
    Rectangle(double w, double h)
        : x_(0), y_(0), width_(w), height_(h)
    {
        std::strcpy(name_, "rect");
    }

    // Rectangle at specified position
    Rectangle(double x, double y, double w, double h)
        : x_(x), y_(y), width_(w), height_(h)
    {
        std::strcpy(name_, "positioned");
    }

    // Named rectangle at position
    Rectangle(const char* name, double x, double y, double w, double h)
        : x_(x), y_(y), width_(w), height_(h)
    {
        std::strncpy(name_, name, 19);
        name_[19] = '\0';
    }

    void print() const
    {
        std::cout << "    " << name_ << ": pos(" << x_ << "," << y_
                  << ") size(" << width_ << "x" << height_
                  << ") area=" << width_ * height_ << std::endl;
    }
};

// ------------------------------------------------------------------
// 6. Class demonstrating order of initialization
// ------------------------------------------------------------------
class InitOrder {
private:
    int a_;
    int b_;
    int c_;

public:
    // Members are initialized in DECLARATION ORDER, not init-list order!
    // Here a_ is initialized first, then b_, then c_, regardless of
    // the order they appear in the initializer list.
    InitOrder(int val)
        : c_(val * 3),    // initialized THIRD (declared third)
          a_(val),         // initialized FIRST (declared first)
          b_(val * 2)      // initialized SECOND (declared second)
    {
        std::cout << "    InitOrder: a_=" << a_
                  << " b_=" << b_ << " c_=" << c_ << std::endl;
    }
};

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Default, parameterized, and overloaded constructors
    // ------------------------------------------------------------------
    std::cout << "=== Point Constructors ===" << std::endl;

    Point p1;               // default
    Point p2(3.0, 4.0);    // parameterized (two args)
    Point p3(5.0);          // overloaded (one arg)
    Point p4(p2);           // copy constructor

    std::cout << "  p1 = "; p1.print(); std::cout << std::endl;
    std::cout << "  p2 = "; p2.print(); std::cout << std::endl;
    std::cout << "  p3 = "; p3.print(); std::cout << std::endl;
    std::cout << "  p4 = "; p4.print(); std::cout << " (copy of p2)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: const and reference members require initializer list
    // ------------------------------------------------------------------
    std::cout << "=== Member Initializer List (const/ref) ===" << std::endl;

    int aliceGrade = 95;
    int bobGrade = 88;

    Student alice("Alice", 20, 3.8, aliceGrade);
    Student bob("Bob", 22, 3.5, bobGrade);

    alice.print();
    bob.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Object lifecycle (construction and destruction order)
    // ------------------------------------------------------------------
    std::cout << "=== Object Lifecycle ===" << std::endl;
    std::cout << "  Entering block:" << std::endl;
    {
        LifecycleDemo a("First");
        LifecycleDemo b("Second");
        LifecycleDemo c("Third");
        std::cout << "    --- inside block ---" << std::endl;
        // Destructors called in REVERSE order when block exits
    }
    std::cout << "  Block exited." << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Copy constructor is called in these situations
    // ------------------------------------------------------------------
    std::cout << "=== When Copy Constructor is Called ===" << std::endl;

    std::cout << "  1. Direct initialization:" << std::endl;
    Point original(1.0, 2.0);
    Point copy1(original);           // explicit copy

    std::cout << "  2. Assignment-style initialization:" << std::endl;
    Point copy2 = original;          // also calls copy constructor (NOT assignment)

    std::cout << "  3. Pass by value to function:" << std::endl;
    // (We'll just note this - calling a function that takes Point by value)
    std::cout << "    (copy is made when passing to function by value)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: DynamicArray with multiple constructors
    // ------------------------------------------------------------------
    std::cout << "=== DynamicArray Constructors ===" << std::endl;

    {
        std::cout << "  Creating arrays:" << std::endl;
        DynamicArray arr1;              // default
        arr1.push(10);
        arr1.push(20);
        arr1.push(30);

        DynamicArray arr2(8);           // custom capacity
        arr2.push(100);
        arr2.push(200);

        int initData[] = {1, 2, 3, 4, 5};
        DynamicArray arr3(initData, 5); // from array

        DynamicArray arr4(arr3);        // deep copy

        std::cout << std::endl;
        std::cout << "  arr1: "; arr1.print(); std::cout << std::endl;
        std::cout << "  arr2: "; arr2.print(); std::cout << std::endl;
        std::cout << "  arr3: "; arr3.print(); std::cout << std::endl;
        std::cout << "  arr4: "; arr4.print(); std::cout << " (copy of arr3)" << std::endl;

        std::cout << std::endl;
        std::cout << "  Destructors will fire:" << std::endl;
    }
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: Multiple constructor overloads (Rectangle)
    // ------------------------------------------------------------------
    std::cout << "=== Rectangle Constructor Overloads ===" << std::endl;

    Rectangle r1;                                   // default
    Rectangle r2(5.0);                              // square
    Rectangle r3(4.0, 6.0);                         // rectangle
    Rectangle r4(10.0, 20.0, 30.0, 40.0);          // positioned
    Rectangle r5("player", 100.0, 200.0, 50.0, 50.0); // named

    r1.print();
    r2.print();
    r3.print();
    r4.print();
    r5.print();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 7: Initialization order
    // ------------------------------------------------------------------
    std::cout << "=== Member Initialization Order ===" << std::endl;
    std::cout << "  Members initialize in DECLARATION order:" << std::endl;

    InitOrder io(10);
    std::cout << "  (a_=10, b_=20, c_=30 regardless of init-list order)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 8: Array of objects (default constructor required)
    // ------------------------------------------------------------------
    std::cout << "=== Array of Objects ===" << std::endl;
    std::cout << "  Creating array of 3 Points (default constructor x3):" << std::endl;

    Point arr[3];  // calls default constructor 3 times
    std::cout << "  arr[0] = "; arr[0].print(); std::cout << std::endl;
    std::cout << "  arr[1] = "; arr[1].print(); std::cout << std::endl;
    std::cout << "  arr[2] = "; arr[2].print(); std::cout << std::endl;

    return 0;
}

/*
Expected output:

=== Point Constructors ===
    Point() default constructor -> (0, 0)
    Point(3, 4) parameterized constructor
    Point(5) single-value constructor
    Point(copy) copy constructor -> (3, 4)
  p1 = (0, 0)
  p2 = (3, 4)
  p3 = (5, 5)
  p4 = (3, 4) (copy of p2)

=== Member Initializer List (const/ref) ===
    ID:1001 Alice Age:20 GPA:3.8
    ID:1002 Bob Age:22 GPA:3.5

=== Object Lifecycle ===
  Entering block:
    [CONSTRUCT] First
    [CONSTRUCT] Second
    [CONSTRUCT] Third
    --- inside block ---
    [DESTROY]   Third
    [DESTROY]   Second
    [DESTROY]   First
  Block exited.

=== When Copy Constructor is Called ===
  1. Direct initialization:
    Point(1, 2) parameterized constructor
    Point(copy) copy constructor -> (1, 2)
  2. Assignment-style initialization:
    Point(copy) copy constructor -> (1, 2)
  3. Pass by value to function:
    (copy is made when passing to function by value)

=== DynamicArray Constructors ===
  Creating arrays:
    DynamicArray() - capacity 4
    DynamicArray(8)
    DynamicArray(array, 5)
    DynamicArray(copy) - deep copy

  arr1: [10, 20, 30] (size=3, cap=4)
  arr2: [100, 200] (size=2, cap=8)
  arr3: [1, 2, 3, 4, 5] (size=5, cap=5)
  arr4: [1, 2, 3, 4, 5] (size=5, cap=5) (copy of arr3)

  Destructors will fire:
    ~DynamicArray() - freeing 5 ints
    ~DynamicArray() - freeing 5 ints
    ~DynamicArray() - freeing 8 ints
    ~DynamicArray() - freeing 4 ints

=== Rectangle Constructor Overloads ===
    default: pos(0,0) size(1x1) area=1
    square: pos(0,0) size(5x5) area=25
    rect: pos(0,0) size(4x6) area=24
    positioned: pos(10,20) size(30x40) area=1200
    player: pos(100,200) size(50x50) area=2500

=== Member Initialization Order ===
  Members initialize in DECLARATION order:
    InitOrder: a_=10 b_=20 c_=30
  (a_=10, b_=20, c_=30 regardless of init-list order)

=== Array of Objects ===
  Creating array of 3 Points (default constructor x3):
    Point() default constructor -> (0, 0)
    Point() default constructor -> (0, 0)
    Point() default constructor -> (0, 0)
  arr[0] = (0, 0)
  arr[1] = (0, 0)
  arr[2] = (0, 0)
*/
