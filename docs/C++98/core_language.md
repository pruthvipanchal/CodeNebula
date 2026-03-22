# C++98 Core Language Concepts

This document covers C++98 core language concepts with simple explanations, real-world scenarios, and short code snippets. Full examples will be added in [examples folder](../examples/C++98/).

## Basic Types
**Explanation**: Fundamental data types like integers, floating-point numbers, characters, and booleans store basic values.  
**Real-World Scenario**: Used in a banking app to store account balances (int), interest rates (float), or transaction status (bool).  
**Snippet**:  
```cpp
int x = 10; float y = 3.14;
```
**Example**: [basic_types.cpp](../examples/C++98/basic_types.cpp)

## Enumerations (Unscoped Enums)
**Explanation**: Named integer constants grouped under a type, providing meaningful names for sets of related values.
**Real-World Scenario**: Represent directions (North, South, East, West) in a navigation system.
**Snippet**:
```cpp
enum Color { Red, Green, Blue }; Color c = Green;
```
**Example**: [enumerations.cpp](../examples/C++98/enumerations.cpp)

## Unions
**Explanation**: A type where all members share the same memory location, holding only one member's value at a time.
**Real-World Scenario**: Store either an integer or a float in a memory-constrained embedded sensor reading.
**Snippet**:
```cpp
union Data { int i; float f; }; Data d; d.i = 42;
```
**Example**: [unions.cpp](../examples/C++98/unions.cpp)

## Bitfields
**Explanation**: Struct members with exact bit widths, enabling compact storage of flags and small values.
**Real-World Scenario**: Pack hardware register flags into a single byte in a device driver.
**Snippet**:
```cpp
struct Flags { unsigned int bold : 1; unsigned int italic : 1; };
```
**Example**: [bitfields.cpp](../examples/C++98/bitfields.cpp)

## sizeof Operator
**Explanation**: Returns the size in bytes of a type or object at compile time.
**Real-World Scenario**: Verify struct sizes match protocol specifications in a network library.
**Snippet**:
```cpp
int size = sizeof(int); // typically 4
```
**Example**: [sizeof_operator.cpp](../examples/C++98/sizeof_operator.cpp)

## Pointers
**Explanation**: Variables that store memory addresses, enabling direct memory access.  
**Real-World Scenario**: In embedded systems, pointers manage hardware registers for device control.  
**Snippet**:  
```cpp
int x = 10; int* ptr = &x;
```
**Example**: [pointers.cpp](../examples/C++98/pointers.cpp)

## References
**Explanation**: Aliases for existing variables, providing another name to access the same data.  
**Real-World Scenario**: Used in a game to refer to a player’s health without copying it.  
**Snippet**:  
```cpp
int x = 10; int& ref = x;
```
**Example**: [references.cpp](../examples/C++98/references.cpp)

## Arrays
**Explanation**: Fixed-size collections of elements of the same type, stored contiguously.  
**Real-World Scenario**: Store student scores in a classroom management system.  
**Snippet**:  
```cpp
int arr[5] = {1, 2, 3, 4, 5};
```
**Example**: [arrays.cpp](../examples/C++98/arrays.cpp)

## Functions
**Explanation**: Reusable code blocks that perform tasks, accepting parameters and returning values.  
**Real-World Scenario**: Calculate total price in an e-commerce checkout function.  
**Snippet**:  
```cpp
int add(int a, int b) { return a + b; }
```
**Example**: [functions.cpp](../examples/C++98/functions.cpp)

## Function Overloading
**Explanation**: Multiple functions with the same name but different parameters.  
**Real-World Scenario**: A graphics library with `draw` functions for different shapes.  
**Snippet**:  
```cpp
void print(int x) {} void print(float x) {}
```
**Example**: [function_overloading.cpp](../examples/C++98/function_overloading.cpp)

## Default Arguments
**Explanation**: Parameter values automatically used when the caller omits them from a function call.
**Real-World Scenario**: A logging function defaults to "INFO" level when severity is not specified.
**Snippet**:
```cpp
void log(const char* msg, int level = 1) {}
```
**Example**: [default_arguments.cpp](../examples/C++98/default_arguments.cpp)

## Inline Functions
**Explanation**: A hint to the compiler to expand the function body at each call site, avoiding function call overhead.
**Real-World Scenario**: A small `square()` function in a math library called millions of times per frame.
**Snippet**:
```cpp
inline int square(int x) { return x * x; }
```
**Example**: [inline_functions.cpp](../examples/C++98/inline_functions.cpp)

## Function Pointers
**Explanation**: Pointers that store the address of a function, enabling dynamic function dispatch and callbacks.
**Real-World Scenario**: Register a callback function for button clicks in a GUI framework.
**Snippet**:
```cpp
void greet() {} void (*fptr)() = &greet; fptr();
```
**Example**: [function_pointers.cpp](../examples/C++98/function_pointers.cpp)

## Pointers to Members
**Explanation**: Pointers that refer to a specific data member or member function of a class.
**Real-World Scenario**: Iterate over different fields of a struct in a serialization library.
**Snippet**:
```cpp
struct S { int x; }; int S::*p = &S::x; S s; s.*p = 42;
```
**Example**: [pointers_to_members.cpp](../examples/C++98/pointers_to_members.cpp)

## Classes
**Explanation**: User-defined types combining data and functions to model entities.  
**Real-World Scenario**: Represent a car in a racing game with speed and accelerate methods.  
**Snippet**:  
```cpp
class Car { public: int speed; void drive() {}; };
```
**Example**: [classes.cpp](../examples/C++98/classes.cpp)

## Objects
**Explanation**: Instances of classes, representing specific entities.  
**Real-World Scenario**: Create multiple player objects in a multiplayer game.  
**Snippet**:  
```cpp
Car myCar; myCar.speed = 100;
```
**Example**: [objects.cpp](../examples/C++98/objects.cpp)

## Constructors
**Explanation**: Special functions called during object creation to initialize data.  
**Real-World Scenario**: Initialize a bank account with a starting balance.  
**Snippet**:  
```cpp
class Account { public: Account(int bal) {} };
```
**Example**: [constructors.cpp](../examples/C++98/constructors.cpp)

## Copy Constructor
**Explanation**: A special constructor that creates a new object as a copy of an existing object of the same type.
**Real-World Scenario**: Duplicate a game save state so the player can experiment without losing progress.
**Snippet**:
```cpp
class Widget { public: Widget(const Widget& other) {} };
```
**Example**: [copy_constructor.cpp](../examples/C++98/copy_constructor.cpp)

## Destructors
**Explanation**: Special functions called when an object is destroyed to clean up resources.  
**Real-World Scenario**: Close a file handle when a file object is deleted.  
**Snippet**:  
```cpp
class File { public: ~File() {} };
```
**Example**: [destructors.cpp](../examples/C++98/destructors.cpp)

## Copy Assignment Operator
**Explanation**: An overloaded `operator=` that assigns one object's state to another existing object of the same type.
**Real-World Scenario**: Reassign a configuration object when settings change at runtime.
**Snippet**:
```cpp
class Config { public: Config& operator=(const Config& other) { return *this; } };
```
**Example**: [copy_assignment.cpp](../examples/C++98/copy_assignment.cpp)

## Conversion Functions
**Explanation**: Member functions that define implicit or explicit conversions from a class type to another type.
**Real-World Scenario**: A `Fraction` class that converts to `double` for use in floating-point calculations.
**Snippet**:
```cpp
class Fraction { public: operator double() const { return 0.5; } };
```
**Example**: [conversion_functions.cpp](../examples/C++98/conversion_functions.cpp)

## Inheritance
### Single Inheritance
**Explanation**: A class inherits properties from one base class.  
**Real-World Scenario**: A `SportsCar` class inherits from a `Car` class in a vehicle simulation.  
**Snippet**:  
```cpp
class Car {}; class SportsCar : public Car {};
```
**Example**: [single_inheritance.cpp](../examples/C++98/single_inheritance.cpp)

### Multiple Inheritance
**Explanation**: A class inherits from multiple base classes.  
**Real-World Scenario**: A `FlyingCar` inherits from `Car` and `Airplane` in a futuristic game.  
**Snippet**:  
```cpp
class Car {}; class Airplane {}; class FlyingCar : public Car, public Airplane {};
```
**Example**: [multiple_inheritance.cpp](../examples/C++98/multiple_inheritance.cpp)

### Virtual Inheritance
**Explanation**: Prevents duplicate base class instances in multiple inheritance using `virtual`.  
**Real-World Scenario**: Avoid duplicating a `Vehicle` base in a complex hierarchy.  
**Snippet**:  
```cpp
class Vehicle {}; class Car : virtual public Vehicle {};
```
**Example**: [virtual_inheritance.cpp](../examples/C++98/virtual_inheritance.cpp)

## Polymorphism
**Explanation**: Treats objects of different types as a common base type.  
**Real-World Scenario**: Process different shapes uniformly in a drawing app.  
**Snippet**:  
```cpp
class Shape { virtual void draw() {} };
```
**Example**: [polymorphism.cpp](../examples/C++98/polymorphism.cpp)

## Virtual Functions
**Explanation**: Base class functions overridden by derived classes for dynamic dispatch.  
**Real-World Scenario**: Render different enemy types with a common `attack` method in a game.  
**Snippet**:  
```cpp
class Enemy { virtual void attack() {} };
```
**Example**: [virtual_functions.cpp](../examples/C++98/virtual_functions.cpp)

## Pure Virtual Functions
**Explanation**: Virtual functions declared with `= 0`, making a class abstract.  
**Real-World Scenario**: Define a `Shape` base class requiring all shapes to implement `draw`.  
**Snippet**:  
```cpp
class Shape { virtual void draw() = 0; };
```
**Example**: [pure_virtual_functions.cpp](../examples/C++98/pure_virtual_functions.cpp)

## Abstract Classes
**Explanation**: Classes with pure virtual functions that cannot be instantiated.  
**Real-World Scenario**: A `Vehicle` base class ensuring all vehicles define `move`.  
**Snippet**:  
```cpp
class Vehicle { virtual void move() = 0; };
```
**Example**: [abstract_classes.cpp](../examples/C++98/abstract_classes.cpp)

## Encapsulation
**Explanation**: Hides data using access specifiers to control access.  
**Real-World Scenario**: Protect a bank account’s balance from direct modification.  
**Snippet**:  
```cpp
class Account { private: int balance; public: int getBalance() {} };
```
**Example**: [encapsulation.cpp](../examples/C++98/encapsulation.cpp)

## Access Specifiers
**Explanation**: `public`, `private`, and `protected` control member visibility.  
**Real-World Scenario**: Restrict access to a game character’s internal state.  
**Snippet**:  
```cpp
class Player { private: int health; public: void move() {} };
```
**Example**: [access_specifiers.cpp](../examples/C++98/access_specifiers.cpp)

## Friend Functions
**Explanation**: Non-member functions granted access to a class’s private members.  
**Real-World Scenario**: Allow a logging function to access private data in a debug system.  
**Snippet**:  
```cpp
class Data { friend void log(Data&); };
```
**Example**: [friend_functions.cpp](../examples/C++98/friend_functions.cpp)

## Friend Classes
**Explanation**: A class granted access to another class’s private members.  
**Real-World Scenario**: A renderer class accessing private data of a game object.  
**Snippet**:  
```cpp
class GameObject { friend class Renderer; };
```
**Example**: [friend_classes.cpp](../examples/C++98/friend_classes.cpp)

## Nested Classes
**Explanation**: A class defined inside the scope of another class, typically used as an implementation detail.
**Real-World Scenario**: A `LinkedList` class containing a private `Node` class that only it needs.
**Snippet**:
```cpp
class List { class Node { int data; Node* next; }; };
```
**Example**: [nested_classes.cpp](../examples/C++98/nested_classes.cpp)

## Local Classes
**Explanation**: A class defined inside a function body, scoped to that function only.
**Real-World Scenario**: Define a temporary comparator class inside a sorting function.
**Snippet**:
```cpp
void process() { class Helper { public: void run() {} }; Helper h; h.run(); }
```
**Example**: [local_classes.cpp](../examples/C++98/local_classes.cpp)

## Operator Overloading
**Explanation**: Redefines operators (e.g., +, ==) for user-defined types.  
**Real-World Scenario**: Add two `Vector2D` objects in a physics engine.  
**Snippet**:  
```cpp
class Vector2D { Vector2D operator+(Vector2D& other) {} };
```
**Example**: [operator_overloading.cpp](../examples/C++98/operator_overloading.cpp)

## Templates
### Function Templates
**Explanation**: Functions that work with any data type via a template parameter.  
**Real-World Scenario**: A generic `max` function for a leaderboard.  
**Snippet**:  
```cpp
template<typename T> T max(T a, T b) { return a > b ? a : b; }
```
**Example**: [function_templates.cpp](../examples/C++98/function_templates.cpp)

### Class Templates
**Explanation**: Classes that work with any data type via a template parameter.  
**Real-World Scenario**: A generic `Stack` class for an inventory system.  
**Snippet**:  
```cpp
template<typename T> class Stack { void push(T item) {} };
```
**Example**: [class_templates.cpp](../examples/C++98/class_templates.cpp)

## Exception Handling
**Explanation**: Handles errors using `try`, `catch`, and `throw`.  
**Real-World Scenario**: Handle file not found errors in a data processing app.  
**Snippet**:  
```cpp
try { throw "Error"; } catch(const char* msg) {}
```
**Example**: [exception_handling.cpp](../examples/C++98/exception_handling.cpp)

## Namespaces
**Explanation**: Groups related code to avoid name conflicts.  
**Real-World Scenario**: Organize utility functions in a library under `Utils`.  
**Snippet**:  
```cpp
namespace Utils { void func() {} }
```
**Example**: [namespaces.cpp](../examples/C++98/namespaces.cpp)

## Scope Resolution Operator (::)
**Explanation**: Accesses members of a namespace, class, or enum, and resolves ambiguity in nested scopes.
**Real-World Scenario**: Call a specific base class method in a diamond inheritance hierarchy.
**Snippet**:
```cpp
namespace Math { int add(int a, int b) { return a + b; } }
int result = Math::add(1, 2);
```
**Example**: [scope_resolution.cpp](../examples/C++98/scope_resolution.cpp)

## Dynamic Memory Management
**Explanation**: Allocates and deallocates memory at runtime using `new` and `delete`.  
**Real-World Scenario**: Allocate memory for a dynamic list of user inputs.  
**Snippet**:  
```cpp
int* ptr = new int; delete ptr;
```
**Example**: [dynamic_memory.cpp](../examples/C++98/dynamic_memory.cpp)

## Type Casting
**Explanation**: Converts between types using `static_cast`, `dynamic_cast`, etc.  
**Real-World Scenario**: Convert a base class pointer to a derived class in a game.  
**Snippet**:  
```cpp
Base* b; Derived* d = dynamic_cast<Derived*>(b);
```
**Example**: [type_casting.cpp](../examples/C++98/type_casting.cpp)

## Run-Time Type Information (RTTI)
**Explanation**: Identifies object types at runtime using `typeid` or `dynamic_cast`.  
**Real-World Scenario**: Log object types in a debugging tool.  
**Snippet**:  
```cpp
#include <typeinfo> typeid(obj).name();
```
**Example**: [rtti.cpp](../examples/C++98/rtti.cpp)

## Typeid
**Explanation**: Operator to get type information of an object at runtime.  
**Real-World Scenario**: Display variable types in a diagnostic tool.  
**Snippet**:  
```cpp
#include <typeinfo> cout << typeid(int).name();
```
**Example**: [typeid.cpp](../examples/C++98/typeid.cpp)

## Storage Class Specifiers
**Explanation**: Keywords (`static`, `extern`, `register`) that control the storage duration, linkage, and lifetime of variables.
**Real-World Scenario**: Use `static` to count how many times a function has been called across a program.
**Snippet**:
```cpp
void counter() { static int count = 0; count++; }
```
**Example**: [storage_class.cpp](../examples/C++98/storage_class.cpp)

## Volatile Keyword
**Explanation**: Tells the compiler that a variable may change at any time, preventing optimization of reads/writes.
**Real-World Scenario**: Read a hardware status register that can change between consecutive reads in a driver.
**Snippet**:
```cpp
volatile int* status_reg = (volatile int*)0x40000;
```
**Example**: [volatile.cpp](../examples/C++98/volatile.cpp)

## Mutable Keyword
**Explanation**: Allows a data member to be modified even inside a `const` member function.
**Real-World Scenario**: Cache a computed value inside a `const` getter to avoid redundant calculations.
**Snippet**:
```cpp
class Data { mutable int cache; public: int get() const { cache = 42; return cache; } };
```
**Example**: [mutable.cpp](../examples/C++98/mutable.cpp)

## Conditional (Ternary) Operator
**Explanation**: An inline expression `condition ? true_value : false_value` that returns one of two values based on a condition.
**Real-World Scenario**: Set a discount label to "VIP" or "Standard" based on a customer's loyalty status.
**Snippet**:
```cpp
int x = 10; int abs_x = (x >= 0) ? x : -x;
```
**Example**: [ternary_operator.cpp](../examples/C++98/ternary_operator.cpp)

## Comma Operator
**Explanation**: Evaluates two expressions in sequence, discards the first result, and returns the second.
**Real-World Scenario**: Initialize multiple loop variables in a single `for` statement.
**Snippet**:
```cpp
for (int i = 0, j = 10; i < j; i++, j--) {}
```
**Example**: [comma_operator.cpp](../examples/C++98/comma_operator.cpp)

## Preprocessor Directives
**Explanation**: Compile-time instructions (`#define`, `#include`, `#ifdef`, `#ifndef`, `#pragma`) that control text substitution and conditional compilation.
**Real-World Scenario**: Use include guards to prevent a header file from being included multiple times.
**Snippet**:
```cpp
#ifndef MY_HEADER_H
#define MY_HEADER_H
// declarations
#endif
```
**Example**: [preprocessor.cpp](../examples/C++98/preprocessor.cpp)