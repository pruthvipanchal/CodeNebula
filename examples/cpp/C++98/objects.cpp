// CodeNebula - C++98 Example: Objects
// Compile: g++ -std=c++98 -Wall -Wextra -o example objects.cpp

// Demonstrates object creation and usage in C++98: stack vs heap objects,
// accessing members, object arrays, objects as function parameters, objects
// as return values, const objects, and object lifetime.

#include <iostream>
#include <cstring>
#include <cmath>

// ------------------------------------------------------------------
// A Color class for demonstrations
// ------------------------------------------------------------------
class Color {
private:
    int r_, g_, b_;

public:
    Color() : r_(0), g_(0), b_(0) {}
    Color(int r, int g, int b) : r_(r), g_(g), b_(b) {}

    int getR() const { return r_; }
    int getG() const { return g_; }
    int getB() const { return b_; }

    void setR(int r) { r_ = r; }
    void setG(int g) { g_ = g; }
    void setB(int b) { b_ = b; }

    void print() const
    {
        std::cout << "RGB(" << r_ << ", " << g_ << ", " << b_ << ")";
    }

    bool equals(const Color& other) const
    {
        return r_ == other.r_ && g_ == other.g_ && b_ == other.b_;
    }
};

// ------------------------------------------------------------------
// A Student class with richer interface
// ------------------------------------------------------------------
class Student {
private:
    char name_[50];
    int grades_[5];
    int gradeCount_;

public:
    Student() : gradeCount_(0)
    {
        std::strcpy(name_, "Unknown");
        for (int i = 0; i < 5; ++i) grades_[i] = 0;
    }

    Student(const char* name) : gradeCount_(0)
    {
        std::strncpy(name_, name, 49);
        name_[49] = '\0';
        for (int i = 0; i < 5; ++i) grades_[i] = 0;
    }

    void addGrade(int grade)
    {
        if (gradeCount_ < 5) {
            grades_[gradeCount_++] = grade;
        }
    }

    double average() const
    {
        if (gradeCount_ == 0) return 0.0;
        int sum = 0;
        for (int i = 0; i < gradeCount_; ++i) {
            sum += grades_[i];
        }
        return static_cast<double>(sum) / gradeCount_;
    }

    const char* getName() const { return name_; }
    int getGradeCount() const { return gradeCount_; }

    void print() const
    {
        std::cout << name_ << " - Grades: [";
        for (int i = 0; i < gradeCount_; ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << grades_[i];
        }
        std::cout << "] Avg: " << average();
    }
};

// ------------------------------------------------------------------
// A Point class for demonstrating object parameters and returns
// ------------------------------------------------------------------
class Point {
public:
    double x, y;

    Point() : x(0), y(0) {}
    Point(double px, double py) : x(px), y(py) {}

    double distanceTo(const Point& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    void print() const
    {
        std::cout << "(" << x << ", " << y << ")";
    }
};

// ------------------------------------------------------------------
// Functions that take and return objects
// ------------------------------------------------------------------

// Pass by value (makes a copy)
void printPointByValue(Point p)
{
    std::cout << "  By value: ";
    p.print();
    std::cout << std::endl;
}

// Pass by const reference (efficient, no copy)
void printPointByRef(const Point& p)
{
    std::cout << "  By ref:   ";
    p.print();
    std::cout << std::endl;
}

// Pass by pointer
void printPointByPtr(const Point* p)
{
    std::cout << "  By ptr:   ";
    p->print();
    std::cout << std::endl;
}

// Return object by value
Point midpoint(const Point& a, const Point& b)
{
    return Point((a.x + b.x) / 2.0, (a.y + b.y) / 2.0);
}

// Modify object via reference
void translate(Point& p, double dx, double dy)
{
    p.x += dx;
    p.y += dy;
}

// Find the closest student to a target average
const Student& findClosestAverage(const Student students[], int count, double target)
{
    int bestIndex = 0;
    double bestDiff = std::fabs(students[0].average() - target);

    for (int i = 1; i < count; ++i) {
        double diff = std::fabs(students[i].average() - target);
        if (diff < bestDiff) {
            bestDiff = diff;
            bestIndex = i;
        }
    }
    return students[bestIndex];
}

int main()
{
    // ------------------------------------------------------------------
    // 1. Creating objects on the stack
    // ------------------------------------------------------------------
    std::cout << "=== Stack Objects ===" << std::endl;

    // Default constructor
    Color black;
    std::cout << "  Default Color: ";
    black.print();
    std::cout << std::endl;

    // Parameterized constructor
    Color red(255, 0, 0);
    Color green(0, 255, 0);
    Color blue(0, 0, 255);

    std::cout << "  Red:   "; red.print();   std::cout << std::endl;
    std::cout << "  Green: "; green.print(); std::cout << std::endl;
    std::cout << "  Blue:  "; blue.print();  std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 2. Accessing and modifying members
    // ------------------------------------------------------------------
    std::cout << "=== Accessing Members ===" << std::endl;

    Color custom(100, 150, 200);
    std::cout << "  Before: "; custom.print(); std::cout << std::endl;
    std::cout << "  R=" << custom.getR() << " G=" << custom.getG()
              << " B=" << custom.getB() << std::endl;

    custom.setR(255);
    custom.setG(128);
    custom.setB(0);
    std::cout << "  After:  "; custom.print(); std::cout << std::endl;

    std::cout << "  red == green? " << (red.equals(green) ? "yes" : "no") << std::endl;
    Color red2(255, 0, 0);
    std::cout << "  red == red2?  " << (red.equals(red2) ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 3. Creating objects on the heap (dynamic)
    // ------------------------------------------------------------------
    std::cout << "=== Heap Objects ===" << std::endl;

    // Single object on heap
    Point* pHeap = new Point(10.0, 20.0);
    std::cout << "  Heap point: ";
    pHeap->print();     // use -> with pointer
    std::cout << std::endl;

    // Access members via pointer
    std::cout << "  x = " << pHeap->x << ", y = " << pHeap->y << std::endl;

    // Modify via pointer
    pHeap->x = 30.0;
    pHeap->y = 40.0;
    std::cout << "  Modified:  ";
    pHeap->print();
    std::cout << std::endl;

    delete pHeap;
    pHeap = NULL;
    std::cout << "  (deleted and set to NULL)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 4. Array of objects
    // ------------------------------------------------------------------
    std::cout << "=== Object Arrays ===" << std::endl;

    // Array on stack (uses default constructor for each element)
    Color palette[5];
    palette[0] = Color(255, 0, 0);
    palette[1] = Color(0, 255, 0);
    palette[2] = Color(0, 0, 255);
    palette[3] = Color(255, 255, 0);
    palette[4] = Color(255, 255, 255);

    const char* names[] = {"Red", "Green", "Blue", "Yellow", "White"};
    for (int i = 0; i < 5; ++i) {
        std::cout << "  " << names[i] << ": ";
        palette[i].print();
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // Dynamic array of objects
    std::cout << "  Dynamic array of Points:" << std::endl;
    int numPoints = 4;
    Point* points = new Point[numPoints];   // default constructor for each
    points[0] = Point(1.0, 1.0);
    points[1] = Point(2.0, 4.0);
    points[2] = Point(3.0, 9.0);
    points[3] = Point(4.0, 16.0);

    for (int i = 0; i < numPoints; ++i) {
        std::cout << "    points[" << i << "] = ";
        points[i].print();
        std::cout << std::endl;
    }

    delete[] points;
    points = NULL;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 5. Objects as function parameters
    // ------------------------------------------------------------------
    std::cout << "=== Objects as Parameters ===" << std::endl;

    Point p(3.0, 4.0);
    printPointByValue(p);       // copy
    printPointByRef(p);         // reference (efficient)
    printPointByPtr(&p);        // pointer

    // Translate modifies the original
    std::cout << "  Before translate: ";
    p.print();
    std::cout << std::endl;

    translate(p, 10.0, 20.0);
    std::cout << "  After translate(10, 20): ";
    p.print();
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 6. Objects as return values
    // ------------------------------------------------------------------
    std::cout << "=== Objects as Return Values ===" << std::endl;

    Point a(0.0, 0.0);
    Point b(10.0, 10.0);
    Point mid = midpoint(a, b);

    std::cout << "  a = "; a.print(); std::cout << std::endl;
    std::cout << "  b = "; b.print(); std::cout << std::endl;
    std::cout << "  midpoint = "; mid.print(); std::cout << std::endl;
    std::cout << "  distance a to b = " << a.distanceTo(b) << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 7. const objects (can only call const member functions)
    // ------------------------------------------------------------------
    std::cout << "=== const Objects ===" << std::endl;

    const Color white(255, 255, 255);
    std::cout << "  const Color white: ";
    white.print();          // OK: print() is const
    std::cout << std::endl;
    std::cout << "  R=" << white.getR() << std::endl;   // OK: getR() is const
    // white.setR(0);       // ERROR: can't call non-const on const object
    std::cout << "  (Cannot call setR() on const object)" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // 8. Array of objects with operations
    // ------------------------------------------------------------------
    std::cout << "=== Student Array ===" << std::endl;

    Student students[4];
    students[0] = Student("Alice");
    students[0].addGrade(90);
    students[0].addGrade(85);
    students[0].addGrade(92);

    students[1] = Student("Bob");
    students[1].addGrade(78);
    students[1].addGrade(82);
    students[1].addGrade(75);

    students[2] = Student("Carol");
    students[2].addGrade(95);
    students[2].addGrade(98);
    students[2].addGrade(97);

    students[3] = Student("Dave");
    students[3].addGrade(88);
    students[3].addGrade(84);
    students[3].addGrade(90);

    for (int i = 0; i < 4; ++i) {
        std::cout << "  ";
        students[i].print();
        std::cout << std::endl;
    }

    const Student& best = findClosestAverage(students, 4, 95.0);
    std::cout << "  Closest to 95.0 avg: " << best.getName()
              << " (" << best.average() << ")" << std::endl;

    return 0;
}

/*
Expected output:

=== Stack Objects ===
  Default Color: RGB(0, 0, 0)
  Red:   RGB(255, 0, 0)
  Green: RGB(0, 255, 0)
  Blue:  RGB(0, 0, 255)

=== Accessing Members ===
  Before: RGB(100, 150, 200)
  R=100 G=150 B=200
  After:  RGB(255, 128, 0)
  red == green? no
  red == red2?  yes

=== Heap Objects ===
  Heap point: (10, 20)
  x = 10, y = 20
  Modified:  (30, 40)
  (deleted and set to NULL)

=== Object Arrays ===
  Red: RGB(255, 0, 0)
  Green: RGB(0, 255, 0)
  Blue: RGB(0, 0, 255)
  Yellow: RGB(255, 255, 0)
  White: RGB(255, 255, 255)

  Dynamic array of Points:
    points[0] = (1, 1)
    points[1] = (2, 4)
    points[2] = (3, 9)
    points[3] = (4, 16)

=== Objects as Parameters ===
  By value: (3, 4)
  By ref:   (3, 4)
  By ptr:   (3, 4)
  Before translate: (3, 4)
  After translate(10, 20): (13, 24)

=== Objects as Return Values ===
  a = (0, 0)
  b = (10, 10)
  midpoint = (5, 5)
  distance a to b = 14.1421

=== const Objects ===
  const Color white: RGB(255, 255, 255)
  R=255
  (Cannot call setR() on const object)

=== Student Array ===
  Alice - Grades: [90, 85, 92] Avg: 89
  Bob - Grades: [78, 82, 75] Avg: 78.3333
  Carol - Grades: [95, 98, 97] Avg: 96.6667
  Dave - Grades: [88, 84, 90] Avg: 87.3333
  Closest to 95.0 avg: Carol (96.6667)
*/
