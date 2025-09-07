# C++98 Core Language and STL Concepts

This document covers all C++98 core language and Standard Template Library (STL) concepts, with simple explanations, real-world scenarios, and short code snippets. Full examples are in the [examples folder](../examples/C++98/).

## Core Language Concepts

### Basic Types
**Explanation**: Fundamental data types like integers, floating-point numbers, characters, and booleans store basic values.  
**Real-World Scenario**: Used in a banking app to store account balances (int), interest rates (float), or transaction status (bool).  
**Snippet**:  
```cpp
int x = 10; float y = 3.14;
```
**Example**: [basic_types.cpp](../examples/C++98/basic_types.cpp)

### Pointers
**Explanation**: Variables that store memory addresses, allowing direct memory access.  
**Real-World Scenario**: In embedded systems, pointers manage hardware registers for controlling devices.  
**Snippet**:  
```cpp
int x = 10; int* ptr = &x;
```
**Example**: [pointers.cpp](../examples/C++98/pointers.cpp)

### References
**Explanation**: Aliases for existing variables, providing an alternative name to access the same data.  
**Real-World Scenario**: Used in a game to refer to a player’s health without copying it.  
**Snippet**:  
```cpp
int x = 10; int& ref = x;
```
**Example**: [references.cpp](../examples/C++98/references.cpp)

### Arrays
**Explanation**: Fixed-size collections of elements of the same type, stored contiguously in memory.  
**Real-World Scenario**: Store a list of student scores in a classroom management system.  
**Snippet**:  
```cpp
int arr[5] = {1, 2, 3, 4, 5};
```
**Example**: [arrays.cpp](../examples/C++98/arrays.cpp)

### Functions
**Explanation**: Blocks of code that perform specific tasks, reusable with parameters and return values.  
**Real-World Scenario**: Calculate the total price in an e-commerce app’s checkout function.  
**Snippet**:  
```cpp
int add(int a, int b) { return a + b; }
```
**Example**: [functions.cpp](../examples/C++98/functions.cpp)

### Function Overloading
**Explanation**: Multiple functions with the same name but different parameters.  
**Real-World Scenario**: A graphics library with `draw` functions for different shapes (circle, rectangle).  
**Snippet**:  
```cpp
void print(int x) {} void print(float x) {}
```
**Example**: [function_overloading.cpp](../examples/C++98/function_overloading.cpp)

### Classes
**Explanation**: User-defined types combining data and functions to model real-world entities.  
**Real-World Scenario**: Represent a car in a racing game with attributes like speed and methods like accelerate.  
**Snippet**:  
```cpp
class Car { public: int speed; void drive() {}; };
```
**Example**: [classes.cpp](../examples/C++98/classes.cpp)

### Objects
**Explanation**: Instances of classes, representing specific entities based on the class blueprint.  
**Real-World Scenario**: Create multiple player objects in a multiplayer game.  
**Snippet**:  
```cpp
Car myCar; myCar.speed = 100;
```
**Example**: [objects.cpp](../examples/C++98/objects.cpp)

### Constructors
**Explanation**: Special member functions called when an object is created to initialize it.  
**Real-World Scenario**: Initialize a bank account with a starting balance in a finance app.  
**Snippet**:  
```cpp
class Account { public: Account(int bal) {} };
```
**Example**: [constructors.cpp](../examples/C++98/constructors.cpp)

### Destructors
**Explanation**: Special functions called when an object is destroyed to clean up resources.  
**Real-World Scenario**: Close a file handle when a file-processing object is deleted.  
**Snippet**:  
```cpp
class File { public: ~File() {} };
```
**Example**: [destructors.cpp](../examples/C++98/destructors.cpp)

### Inheritance
#### Single Inheritance
**Explanation**: A class inherits properties and methods from one base class.  
**Real-World Scenario**: A `SportsCar` class inherits from a `Car` class in a vehicle simulation.  
**Snippet**:  
```cpp
class Car {}; class SportsCar : public Car {};
```
**Example**: [single_inheritance.cpp](../examples/C++98/single_inheritance.cpp)

#### Multiple Inheritance
**Explanation**: A class inherits from multiple base classes.  
**Real-World Scenario**: A `FlyingCar` inherits from both `Car` and `Airplane` in a futuristic game.  
**Snippet**:  
```cpp
class Car {}; class Airplane {}; class FlyingCar : public Car, public Airplane {};
```
**Example**: [multiple_inheritance.cpp](../examples/C++98/multiple_inheritance.cpp)

#### Virtual Inheritance
**Explanation**: Prevents duplicate base class instances in multiple inheritance using `virtual`.  
**Real-World Scenario**: Avoid duplicating a `Vehicle` base class in a complex vehicle hierarchy.  
**Snippet**:  
```cpp
class Vehicle {}; class Car : virtual public Vehicle {};
```
**Example**: [virtual_inheritance.cpp](../examples/C++98/virtual_inheritance.cpp)

### Polymorphism
**Explanation**: Allows objects of different types to be treated as objects of a common base type.  
**Real-World Scenario**: Process different shapes (circle, square) uniformly in a drawing app.  
**Snippet**:  
```cpp
class Shape { virtual void draw() {} };
```
**Example**: [polymorphism.cpp](../examples/C++98/polymorphism.cpp)

### Virtual Functions
**Explanation**: Functions in a base class overridden by derived classes for dynamic dispatch.  
**Real-World Scenario**: Render different enemy types in a game with a common `attack` method.  
**Snippet**:  
```cpp
class Enemy { virtual void attack() {} };
```
**Example**: [virtual_functions.cpp](../examples/C++98/virtual_functions.cpp)

### Pure Virtual Functions
**Explanation**: Virtual functions declared with `= 0`, making a class abstract.  
**Real-World Scenario**: Define a `Shape` base class requiring all shapes to implement `draw`.  
**Snippet**:  
```cpp
class Shape { virtual void draw() = 0; };
```
**Example**: [pure_virtual_functions.cpp](../examples/C++98/pure_virtual_functions.cpp)

### Abstract Classes
**Explanation**: Classes with pure virtual functions that cannot be instantiated.  
**Real-World Scenario**: A `Vehicle` base class ensuring all vehicles define a `move` method.  
**Snippet**:  
```cpp
class Vehicle { virtual void move() = 0; };
```
**Example**: [abstract_classes.cpp](../examples/C++98/abstract_classes.cpp)

### Encapsulation
**Explanation**: Hiding data using access specifiers to control access to class members.  
**Real-World Scenario**: Protect a bank account’s balance from direct modification in a finance app.  
**Snippet**:  
```cpp
class Account { private: int balance; public: int getBalance() {} };
```
**Example**: [encapsulation.cpp](../examples/C++98/encapsulation.cpp)

### Access Specifiers
**Explanation**: `public`, `private`, and `protected` control member visibility.  
**Real-World Scenario**: Restrict access to a game character’s internal state while exposing actions.  
**Snippet**:  
```cpp
class Player { private: int health; public: void move() {} };
```
**Example**: [access_specifiers.cpp](../examples/C++98/access_specifiers.cpp)

### Friend Functions
**Explanation**: Non-member functions granted access to a class’s private members.  
**Real-World Scenario**: Allow a logging function to access private data in a debug system.  
**Snippet**:  
```cpp
class Data { friend void log(Data&); };
```
**Example**: [friend_functions.cpp](../examples/C++98/friend_functions.cpp)

### Friend Classes
**Explanation**: A class granted access to another class’s private members.  
**Real-World Scenario**: A renderer class accessing private data of a game object.  
**Snippet**:  
```cpp
class GameObject { friend class Renderer; };
```
**Example**: [friend_classes.cpp](../examples/C++98/friend_classes.cpp)

### Operator Overloading
**Explanation**: Redefining operators (e.g., +, ==) for user-defined types.  
**Real-World Scenario**: Add two `Vector2D` objects in a physics engine for position updates.  
**Snippet**:  
```cpp
class Vector2D { Vector2D operator+(Vector2D& other) {} };
```
**Example**: [operator_overloading.cpp](../examples/C++98/operator_overloading.cpp)

### Templates
#### Function Templates
**Explanation**: Functions that work with any data type using a template parameter.  
**Real-World Scenario**: A generic `max` function to compare scores in a leaderboard.  
**Snippet**:  
```cpp
template<typename T> T max(T a, T b) { return a > b ? a : b; }
```
**Example**: [function_templates.cpp](../examples/C++98/function_templates.cpp)

#### Class Templates
**Explanation**: Classes that work with any data type using a template parameter.  
**Real-World Scenario**: A generic `Stack` class for items in an inventory system.  
**Snippet**:  
```cpp
template<typename T> class Stack { void push(T item) {} };
```
**Example**: [class_templates.cpp](../examples/C++98/class_templates.cpp)

### Exception Handling
**Explanation**: Mechanism to handle errors using `try`, `catch`, and `throw`.  
**Real-World Scenario**: Handle file not found errors in a data processing application.  
**Snippet**:  
```cpp
try { throw "Error"; } catch(const char* msg) {}
```
**Example**: [exception_handling.cpp](../examples/C++98/exception_handling.cpp)

### Namespaces
**Explanation**: Group related code to avoid name conflicts.  
**Real-World Scenario**: Organize utility functions in a library under a `Utils` namespace.  
**Snippet**:  
```cpp
namespace Utils { void func() {} }
```
**Example**: [namespaces.cpp](../examples/C++98/namespaces.cpp)

### Dynamic Memory Management
**Explanation**: Allocate and deallocate memory at runtime using `new` and `delete`.  
**Real-World Scenario**: Allocate memory for a dynamic list of user inputs in a survey app.  
**Snippet**:  
```cpp
int* ptr = new int; delete ptr;
```
**Example**: [dynamic_memory.cpp](../examples/C++98/dynamic_memory.cpp)

### Type Casting
**Explanation**: Convert between types using `static_cast`, `dynamic_cast`, etc.  
**Real-World Scenario**: Convert a base class pointer to a derived class in a game hierarchy.  
**Snippet**:  
```cpp
Base* b; Derived* d = dynamic_cast<Derived*>(b);
```
**Example**: [type_casting.cpp](../examples/C++98/type_casting.cpp)

### Run-Time Type Information (RTTI)
**Explanation**: Identify object types at runtime using `typeid` or `dynamic_cast`.  
**Real-World Scenario**: Log the type of objects in a debugging tool.  
**Snippet**:  
```cpp
#include <typeinfo> typeid(obj).name();
```
**Example**: [rtti.cpp](../examples/C++98/rtti.cpp)

### Typeid
**Explanation**: Operator to get type information of an object at runtime.  
**Real-World Scenario**: Display the type of a variable in a diagnostic tool.  
**Snippet**:  
```cpp
#include <typeinfo> cout << typeid(int).name();
```
**Example**: [typeid.cpp](../examples/C++98/typeid.cpp)

## STL Concepts

### Containers
#### std::vector
**Explanation**: Dynamic array that grows or shrinks as needed.  
**Real-World Scenario**: Store a list of user messages in a chat application.  
**Snippet**:  
```cpp
#include <vector> std::vector<int> vec = {1, 2, 3};
```
**Example**: [vector.cpp](../examples/C++98/vector.cpp)

#### std::list
**Explanation**: Doubly-linked list for efficient insertions and deletions.  
**Real-World Scenario**: Manage a playlist of songs with frequent reordering.  
**Snippet**:  
```cpp
#include <list> std::list<int> lst = {1, 2, 3};
```
**Example**: [list.cpp](../examples/C++98/list.cpp)

#### std::deque
**Explanation**: Double-ended queue supporting fast insertions at both ends.  
**Real-World Scenario**: Implement a task queue in a job scheduler.  
**Snippet**:  
```cpp
#include <deque> std::deque<int> dq = {1, 2, 3};
```
**Example**: [deque.cpp](../examples/C++98/deque.cpp)

#### std::set
**Explanation**: Sorted collection of unique elements.  
**Real-World Scenario**: Store unique user IDs in a membership system.  
**Snippet**:  
```cpp
#include <set> std::set<int> s = {1, 2, 3};
```
**Example**: [set.cpp](../examples/C++98/set.cpp)

#### std::map
**Explanation**: Sorted key-value pairs with unique keys.  
**Real-World Scenario**: Store student grades by ID in a school database.  
**Snippet**:  
```cpp
#include <map> std::map<int, string> m = {{1, "A"}};
```
**Example**: [map.cpp](../examples/C++98/map.cpp)

#### std::multiset
**Explanation**: Sorted collection allowing duplicate elements.  
**Real-World Scenario**: Track multiple occurrences of event timestamps in a log.  
**Snippet**:  
```cpp
#include <multiset> std::multiset<int> ms = {1, 1, 2};
```
**Example**: [multiset.cpp](../examples/C++98/multiset.cpp)

#### std::multimap
**Explanation**: Sorted key-value pairs allowing duplicate keys.  
**Real-World Scenario**: Store multiple phone numbers per contact in an address book.  
**Snippet**:  
```cpp
#include <map> std::multimap<int, string> mm = {{1, "A"}};
```
**Example**: [multimap.cpp](../examples/C++98/multimap.cpp)

#### std::stack (Container Adaptor)
**Explanation**: LIFO (last-in, first-out) container adaptor.  
**Real-World Scenario**: Implement undo functionality in a text editor.  
**Snippet**:  
```cpp
#include <stack> std::stack<int> stk; stk.push(1);
```
**Example**: [stack.cpp](../examples/C++98/stack.cpp)

#### std::queue (Container Adaptor)
**Explanation**: FIFO (first-in, first-out) container adaptor.  
**Real-World Scenario**: Manage print jobs in a printer queue.  
**Snippet**:  
```cpp
#include <queue> std::queue<int> q; q.push(1);
```
**Example**: [queue.cpp](../examples/C++98/queue.cpp)

#### std::priority_queue (Container Adaptor)
**Explanation**: Queue where the largest element is always at the top.  
**Real-World Scenario**: Schedule tasks by priority in a task manager.  
**Snippet**:  
```cpp
#include <queue> std::priority_queue<int> pq; pq.push(1);
```
**Example**: [priority_queue.cpp](../examples/C++98/priority_queue.cpp)

### Iterators
#### Input Iterator
**Explanation**: Reads elements in a sequence (single-pass, read-only).  
**Real-World Scenario**: Read data from a file stream in a data parser.  
**Snippet**:  
```cpp
std::istream_iterator<int> it(std::cin);
```
**Example**: [input_iterator.cpp](../examples/C++98/input_iterator.cpp)

#### Output Iterator
**Explanation**: Writes elements to a sequence (single-pass, write-only).  
**Real-World Scenario**: Write results to an output stream in a logging system.  
**Snippet**:  
```cpp
std::ostream_iterator<int> it(std::cout, " ");
```
**Example**: [output_iterator.cpp](../examples/C++98/output_iterator.cpp)

#### Forward Iterator
**Explanation**: Reads/writes elements, supports multiple passes in one direction.  
**Real-World Scenario**: Traverse a linked list in a navigation system.  
**Snippet**:  
```cpp
std::list<int>::iterator it = lst.begin();
```
**Example**: [forward_iterator.cpp](../examples/C++98/forward_iterator.cpp)

#### Bidirectional Iterator
**Explanation**: Reads/writes elements, moves forward and backward.  
**Real-World Scenario**: Navigate a playlist forward and backward.  
**Snippet**:  
```cpp
std::list<int>::iterator it = lst.begin(); ++it; --it;
```
**Example**: [bidirectional_iterator.cpp](../examples/C++98/bidirectional_iterator.cpp)

#### Random Access Iterator
**Explanation**: Reads/writes elements with direct access via indexing.  
**Real-World Scenario**: Access elements in an array-based database randomly.  
**Snippet**:  
```cpp
std::vector<int>::iterator it = vec.begin(); it += 2;
```
**Example**: [random_access_iterator.cpp](../examples/C++98/random_access_iterator.cpp)

#### Iterator Traits
**Explanation**: Provides metadata about iterator types (e.g., value_type).  
**Real-World Scenario**: Write generic algorithms that adapt to iterator types.  
**Snippet**:  
```cpp
std::iterator_traits<It>::value_type val;
```
**Example**: [iterator_traits.cpp](../examples/C++98/iterator_traits.cpp)

#### std::iterator
**Explanation**: Base class for defining custom iterators.  
**Real-World Scenario**: Create a custom iterator for a user-defined container.  
**Snippet**:  
```cpp
#include <iterator> class MyIterator : public std::iterator<std::forward_iterator_tag, int> {};
```
**Example**: [iterator.cpp](../examples/C++98/iterator.cpp)

#### std::advance
**Explanation**: Moves an iterator by a specified distance.  
**Real-World Scenario**: Skip elements in a list during data processing.  
**Snippet**:  
```cpp
std::list<int>::iterator it = lst.begin(); std::advance(it, 2);
```
**Example**: [advance.cpp](../examples/C++98/advance.cpp)

#### std::distance
**Explanation**: Calculates the number of elements between two iterators.  
**Real-World Scenario**: Determine the size of a range in a search algorithm.  
**Snippet**:  
```cpp
std::distance(vec.begin(), vec.end());
```
**Example**: [distance.cpp](../examples/C++98/distance.cpp)

#### std::next
**Explanation**: Returns an iterator advanced by a given distance.  
**Real-World Scenario**: Get the next element in a sequence for processing.  
**Snippet**:  
```cpp
std::list<int>::iterator it = std::next(lst.begin());
```
**Example**: [next.cpp](../examples/C++98/next.cpp)

#### std::prev
**Explanation**: Returns an iterator moved backward by a given distance.  
**Real-World Scenario**: Access the previous element in a playlist.  
**Snippet**:  
```cpp
std::list<int>::iterator it = std::prev(lst.end());
```
**Example**: [prev.cpp](../examples/C++98/prev.cpp)

### Iterator Adaptors
#### std::reverse_iterator
**Explanation**: Iterator that traverses a sequence in reverse order.  
**Real-World Scenario**: Print a list of events in reverse chronological order.  
**Snippet**:  
```cpp
std::vector<int>::reverse_iterator rit = vec.rbegin();
```
**Example**: [reverse_iterator.cpp](../examples/C++98/reverse_iterator.cpp)

#### std::back_insert_iterator
**Explanation**: Inserts elements at the end of a container.  
**Real-World Scenario**: Append data to a vector in a data collection system.  
**Snippet**:  
```cpp
std::back_insert_iterator<std::vector<int>> it(vec);
```
**Example**: [back_insert_iterator.cpp](../examples/C++98/back_insert_iterator.cpp)

#### std::front_insert_iterator
**Explanation**: Inserts elements at the beginning of a container.  
**Real-World Scenario**: Add new tasks to the front of a deque in a scheduler.  
**Snippet**:  
```cpp
std::front_insert_iterator<std::deque<int>> it(dq);
```
**Example**: [front_insert_iterator.cpp](../examples/C++98/front_insert_iterator.cpp)

#### std::insert_iterator
**Explanation**: Inserts elements at a specific position in a container.  
**Real-World Scenario**: Insert data into a set during a merge operation.  
**Snippet**:  
```cpp
std::insert_iterator<std::set<int>> it(s);
```
**Example**: [insert_iterator.cpp](../examples/C++98/insert_iterator.cpp)

#### std::istream_iterator
**Explanation**: Reads elements from an input stream as an iterator.  
**Real-World Scenario**: Read numbers from a file in a data parser.  
**Snippet**:  
```cpp
std::istream_iterator<int> it(std::cin);
```
**Example**: [istream_iterator.cpp](../examples/C++98/istream_iterator.cpp)

#### std::ostream_iterator
**Explanation**: Writes elements to an output stream as an iterator.  
**Real-World Scenario**: Write results to a file in a logging system.  
**Snippet**:  
```cpp
std::ostream_iterator<int> it(std::cout, " ");
```
**Example**: [ostream_iterator.cpp](../examples/C++98/ostream_iterator.cpp)

#### std::istreambuf_iterator
**Explanation**: Reads characters directly from an input stream buffer.  
**Real-World Scenario**: Process raw input in a text parser.  
**Snippet**:  
```cpp
std::istreambuf_iterator<char> it(std::cin);
```
**Example**: [istreambuf_iterator.cpp](../examples/C++98/istreambuf_iterator.cpp)

#### std::ostreambuf_iterator
**Explanation**: Writes characters directly to an output stream buffer.  
**Real-World Scenario**: Write raw data to a file in a logging system.  
**Snippet**:  
```cpp
std::ostreambuf_iterator<char> it(std::cout);
```
**Example**: [ostreambuf_iterator.cpp](../examples/C++98/ostreambuf_iterator.cpp)

### Algorithms
#### std::for_each
**Explanation**: Applies a function to each element in a range.  
**Real-World Scenario**: Print all items in a shopping cart.  
**Snippet**:  
```cpp
std::for_each(vec.begin(), vec.end(), print);
```
**Example**: [for_each.cpp](../examples/C++98/for_each.cpp)

#### std::find
**Explanation**: Finds the first occurrence of a value in a range.  
**Real-World Scenario**: Locate a user ID in a database.  
**Snippet**:  
```cpp
std::find(vec.begin(), vec.end(), 5);
```
**Example**: [find.cpp](../examples/C++98/find.cpp)

#### std::find_if
**Explanation**: Finds the first element satisfying a predicate.  
**Real-World Scenario**: Find the first overdue task in a scheduler.  
**Snippet**:  
```cpp
std::find_if(vec.begin(), vec.end(), isEven);
```
**Example**: [find_if.cpp](../examples/C++98/find_if.cpp)

#### std::find_end
**Explanation**: Finds the last occurrence of a subsequence in a range.  
**Real-World Scenario**: Locate the last matching pattern in a text search.  
**Snippet**:  
```cpp
std::find_end(vec.begin(), vec.end(), sub.begin(), sub.end());
```
**Example**: [find_end.cpp](../examples/C++98/find_end.cpp)

#### std::find_first_of
**Explanation**: Finds the first element matching any from another range.  
**Real-World Scenario**: Find a special character in a string parser.  
**Snippet**:  
```cpp
std::find_first_of(vec.begin(), vec.end(), chars.begin(), chars.end());
```
**Example**: [find_first_of.cpp](../examples/C++98/find_first_of.cpp)

#### std::adjacent_find
**Explanation**: Finds the first pair of adjacent equal elements.  
**Real-World Scenario**: Detect consecutive duplicate entries in a log.  
**Snippet**:  
```cpp
std::adjacent_find(vec.begin(), vec.end());
```
**Example**: [adjacent_find.cpp](../examples/C++98/adjacent_find.cpp)

#### std::count
**Explanation**: Counts occurrences of a value in a range.  
**Real-World Scenario**: Count how many times a product appears in a cart.  
**Snippet**:  
```cpp
std::count(vec.begin(), vec.end(), 5);
```
**Example**: [count.cpp](../examples/C++98/count.cpp)

#### std::count_if
**Explanation**: Counts elements satisfying a predicate.  
**Real-World Scenario**: Count tasks marked as completed in a to-do list.  
**Snippet**:  
```cpp
std::count_if(vec.begin(), vec.end(), isPositive);
```
**Example**: [count_if.cpp](../examples/C++98/count_if.cpp)

#### std::mismatch
**Explanation**: Finds the first position where two ranges differ.  
**Real-World Scenario**: Compare two versions of a file for differences.  
**Snippet**:  
```cpp
std::mismatch(vec1.begin(), vec1.end(), vec2.begin());
```
**Example**: [mismatch.cpp](../examples/C++98/mismatch.cpp)

#### std::equal
**Explanation**: Checks if two ranges are equal.  
**Real-World Scenario**: Verify if two user profiles have identical settings.  
**Snippet**:  
```cpp
std::equal(vec1.begin(), vec1.end(), vec2.begin());
```
**Example**: [equal.cpp](../examples/C++98/equal.cpp)

#### std::search
**Explanation**: Finds the first occurrence of a subsequence in a range.  
**Real-World Scenario**: Search for a pattern in a text editor.  
**Snippet**:  
```cpp
std::search(vec.begin(), vec.end(), sub.begin(), sub.end());
```
**Example**: [search.cpp](../examples/C++98/search.cpp)

#### std::search_n
**Explanation**: Finds a sequence of n consecutive equal elements.  
**Real-World Scenario**: Detect repeated characters in a password validator.  
**Snippet**:  
```cpp
std::search_n(vec.begin(), vec.end(), 2, 5);
```
**Example**: [search_n.cpp](../examples/C++98/search_n.cpp)

#### std::copy
**Explanation**: Copies elements from one range to another.  
**Real-World Scenario**: Duplicate a list of items in a backup system.  
**Snippet**:  
```cpp
std::copy(vec.begin(), vec.end(), dest.begin());
```
**Example**: [copy.cpp](../examples/C++98/copy.cpp)

#### std::copy_backward
**Explanation**: Copies elements in reverse order to a destination.  
**Real-World Scenario**: Reverse-copy a log for display in a UI.  
**Snippet**:  
```cpp
std::copy_backward(vec.begin(), vec.end(), dest.end());
```
**Example**: [copy_backward.cpp](../examples/C++98/copy_backward.cpp)

#### std::move (Algorithm)
**Explanation**: Moves elements from one range to another (not move semantics).  
**Real-World Scenario**: Transfer data between buffers in a network app.  
**Snippet**:  
```cpp
std::move(vec.begin(), vec.end(), dest.begin());
```
**Example**: [move_algorithm.cpp](../examples/C++98/move_algorithm.cpp)

#### std::move_backward
**Explanation**: Moves elements in reverse order to a destination.  
**Real-World Scenario**: Reverse-move data in a memory management system.  
**Snippet**:  
```cpp
std::move_backward(vec.begin(), vec.end(), dest.end());
```
**Example**: [move_backward.cpp](../examples/C++98/move_backward.cpp)

#### std::fill
**Explanation**: Fills a range with a specified value.  
**Real-World Scenario**: Initialize an array of scores to zero in a game.  
**Snippet**:  
```cpp
std::fill(vec.begin(), vec.end(), 0);
```
**Example**: [fill.cpp](../examples/C++98/fill.cpp)

#### std::fill_n
**Explanation**: Fills n elements with a specified value.  
**Real-World Scenario**: Set the first n slots of a buffer to a default value.  
**Snippet**:  
```cpp
std::fill_n(vec.begin(), 5, 0);
```
**Example**: [fill_n.cpp](../examples/C++98/fill_n.cpp)

#### std::transform
**Explanation**: Applies a function to a range, storing results in another range.  
**Real-World Scenario**: Convert temperatures from Celsius to Fahrenheit.  
**Snippet**:  
```cpp
std::transform(vec.begin(), vec.end(), dest.begin(), toFahrenheit);
```
**Example**: [transform.cpp](../examples/C++98/transform.cpp)

#### std::generate
**Explanation**: Assigns values from a generator function to a range.  
**Real-World Scenario**: Generate random IDs for users in a registration system.  
**Snippet**:  
```cpp
std::generate(vec.begin(), vec.end(), rand);
```
**Example**: [generate.cpp](../examples/C++98/generate.cpp)

#### std::generate_n
**Explanation**: Assigns values from a generator to n elements.  
**Real-World Scenario**: Generate n unique IDs for a batch process.  
**Snippet**:  
```cpp
std::generate_n(vec.begin(), 5, rand);
```
**Example**: [generate_n.cpp](../examples/C++98/generate_n.cpp)

#### std::remove
**Explanation**: Moves elements not matching a value to the front of a range.  
**Real-World Scenario**: Remove invalid entries from a dataset.  
**Snippet**:  
```cpp
std::remove(vec.begin(), vec.end(), 0);
```
**Example**: [remove.cpp](../examples/C++98/remove.cpp)

#### std::remove_if
**Explanation**: Moves elements not satisfying a predicate to the front.  
**Real-World Scenario**: Remove negative values from a financial report.  
**Snippet**:  
```cpp
std::remove_if(vec.begin(), vec.end(), isNegative);
```
**Example**: [remove_if.cpp](../examples/C++98/remove_if.cpp)

#### std::replace
**Explanation**: Replaces all occurrences of a value in a range.  
**Real-World Scenario**: Replace placeholder text in a template engine.  
**Snippet**:  
```cpp
std::replace(vec.begin(), vec.end(), 0, 1);
```
**Example**: [replace.cpp](../examples/C++98/replace.cpp)

#### std::replace_if
**Explanation**: Replaces elements satisfying a predicate.  
**Real-World Scenario**: Replace all negative scores with zero in a game.  
**Snippet**:  
```cpp
std::replace_if(vec.begin(), vec.end(), isNegative, 0);
```
**Example**: [replace_if.cpp](../examples/C++98/replace_if.cpp)

#### std::swap
**Explanation**: Exchanges values of two variables.  
**Real-World Scenario**: Swap two elements in a sorting algorithm.  
**Snippet**:  
```cpp
std::swap(x, y);
```
**Example**: [swap.cpp](../examples/C++98/swap.cpp)

#### std::swap_ranges
**Explanation**: Exchanges elements between two ranges.  
**Real-World Scenario**: Swap two rows in a matrix editor.  
**Snippet**:  
```cpp
std::swap_ranges(vec1.begin(), vec1.end(), vec2.begin());
```
**Example**: [swap_ranges.cpp](../examples/C++98/swap_ranges.cpp)

#### std::iter_swap
**Explanation**: Swaps elements pointed to by two iterators.  
**Real-World Scenario**: Swap two items in a playlist reorder operation.  
**Snippet**:  
```cpp
std::iter_swap(vec.begin(), vec.begin() + 1);
```
**Example**: [iter_swap.cpp](../examples/C++98/iter_swap.cpp)

#### std::reverse
**Explanation**: Reverses the order of elements in a range.  
**Real-World Scenario**: Reverse a list of events for chronological display.  
**Snippet**:  
```cpp
std::reverse(vec.begin(), vec.end());
```
**Example**: [reverse.cpp](../examples/C++98/reverse.cpp)

#### std::reverse_copy
**Explanation**: Copies a range in reverse order to a destination.  
**Real-World Scenario**: Create a reversed copy of a log for analysis.  
**Snippet**:  
```cpp
std::reverse_copy(vec.begin(), vec.end(), dest.begin());
```
**Example**: [reverse_copy.cpp](../examples/C++98/reverse_copy.cpp)

#### std::rotate
**Explanation**: Rotates elements in a range around a pivot.  
**Real-World Scenario**: Shift elements in a circular buffer.  
**Snippet**:  
```cpp
std::rotate(vec.begin(), vec.begin() + 2, vec.end());
```
**Example**: [rotate.cpp](../examples/C++98/rotate.cpp)

#### std::rotate_copy
**Explanation**: Copies a rotated range to a destination.  
**Real-World Scenario**: Create a rotated version of a schedule for display.  
**Snippet**:  
```cpp
std::rotate_copy(vec.begin(), vec.begin() + 2, vec.end(), dest.begin());
```
**Example**: [rotate_copy.cpp](../examples/C++98/rotate_copy.cpp)

#### std::unique
**Explanation**: Removes consecutive duplicates in a range.  
**Real-World Scenario**: Clean up duplicate entries in a log file.  
**Snippet**:  
```cpp
std::unique(vec.begin(), vec.end());
```
**Example**: [unique.cpp](../examples/C++98/unique.cpp)

#### std::unique_copy
**Explanation**: Copies a range, removing consecutive duplicates.  
**Real-World Scenario**: Create a deduplicated list of user inputs.  
**Snippet**:  
```cpp
std::unique_copy(vec.begin(), vec.end(), dest.begin());
```
**Example**: [unique_copy.cpp](../examples/C++98/unique_copy.cpp)

#### std::partition
**Explanation**: Reorders elements so those satisfying a predicate come first.  
**Real-World Scenario**: Separate completed tasks in a to-do list.  
**Snippet**:  
```cpp
std::partition(vec.begin(), vec.end(), isPositive);
```
**Example**: [partition.cpp](../examples/C++98/partition.cpp)

#### std::stable_partition
**Explanation**: Partitions while preserving relative order.  
**Real-World Scenario**: Group items by category while maintaining order in a catalog.  
**Snippet**:  
```cpp
std::stable_partition(vec.begin(), vec.end(), isPositive);
```
**Example**: [stable_partition.cpp](../examples/C++98/stable_partition.cpp)

#### std::sort
**Explanation**: Sorts elements in a range.  
**Real-World Scenario**: Sort a leaderboard by scores in a game.  
**Snippet**:  
```cpp
std::sort(vec.begin(), vec.end());
```
**Example**: [sort.cpp](../examples/C++98/sort.cpp)

#### std::stable_sort
**Explanation**: Sorts while preserving relative order of equal elements.  
**Real-World Scenario**: Sort products by price, keeping same-priced items in order.  
**Snippet**:  
```cpp
std::stable_sort(vec.begin(), vec.end());
```
**Example**: [stable_sort.cpp](../examples/C++98/stable_sort.cpp)

#### std::partial_sort
**Explanation**: Sorts the first n elements of a range.  
**Real-World Scenario**: Display the top 5 scores in a leaderboard.  
**Snippet**:  
```cpp
std::partial_sort(vec.begin(), vec.begin() + 5, vec.end());
```
**Example**: [partial_sort.cpp](../examples/C++98/partial_sort.cpp)

#### std::partial_sort_copy
**Explanation**: Copies the smallest n elements in sorted order.  
**Real-World Scenario**: Copy top items to a summary report.  
**Snippet**:  
```cpp
std::partial_sort_copy(vec.begin(), vec.end(), dest.begin(), dest.end());
```
**Example**: [partial_sort_copy.cpp](../examples/C++98/partial_sort_copy.cpp)

#### std::nth_element
**Explanation**: Places the nth element in its sorted position.  
**Real-World Scenario**: Find the median value in a dataset.  
**Snippet**:  
```cpp
std::nth_element(vec.begin(), vec.begin() + n, vec.end());
```
**Example**: [nth_element.cpp](../examples/C++98/nth_element.cpp)

#### std::merge
**Explanation**: Merges two sorted ranges into a destination.  
**Real-World Scenario**: Combine two sorted lists of orders in an e-commerce system.  
**Snippet**:  
```cpp
std::merge(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), dest.begin());
```
**Example**: [merge.cpp](../examples/C++98/merge.cpp)

#### std::inplace_merge
**Explanation**: Merges two sorted subranges in place.  
**Real-World Scenario**: Merge sorted halves of a dataset in a database.  
**Snippet**:  
```cpp
std::inplace_merge(vec.begin(), vec.begin() + n, vec.end());
```
**Example**: [inplace_merge.cpp](../examples/C++98/inplace_merge.cpp)

#### std::includes
**Explanation**: Checks if one sorted range is a subset of another.  
**Real-World Scenario**: Verify if a user’s permissions include required ones.  
**Snippet**:  
```cpp
std::includes(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
```
**Example**: [includes.cpp](../examples/C++98/includes.cpp)

#### std::set_union
**Explanation**: Combines two sorted ranges, keeping unique elements.  
**Real-World Scenario**: Merge two lists of unique users from different sources.  
**Snippet**:  
```cpp
std::set_union(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), dest.begin());
```
**Example**: [set_union.cpp](../examples/C++98/set_union.cpp)

#### std::set_intersection
**Explanation**: Finds elements common to two sorted ranges.  
**Real-World Scenario**: Identify common items in two inventories.  
**Snippet**:  
```cpp
std::set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), dest.begin());
```
**Example**: [set_intersection.cpp](../examples/C++98/set_intersection.cpp)

#### std::set_difference
**Explanation**: Finds elements in one sorted range but not another.  
**Real-World Scenario**: List items in one store but not another.  
**Snippet**:  
```cpp
std::set_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), dest.begin());
```
**Example**: [set_difference.cpp](../examples/C++98/set_difference.cpp)

#### std::set_symmetric_difference
**Explanation**: Finds elements in either sorted range but not both.  
**Real-World Scenario**: Identify differences between two user permission sets.  
**Snippet**:  
```cpp
std::set_symmetric_difference(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), dest.begin());
```
**Example**: [set_symmetric_difference.cpp](../examples/C++98/set_symmetric_difference.cpp)

#### std::push_heap
**Explanation**: Adds an element to a heap.  
**Real-World Scenario**: Add a task to a priority queue in a scheduler.  
**Snippet**:  
```cpp
std::push_heap(vec.begin(), vec.end());
```
**Example**: [push_heap.cpp](../examples/C++98/push_heap.cpp)

#### std::pop_heap
**Explanation**: Removes the largest element from a heap.  
**Real-World Scenario**: Retrieve the highest-priority task from a queue.  
**Snippet**:  
```cpp
std::pop_heap(vec.begin(), vec.end());
```
**Example**: [pop_heap.cpp](../examples/C++98/pop_heap.cpp)

#### std::make_heap
**Explanation**: Converts a range into a heap.  
**Real-World Scenario**: Initialize a priority queue for tasks.  
**Snippet**:  
```cpp
std::make_heap(vec.begin(), vec.end());
```
**Example**: [make_heap.cpp](../examples/C++98/make_heap.cpp)

#### std::sort_heap
**Explanation**: Sorts a heap into a sorted range.  
**Real-World Scenario**: Convert a priority queue into a sorted list.  
**Snippet**:  
```cpp
std::sort_heap(vec.begin(), vec.end());
```
**Example**: [sort_heap.cpp](../examples/C++98/sort_heap.cpp)

#### std::min
**Explanation**: Returns the smaller of two values.  
**Real-World Scenario**: Find the cheaper of two products in a store.  
**Snippet**:  
```cpp
std::min(a, b);
```
**Example**: [min.cpp](../examples/C++98/min.cpp)

#### std::max
**Explanation**: Returns the larger of two values.  
**Real-World Scenario**: Find the higher score in a game.  
**Snippet**:  
```cpp
std::max(a, b);
```
**Example**: [max.cpp](../examples/C++98/max.cpp)

#### std::min_element
**Explanation**: Finds the smallest element in a range.  
**Real-World Scenario**: Identify the lowest price in a product list.  
**Snippet**:  
```cpp
std::min_element(vec.begin(), vec.end());
```
**Example**: [min_element.cpp](../examples/C++98/min_element.cpp)

#### std::max_element
**Explanation**: Finds the largest element in a range.  
**Real-World Scenario**: Find the highest score in a leaderboard.  
**Snippet**:  
```cpp
std::max_element(vec.begin(), vec.end());
```
**Example**: [max_element.cpp](../examples/C++98/max_element.cpp)

#### std::lexicographical_compare
**Explanation**: Compares two ranges lexicographically.  
**Real-World Scenario**: Sort strings in a dictionary application.  
**Snippet**:  
```cpp
std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end());
```
**Example**: [lexicographical_compare.cpp](../examples/C++98/lexicographical_compare.cpp)

#### std::next_permutation
**Explanation**: Generates the next permutation of a range.  
**Real-World Scenario**: Generate all possible routes in a navigation system.  
**Snippet**:  
```cpp
std::next_permutation(vec.begin(), vec.end());
```
**Example**: [next_permutation.cpp](../examples/C++98/next_permutation.cpp)

#### std::prev_permutation
**Explanation**: Generates the previous permutation of a range.  
**Real-World Scenario**: Find the previous valid combination in a puzzle solver.  
**Snippet**:  
```cpp
std::prev_permutation(vec.begin(), vec.end());
```
**Example**: [prev_permutation.cpp](../examples/C++98/prev_permutation.cpp)

### Function Objects (Functors)
#### std::unary_function
**Explanation**: Base for unary function objects (deprecated in C++11).  
**Real-World Scenario**: Define a custom function for transforming data.  
**Snippet**:  
```cpp
struct MyFunc : std::unary_function<int, int> { int operator()(int x) { return x; } };
```
**Example**: [unary_function.cpp](../examples/C++98/unary_function.cpp)

#### std::binary_function
**Explanation**: Base for binary function objects (deprecated in C++11).  
**Real-World Scenario**: Define a custom comparison for sorting.  
**Snippet**:  
```cpp
struct MyComp : std::binary_function<int, int, bool> { bool operator()(int x, int y) { return x < y; } };
```
**Example**: [binary_function.cpp](../examples/C++98/binary_function.cpp)

#### std::plus
**Explanation**: Adds two values.  
**Real-World Scenario**: Sum prices in a shopping cart.  
**Snippet**:  
```cpp
std::plus<int> add; add(2, 3);
```
**Example**: [plus.cpp](../examples/C++98/plus.cpp)

#### std::minus
**Explanation**: Subtracts one value from another.  
**Real-World Scenario**: Calculate the difference in scores.  
**Snippet**:  
```cpp
std::minus<int> sub; sub(5, 3);
```
**Example**: [minus.cpp](../examples/C++98/minus.cpp)

#### std::multiplies
**Explanation**: Multiplies two values.  
**Real-World Scenario**: Compute total cost with quantity in a store.  
**Snippet**:  
```cpp
std::multiplies<int> mul; mul(2, 3);
```
**Example**: [multiplies.cpp](../examples/C++98/multiplies.cpp)

#### std::divides
**Explanation**: Divides one value by another.  
**Real-World Scenario**: Calculate average speed in a tracking app.  
**Snippet**:  
```cpp
std::divides<int> div; div(6, 2);
```
**Example**: [divides.cpp](../examples/C++98/divides.cpp)

#### std::modulus
**Explanation**: Computes the remainder of division.  
**Real-World Scenario**: Check if a number is even in a validator.  
**Snippet**:  
```cpp
std::modulus<int> mod; mod(5, 2);
```
**Example**: [modulus.cpp](../examples/C++98/modulus.cpp)

#### std::negate
**Explanation**: Negates a value.  
**Real-World Scenario**: Invert a value in a physics calculation.  
**Snippet**:  
```cpp
std::negate<int> neg; neg(5);
```
**Example**: [negate.cpp](../examples/C++98/negate.cpp)

#### std::equal_to
**Explanation**: Checks if two values are equal.  
**Real-World Scenario**: Compare user inputs in a form validator.  
**Snippet**:  
```cpp
std::equal_to<int> eq; eq(5, 5);
```
**Example**: [equal_to.cpp](../examples/C++98/equal_to.cpp)

#### std::not_equal_to
**Explanation**: Checks if two values are not equal.  
**Real-World Scenario**: Validate unique usernames in a system.  
**Snippet**:  
```cpp
std::not_equal_to<int> neq; neq(5, 3);
```
**Example**: [not_equal_to.cpp](../examples/C++98/not_equal_to.cpp)

#### std::greater
**Explanation**: Checks if one value is greater than another.  
**Real-World Scenario**: Sort scores in descending order.  
**Snippet**:  
```cpp
std::greater<int> gt; gt(5, 3);
```
**Example**: [greater.cpp](../examples/C++98/greater.cpp)

#### std::less
**Explanation**: Checks if one value is less than another.  
**Real-World Scenario**: Sort prices in ascending order.  
**Snippet**:  
```cpp
std::less<int> lt; lt(3, 5);
```
**Example**: [less.cpp](../examples/C++98/less.cpp)

#### std::greater_equal
**Explanation**: Checks if one value is greater than or equal to another.  
**Real-World Scenario**: Filter items with a minimum rating.  
**Snippet**:  
```cpp
std::greater_equal<int> ge; ge(5, 5);
```
**Example**: [greater_equal.cpp](../examples/C++98/greater_equal.cpp)

#### std::less_equal
**Explanation**: Checks if one value is less than or equal to another.  
**Real-World Scenario**: Check if a budget meets a threshold.  
**Snippet**:  
```cpp
std::less_equal<int> le; le(3, 5);
```
**Example**: [less_equal.cpp](../examples/C++98/less_equal.cpp)

#### std::logical_and
**Explanation**: Performs logical AND on two values.  
**Real-World Scenario**: Check if two conditions are true in a validator.  
**Snippet**:  
```cpp
std::logical_and<bool> and_op; and_op(true, true);
```
**Example**: [logical_and.cpp](../examples/C++98/logical_and.cpp)

#### std::logical_or
**Explanation**: Performs logical OR on two values.  
**Real-World Scenario**: Allow access if one of two permissions is granted.  
**Snippet**:  
```cpp
std::logical_or<bool> or_op; or_op(true, false);
```
**Example**: [logical_or.cpp](../examples/C++98/logical_or.cpp)

#### std::logical_not
**Explanation**: Performs logical NOT on a value.  
**Real-World Scenario**: Invert a condition in a control system.  
**Snippet**:  
```cpp
std::logical_not<bool> not_op; not_op(true);
```
**Example**: [logical_not.cpp](../examples/C++98/logical_not.cpp)

#### std::unary_negate
**Explanation**: Negates the result of a unary predicate (deprecated in C++11).  
**Real-World Scenario**: Invert a condition in a filtering algorithm.  
**Snippet**:  
```cpp
std::unary_negate<MyPred> neg(pred);
```
**Example**: [unary_negate.cpp](../examples/C++98/unary_negate.cpp)

#### std::binary_negate
**Explanation**: Negates the result of a binary predicate (deprecated in C++11).  
**Real-World Scenario**: Invert a comparison in a sorting algorithm.  
**Snippet**:  
```cpp
std::binary_negate<MyComp> neg(comp);
```
**Example**: [binary_negate.cpp](../examples/C++98/binary_negate.cpp)

#### std::binder1st
**Explanation**: Binds the first argument of a binary function (deprecated in C++11).  
**Real-World Scenario**: Fix one argument in a comparison function.  
**Snippet**:  
```cpp
std::binder1st<std::plus<int>> add_to_5(std::plus<int>(), 5);
```
**Example**: [binder1st.cpp](../examples/C++98/binder1st.cpp)

#### std::binder2nd
**Explanation**: Binds the second argument of a binary function (deprecated in C++11).  
**Real-World Scenario**: Fix the second operand in a subtraction function.  
**Snippet**:  
```cpp
std::binder2nd<std::minus<int>> sub_from_5(std::minus<int>(), 5);
```
**Example**: [binder2nd.cpp](../examples/C++98/binder2nd.cpp)

#### std::pointer_to_unary_function
**Explanation**: Converts a unary function pointer to a function object (deprecated in C++11).  
**Real-World Scenario**: Adapt a function for use in an algorithm.  
**Snippet**:  
```cpp
std::pointer_to_unary_function<int, int> func_ptr(myFunc);
```
**Example**: [pointer_to_unary_function.cpp](../examples/C++98/pointer_to_unary_function.cpp)

#### std::pointer_to_binary_function
**Explanation**: Converts a binary function pointer to a function object (deprecated in C++11).  
**Real-World Scenario**: Use a function pointer in a sorting algorithm.  
**Snippet**:  
```cpp
std::pointer_to_binary_function<int, int, int> func_ptr(myFunc);
```
**Example**: [pointer_to_binary_function.cpp](../examples/C++98/pointer_to_binary_function.cpp)

#### std::mem_fun
**Explanation**: Creates a function object from a member function (deprecated in C++11).  
**Real-World Scenario**: Call a member function on objects in a container.  
**Snippet**:  
```cpp
std::mem_fun(&MyClass::myMethod);
```
**Example**: [mem_fun.cpp](../examples/C++98/mem_fun.cpp)

#### std::mem_fun_ref
**Explanation**: Creates a function object from a member function for references (deprecated in C++11).  
**Real-World Scenario**: Apply a member function to a container of objects.  
**Snippet**:  
```cpp
std::mem_fun_ref(&MyClass::myMethod);
```
**Example**: [mem_fun_ref.cpp](../examples/C++98/mem_fun_ref.cpp)

### Utilities
#### std::pair
**Explanation**: Stores two values of different types.  
**Real-World Scenario**: Store key-value pairs in a configuration file parser.  
**Snippet**:  
```cpp
std::pair<int, string> p = {1, "value"};
```
**Example**: [pair.cpp](../examples/C++98/pair.cpp)

#### std::string
**Explanation**: Manages sequences of characters.  
**Real-World Scenario**: Store usernames in a login system.  
**Snippet**:  
```cpp
std::string s = "hello";
```
**Example**: [string.cpp](../examples/C++98/string.cpp)

#### std::auto_ptr (Deprecated in C++11)
**Explanation**: Smart pointer for automatic memory management.  
**Real-World Scenario**: Manage dynamic memory in a legacy system.  
**Snippet**:  
```cpp
std::auto_ptr<int> ptr(new int(5));
```
**Example**: [auto_ptr.cpp](../examples/C++98/auto_ptr.cpp)

#### std::rel_ops
**Explanation**: Generates relational operators from `==` and `<`.  
**Real-World Scenario**: Simplify comparisons in a custom class.  
**Snippet**:  
```cpp
using namespace std::rel_ops; bool operator==(MyClass, MyClass);
```
**Example**: [rel_ops.cpp](../examples/C++98/rel_ops.cpp)

### Input/Output
#### std::iostream
**Explanation**: Provides input and output functionality via streams.  
**Real-World Scenario**: Read user input and display results in a console app.  
**Snippet**:  
```cpp
std::cout << "Hello"; std::cin >> x;
```
**Example**: [iostream.cpp](../examples/C++98/iostream.cpp)

#### std::istream
**Explanation**: Handles input operations from streams.  
**Real-World Scenario**: Read data from a file in a data importer.  
**Snippet**:  
```cpp
std::ifstream in("file.txt"); int x; in >> x;
```
**Example**: [istream.cpp](../examples/C++98/istream.cpp)

#### std::ostream
**Explanation**: Handles output operations to streams.  
**Real-World Scenario**: Write logs to a file in a logging system.  
**Snippet**:  
```cpp
std::ofstream out("log.txt"); out << "Log";
```
**Example**: [ostream.cpp](../examples/C++98/ostream.cpp)

#### std::stringstream
**Explanation**: Manages string-based input/output operations.  
**Real-World Scenario**: Parse a string of numbers in a data processor.  
**Snippet**:  
```cpp
std::stringstream ss; ss << "123"; int x; ss >> x;
```
**Example**: [stringstream.cpp](../examples/C++98/stringstream.cpp)