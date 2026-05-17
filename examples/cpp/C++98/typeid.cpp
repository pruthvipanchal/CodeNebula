// CodeNebula - C++98 Example: typeid Operator
// Compile: g++ -std=c++98 -Wall -Wextra -o example typeid.cpp

// The typeid operator returns a const reference to std::type_info, providing
// runtime type information. This example focuses on typeid with polymorphic
// types, type_info::name(), type comparison, and the difference between
// static and dynamic type resolution.

#include <iostream>
#include <typeinfo>   // Required for typeid, type_info, bad_typeid
#include <string>

// ------------------------------------------------------------------
// Polymorphic hierarchy (has virtual functions -> dynamic typeid)
// ------------------------------------------------------------------
class Vehicle {
public:
    virtual std::string describe() const { return "Vehicle"; }
    virtual ~Vehicle() {}
};

class Car : public Vehicle {
public:
    std::string describe() const { return "Car"; }
};

class ElectricCar : public Car {
public:
    std::string describe() const { return "ElectricCar"; }
};

class Truck : public Vehicle {
public:
    std::string describe() const { return "Truck"; }
};

// ------------------------------------------------------------------
// Non-polymorphic hierarchy (no virtual functions -> static typeid)
// ------------------------------------------------------------------
class BaseNP {
public:
    int x;
    BaseNP() : x(0) {}
};

class DerivedNP : public BaseNP {
public:
    int y;
    DerivedNP() : y(0) {}
};

// ------------------------------------------------------------------
// Helper: print type info
// ------------------------------------------------------------------
void printTypeInfo(const std::type_info& ti) {
    std::cout << "  name():  " << ti.name() << std::endl;
}

int main() {
    std::cout << "=== C++98 typeid Operator ===" << std::endl;

    // --- 1. typeid with fundamental types ---
    std::cout << "\n--- 1. Fundamental types ---" << std::endl;
    std::cout << "typeid(int).name()     = " << typeid(int).name() << std::endl;
    std::cout << "typeid(double).name()  = " << typeid(double).name() << std::endl;
    std::cout << "typeid(char).name()    = " << typeid(char).name() << std::endl;
    std::cout << "typeid(bool).name()    = " << typeid(bool).name() << std::endl;
    std::cout << "typeid(float*).name()  = " << typeid(float*).name() << std::endl;
    // Note: name() output is implementation-defined (e.g., "i", "d" on GCC)

    // --- 2. typeid comparison ---
    std::cout << "\n--- 2. Type comparison ---" << std::endl;
    int a = 10;
    double b = 3.14;
    int c = 20;

    std::cout << "typeid(a) == typeid(c): "
              << (typeid(a) == typeid(c) ? "true" : "false") << std::endl;
    // Expected: true (both are int)

    std::cout << "typeid(a) == typeid(b): "
              << (typeid(a) == typeid(b) ? "true" : "false") << std::endl;
    // Expected: false (int vs double)

    std::cout << "typeid(a) == typeid(int): "
              << (typeid(a) == typeid(int) ? "true" : "false") << std::endl;
    // Expected: true

    // --- 3. Polymorphic types: dynamic type resolution ---
    std::cout << "\n--- 3. Polymorphic types (dynamic typeid) ---" << std::endl;
    Car car;
    ElectricCar eCar;
    Truck truck;

    // Through base pointer, typeid gives the DYNAMIC (actual) type
    Vehicle* vehicles[3];
    vehicles[0] = &car;
    vehicles[1] = &eCar;
    vehicles[2] = &truck;

    for (int i = 0; i < 3; ++i) {
        std::cout << "vehicles[" << i << "]: "
                  << "typeid.name() = " << typeid(*vehicles[i]).name()
                  << ", describe() = " << vehicles[i]->describe()
                  << std::endl;
    }
    // typeid(*vehicles[i]) resolves to the actual runtime type

    // --- 4. Static type vs dynamic type ---
    std::cout << "\n--- 4. Static vs dynamic type ---" << std::endl;

    Vehicle* vp = &eCar;

    // typeid of the POINTER (static type) vs typeid of the OBJECT (dynamic type)
    std::cout << "typeid(vp).name()  = " << typeid(vp).name()
              << "  (pointer type - static)" << std::endl;
    std::cout << "typeid(*vp).name() = " << typeid(*vp).name()
              << "  (object type - dynamic)" << std::endl;

    // The pointer type is always Vehicle*, regardless of what it points to
    // The dereferenced type reflects the actual object (ElectricCar)

    std::cout << "\ntypeid(*vp) == typeid(ElectricCar): "
              << (typeid(*vp) == typeid(ElectricCar) ? "true" : "false") << std::endl;
    // Expected: true

    std::cout << "typeid(*vp) == typeid(Car): "
              << (typeid(*vp) == typeid(Car) ? "true" : "false") << std::endl;
    // Expected: false (exact type is ElectricCar, not Car)

    std::cout << "typeid(*vp) == typeid(Vehicle): "
              << (typeid(*vp) == typeid(Vehicle) ? "true" : "false") << std::endl;
    // Expected: false

    // --- 5. Non-polymorphic types: static type resolution ---
    std::cout << "\n--- 5. Non-polymorphic types (static typeid) ---" << std::endl;

    DerivedNP derived;
    BaseNP* bp = &derived;

    // Without virtual functions, typeid uses the STATIC (declared) type
    std::cout << "typeid(*bp).name() = " << typeid(*bp).name()
              << "  (STATIC type - BaseNP)" << std::endl;
    std::cout << "typeid(derived).name() = " << typeid(derived).name()
              << "  (known at compile time)" << std::endl;

    std::cout << "typeid(*bp) == typeid(BaseNP): "
              << (typeid(*bp) == typeid(BaseNP) ? "true" : "false") << std::endl;
    // Expected: true (uses static type since no virtual functions)

    std::cout << "typeid(*bp) == typeid(DerivedNP): "
              << (typeid(*bp) == typeid(DerivedNP) ? "true" : "false") << std::endl;
    // Expected: false (static type is BaseNP)

    // --- 6. type_info::before() ---
    std::cout << "\n--- 6. type_info::before() ---" << std::endl;
    const std::type_info& tiCar = typeid(Car);
    const std::type_info& tiTruck = typeid(Truck);

    // before() provides a consistent ordering (implementation-defined)
    std::cout << "Car before Truck: "
              << (tiCar.before(tiTruck) ? "yes" : "no") << std::endl;
    std::cout << "Truck before Car: "
              << (tiTruck.before(tiCar) ? "yes" : "no") << std::endl;
    // One must be true, the other false (total ordering)

    // --- 7. typeid with expressions ---
    std::cout << "\n--- 7. typeid with expressions ---" << std::endl;
    int x = 5;
    double y = 2.5;

    std::cout << "typeid(x + x).name() = " << typeid(x + x).name() << std::endl;
    // Expected: int
    std::cout << "typeid(x + y).name() = " << typeid(x + y).name() << std::endl;
    // Expected: double (int promoted to double)
    std::cout << "typeid(true).name()  = " << typeid(true).name() << std::endl;
    // Expected: bool

    // --- 8. Using typeid for a simple type-based dispatch ---
    std::cout << "\n--- 8. Type-based dispatch ---" << std::endl;
    for (int i = 0; i < 3; ++i) {
        const std::type_info& ti = typeid(*vehicles[i]);

        if (ti == typeid(Car)) {
            std::cout << "Processing a Car..." << std::endl;
        } else if (ti == typeid(ElectricCar)) {
            std::cout << "Processing an ElectricCar (check battery!)..." << std::endl;
        } else if (ti == typeid(Truck)) {
            std::cout << "Processing a Truck (check cargo!)..." << std::endl;
        }
    }

    return 0;
}

/*
Expected Output:
=== C++98 typeid Operator ===

--- 1. Fundamental types ---
typeid(int).name()     = i          (GCC) or "int" (MSVC)
typeid(double).name()  = d          (GCC) or "double" (MSVC)
typeid(char).name()    = c          (GCC) or "char" (MSVC)
typeid(bool).name()    = b          (GCC) or "bool" (MSVC)
typeid(float*).name()  = Pf         (GCC) or "float *" (MSVC)

--- 2. Type comparison ---
typeid(a) == typeid(c): true
typeid(a) == typeid(b): false
typeid(a) == typeid(int): true

--- 3. Polymorphic types (dynamic typeid) ---
vehicles[0]: typeid = Car, describe() = Car
vehicles[1]: typeid = ElectricCar, describe() = ElectricCar
vehicles[2]: typeid = Truck, describe() = Truck

--- 4. Static vs dynamic type ---
typeid(vp)  = Vehicle*  (pointer - static)
typeid(*vp) = ElectricCar  (object - dynamic)
typeid(*vp) == typeid(ElectricCar): true
typeid(*vp) == typeid(Car): false
typeid(*vp) == typeid(Vehicle): false

--- 5. Non-polymorphic types (static typeid) ---
typeid(*bp) = BaseNP  (STATIC type)
typeid(*bp) == typeid(BaseNP): true
typeid(*bp) == typeid(DerivedNP): false

--- 6. type_info::before() ---
(ordering is implementation-defined)

--- 7. typeid with expressions ---
typeid(x + x) = int
typeid(x + y) = double
typeid(true)  = bool

--- 8. Type-based dispatch ---
Processing a Car...
Processing an ElectricCar (check battery!)...
Processing a Truck (check cargo!)...
*/
