// CodeNebula - C++98 Example: Classes
// Compile: g++ -std=c++98 -Wall -Wextra -o example classes.cpp

// Demonstrates classes in C++98: data members, member functions, access
// specifiers (public/private/protected), constructors, the this pointer,
// const member functions, static members, and friend functions.

#include <iostream>
#include <cstring>
#include <cmath>

// ------------------------------------------------------------------
// 1. Basic class with private data and public interface
// ------------------------------------------------------------------
class Rectangle {
private:
    double width_;
    double height_;

public:
    // Constructor
    Rectangle(double w, double h) : width_(w), height_(h) {}

    // Getters (const member functions - promise not to modify the object)
    double getWidth() const  { return width_; }
    double getHeight() const { return height_; }

    // Setters
    void setWidth(double w)  { width_ = w; }
    void setHeight(double h) { height_ = h; }

    // Computation methods
    double area() const      { return width_ * height_; }
    double perimeter() const { return 2.0 * (width_ + height_); }
    bool isSquare() const    { return width_ == height_; }

    // Display
    void print() const
    {
        std::cout << "Rectangle(" << width_ << " x " << height_ << ")";
    }
};

// ------------------------------------------------------------------
// 2. Class demonstrating all three access specifiers
// ------------------------------------------------------------------
class BankAccount {
private:
    char owner_[50];
    double balance_;
    int transactionCount_;

    // Private helper
    void logTransaction(const char* type, double amount)
    {
        ++transactionCount_;
        std::cout << "    [Transaction #" << transactionCount_ << "] "
                  << type << ": $" << amount << std::endl;
    }

public:
    BankAccount(const char* owner, double initialBalance)
        : balance_(initialBalance), transactionCount_(0)
    {
        std::strncpy(owner_, owner, 49);
        owner_[49] = '\0';
    }

    void deposit(double amount)
    {
        if (amount > 0) {
            balance_ += amount;
            logTransaction("Deposit", amount);
        }
    }

    bool withdraw(double amount)
    {
        if (amount > 0 && amount <= balance_) {
            balance_ -= amount;
            logTransaction("Withdrawal", amount);
            return true;
        }
        std::cout << "    Withdrawal of $" << amount << " denied." << std::endl;
        return false;
    }

    double getBalance() const { return balance_; }
    const char* getOwner() const { return owner_; }

    void printStatement() const
    {
        std::cout << "    Account: " << owner_
                  << " | Balance: $" << balance_
                  << " | Transactions: " << transactionCount_ << std::endl;
    }
};

// ------------------------------------------------------------------
// 3. Class demonstrating the 'this' pointer
// ------------------------------------------------------------------
class Vector2D {
private:
    double x_;
    double y_;

public:
    Vector2D(double x, double y) : x_(x), y_(y) {}

    // 'this' pointer returns reference for method chaining
    Vector2D& setX(double x) { this->x_ = x; return *this; }
    Vector2D& setY(double y) { this->y_ = y; return *this; }

    Vector2D& scale(double factor)
    {
        this->x_ *= factor;
        this->y_ *= factor;
        return *this;
    }

    Vector2D& add(const Vector2D& other)
    {
        this->x_ += other.x_;
        this->y_ += other.y_;
        return *this;
    }

    double magnitude() const
    {
        return std::sqrt(x_ * x_ + y_ * y_);
    }

    void print() const
    {
        std::cout << "(" << x_ << ", " << y_ << ")";
    }
};

// ------------------------------------------------------------------
// 4. Class with static members
// ------------------------------------------------------------------
class Counter {
private:
    int id_;
    static int count_;       // shared across all instances
    static int nextId_;

public:
    Counter() : id_(nextId_++)
    {
        ++count_;
    }

    ~Counter()
    {
        --count_;
    }

    int getId() const { return id_; }

    static int getCount() { return count_; }

    void print() const
    {
        std::cout << "    Counter id=" << id_
                  << " (total active: " << count_ << ")" << std::endl;
    }
};

// Static member definitions (must be outside the class)
int Counter::count_ = 0;
int Counter::nextId_ = 1;

// ------------------------------------------------------------------
// 5. Class with friend function
// ------------------------------------------------------------------
class Temperature {
private:
    double celsius_;

public:
    Temperature(double c) : celsius_(c) {}

    double getCelsius() const { return celsius_; }
    double getFahrenheit() const { return celsius_ * 9.0 / 5.0 + 32.0; }

    // Friend function can access private members
    friend Temperature addTemperatures(const Temperature& a, const Temperature& b);
    friend void printDetailed(const Temperature& t);
};

Temperature addTemperatures(const Temperature& a, const Temperature& b)
{
    // Can access private celsius_ because it's a friend
    return Temperature(a.celsius_ + b.celsius_);
}

void printDetailed(const Temperature& t)
{
    // Can access private celsius_ directly
    std::cout << "    " << t.celsius_ << " C = " << t.getFahrenheit() << " F" << std::endl;
}

// ------------------------------------------------------------------
// 6. Struct vs Class (only difference: default access)
// ------------------------------------------------------------------
struct Point {        // default: public
    double x;
    double y;

    Point(double px, double py) : x(px), y(py) {}

    double distanceTo(const Point& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};

int main()
{
    // ------------------------------------------------------------------
    // Demo 1: Basic class usage
    // ------------------------------------------------------------------
    std::cout << "=== Rectangle Class ===" << std::endl;

    Rectangle r(5.0, 3.0);
    std::cout << "  ";
    r.print();
    std::cout << std::endl;
    std::cout << "  Area:      " << r.area() << std::endl;
    std::cout << "  Perimeter: " << r.perimeter() << std::endl;
    std::cout << "  Is square? " << (r.isSquare() ? "yes" : "no") << std::endl;

    r.setWidth(4.0);
    r.setHeight(4.0);
    std::cout << "  After resize: ";
    r.print();
    std::cout << std::endl;
    std::cout << "  Is square? " << (r.isSquare() ? "yes" : "no") << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 2: Encapsulation with BankAccount
    // ------------------------------------------------------------------
    std::cout << "=== BankAccount Class ===" << std::endl;

    BankAccount acct("Alice", 1000.0);
    acct.printStatement();

    acct.deposit(500.0);
    acct.withdraw(200.0);
    acct.withdraw(2000.0);    // denied
    acct.printStatement();
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 3: Method chaining with 'this'
    // ------------------------------------------------------------------
    std::cout << "=== Vector2D - Method Chaining ===" << std::endl;

    Vector2D v(1.0, 2.0);
    std::cout << "  Original: ";
    v.print();
    std::cout << std::endl;

    // Chain multiple operations
    v.setX(3.0).setY(4.0).scale(2.0);
    std::cout << "  After setX(3).setY(4).scale(2): ";
    v.print();
    std::cout << std::endl;
    std::cout << "  Magnitude: " << v.magnitude() << std::endl;

    Vector2D v2(1.0, 1.0);
    v.add(v2).scale(0.5);
    std::cout << "  After add(1,1).scale(0.5): ";
    v.print();
    std::cout << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 4: Static members
    // ------------------------------------------------------------------
    std::cout << "=== Static Members ===" << std::endl;

    std::cout << "  Active counters: " << Counter::getCount() << std::endl;

    Counter c1;
    Counter c2;
    Counter c3;
    c1.print();
    c2.print();
    c3.print();

    {
        Counter c4;
        c4.print();
        std::cout << "    (c4 about to go out of scope)" << std::endl;
    }
    std::cout << "  After c4 destroyed, active: " << Counter::getCount() << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 5: Friend function
    // ------------------------------------------------------------------
    std::cout << "=== Friend Function ===" << std::endl;

    Temperature t1(100.0);
    Temperature t2(37.0);

    std::cout << "  t1: ";
    printDetailed(t1);

    std::cout << "  t2: ";
    printDetailed(t2);

    Temperature sum = addTemperatures(t1, t2);
    std::cout << "  t1 + t2: ";
    printDetailed(sum);
    std::cout << std::endl;

    // ------------------------------------------------------------------
    // Demo 6: struct (default public) vs class (default private)
    // ------------------------------------------------------------------
    std::cout << "=== Struct vs Class ===" << std::endl;

    Point p1(0.0, 0.0);
    Point p2(3.0, 4.0);

    // Members are public by default in struct
    std::cout << "  p1 = (" << p1.x << ", " << p1.y << ")" << std::endl;
    std::cout << "  p2 = (" << p2.x << ", " << p2.y << ")" << std::endl;
    std::cout << "  Distance: " << p1.distanceTo(p2) << std::endl;

    return 0;
}

/*
Expected output:

=== Rectangle Class ===
  Rectangle(5 x 3)
  Area:      15
  Perimeter: 16
  Is square? no
  After resize: Rectangle(4 x 4)
  Is square? yes

=== BankAccount Class ===
    Account: Alice | Balance: $1000 | Transactions: 0
    [Transaction #1] Deposit: $500
    [Transaction #2] Withdrawal: $200
    Withdrawal of $2000 denied.
    Account: Alice | Balance: $1300 | Transactions: 2

=== Vector2D - Method Chaining ===
  Original: (1, 2)
  After setX(3).setY(4).scale(2): (6, 8)
  Magnitude: 10
  After add(1,1).scale(0.5): (3.5, 4.5)

=== Static Members ===
  Active counters: 0
    Counter id=1 (total active: 3)
    Counter id=2 (total active: 3)
    Counter id=3 (total active: 3)
    Counter id=4 (total active: 4)
    (c4 about to go out of scope)
  After c4 destroyed, active: 3

=== Friend Function ===
  t1:     100 C = 212 F
  t2:     37 C = 98.6 F
  t1 + t2:     137 C = 278.6 F

=== Struct vs Class ===
  p1 = (0, 0)
  p2 = (3, 4)
  Distance: 5
*/
