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

## Destructors
**Explanation**: Special functions called when an object is destroyed to clean up resources.  
**Real-World Scenario**: Close a file handle when a file object is deleted.  
**Snippet**:  
```cpp
class File { public: ~File() {} };
```
**Example**: [destructors.cpp](../examples/C++98/destructors.cpp)

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