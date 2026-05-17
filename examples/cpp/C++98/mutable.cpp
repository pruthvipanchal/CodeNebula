// CodeNebula - C++98 Example: mutable Keyword
// Compile: g++ -std=c++98 -Wall -Wextra -o example mutable.cpp

// The 'mutable' keyword allows a class member to be modified even when
// accessed through a const reference or inside a const member function.
// This is useful for:
//   - Caching/memoization (lazy computation)
//   - Mutexes and synchronization primitives
//   - Debug counters and access tracking
//   - Internal bookkeeping that doesn't affect logical constness

#include <iostream>
#include <string>
#include <cmath>

// ------------------------------------------------------------------
// 1. Caching pattern: expensive computation cached in mutable member
// ------------------------------------------------------------------
class Circle {
private:
    double radius;
    mutable double cachedArea;       // Can be modified in const methods
    mutable bool areaCacheValid;     // Tracks if cache is up to date

public:
    Circle(double r) : radius(r), cachedArea(0.0), areaCacheValid(false) {}

    void setRadius(double r) {
        radius = r;
        areaCacheValid = false;  // Invalidate cache when state changes
    }

    double getRadius() const {
        return radius;
    }

    // This is a const method, but it modifies mutable members
    double getArea() const {
        if (!areaCacheValid) {
            std::cout << "    (computing area...)" << std::endl;
            cachedArea = 3.14159265 * radius * radius;  // OK: mutable
            areaCacheValid = true;                        // OK: mutable
        } else {
            std::cout << "    (returning cached area)" << std::endl;
        }
        return cachedArea;
    }
};

// ------------------------------------------------------------------
// 2. Access counter: track how many times data is read
// ------------------------------------------------------------------
class SecureData {
private:
    std::string data;
    mutable int accessCount;   // Tracks reads without affecting const

public:
    SecureData(const std::string& d) : data(d), accessCount(0) {}

    // const method that modifies the mutable counter
    std::string getData() const {
        ++accessCount;    // OK: mutable member
        return data;
    }

    int getAccessCount() const {
        return accessCount;
    }

    void resetAccessCount() {
        accessCount = 0;
    }
};

// ------------------------------------------------------------------
// 3. Lazy initialization pattern
// ------------------------------------------------------------------
class Config {
private:
    std::string filename;
    mutable std::string cachedContent;
    mutable bool loaded;

public:
    Config(const std::string& fname)
        : filename(fname), cachedContent(""), loaded(false) {}

    // Const method that lazily "loads" data on first access
    const std::string& getContent() const {
        if (!loaded) {
            std::cout << "    (loading config from \"" << filename << "\"...)" << std::endl;
            // Simulate loading from file
            cachedContent = "key1=value1;key2=value2;key3=value3";
            loaded = true;
        }
        return cachedContent;
    }

    // Check if data has been loaded
    bool isLoaded() const {
        return loaded;
    }
};

// ------------------------------------------------------------------
// 4. Statistics tracker in a const-correct container
// ------------------------------------------------------------------
class DataStore {
private:
    int values[10];
    int count;
    mutable int lookupCount;    // How many times find() was called
    mutable int lastFoundIndex; // Last successful search result

public:
    DataStore() : count(0), lookupCount(0), lastFoundIndex(-1) {}

    void add(int value) {
        if (count < 10) {
            values[count++] = value;
        }
    }

    // const method that updates mutable diagnostic members
    int find(int value) const {
        ++lookupCount;  // OK: mutable
        for (int i = 0; i < count; ++i) {
            if (values[i] == value) {
                lastFoundIndex = i;  // OK: mutable
                return i;
            }
        }
        lastFoundIndex = -1;
        return -1;
    }

    int getLookupCount() const { return lookupCount; }
    int getLastFoundIndex() const { return lastFoundIndex; }

    void print() const {
        std::cout << "  DataStore [";
        for (int i = 0; i < count; ++i) {
            std::cout << values[i];
            if (i < count - 1) std::cout << ", ";
        }
        std::cout << "]" << std::endl;
    }
};

// ------------------------------------------------------------------
// 5. Demonstrating mutable with const objects and references
// ------------------------------------------------------------------
void useConstCircle(const Circle& c) {
    // Even though 'c' is const, getArea() can update the mutable cache
    std::cout << "  Area = " << c.getArea() << std::endl;
    std::cout << "  Area = " << c.getArea() << std::endl;  // Should use cache
}

void useConstSecureData(const SecureData& sd) {
    // Reading data through a const reference still increments the counter
    std::cout << "  Data: " << sd.getData() << std::endl;
    std::cout << "  Data: " << sd.getData() << std::endl;
    std::cout << "  Access count: " << sd.getAccessCount() << std::endl;
}

int main() {
    std::cout << "=== C++98 mutable Keyword ===" << std::endl;

    // --- 1. Caching pattern ---
    std::cout << "\n--- 1. Caching (Circle::getArea) ---" << std::endl;
    Circle circle(5.0);

    std::cout << "First call (computes):" << std::endl;
    std::cout << "  Area = " << circle.getArea() << std::endl;
    // Expected: (computing area...) then 78.5398

    std::cout << "Second call (cached):" << std::endl;
    std::cout << "  Area = " << circle.getArea() << std::endl;
    // Expected: (returning cached area) then 78.5398

    std::cout << "After setRadius(10):" << std::endl;
    circle.setRadius(10.0);
    std::cout << "  Area = " << circle.getArea() << std::endl;
    // Expected: (computing area...) then 314.159 (cache invalidated)

    std::cout << "Again (cached):" << std::endl;
    std::cout << "  Area = " << circle.getArea() << std::endl;
    // Expected: (returning cached area)

    // --- 2. With const reference ---
    std::cout << "\n--- 2. Mutable through const reference ---" << std::endl;
    const Circle constCircle(3.0);
    std::cout << "Calling getArea() on a const Circle:" << std::endl;
    useConstCircle(constCircle);
    // First call computes, second call returns cached

    // --- 3. Access counter ---
    std::cout << "\n--- 3. Access counter (SecureData) ---" << std::endl;
    SecureData secret("TOP_SECRET_DATA");

    std::cout << "Via const reference:" << std::endl;
    useConstSecureData(secret);
    // Expected: Access count: 2

    std::cout << "  One more read: " << secret.getData() << std::endl;
    std::cout << "  Total access count: " << secret.getAccessCount() << std::endl;
    // Expected: 3

    secret.resetAccessCount();
    std::cout << "  After reset: " << secret.getAccessCount() << std::endl;
    // Expected: 0

    // --- 4. Lazy initialization ---
    std::cout << "\n--- 4. Lazy initialization (Config) ---" << std::endl;
    const Config cfg("settings.ini");

    std::cout << "  Loaded? " << (cfg.isLoaded() ? "yes" : "no") << std::endl;
    // Expected: no

    std::cout << "  Content: " << cfg.getContent() << std::endl;
    // Expected: (loading...) then the content

    std::cout << "  Loaded? " << (cfg.isLoaded() ? "yes" : "no") << std::endl;
    // Expected: yes

    std::cout << "  Content: " << cfg.getContent() << std::endl;
    // Expected: returns immediately (no loading message)

    // --- 5. Diagnostic counters ---
    std::cout << "\n--- 5. Diagnostic counters (DataStore) ---" << std::endl;
    DataStore store;
    store.add(10);
    store.add(20);
    store.add(30);
    store.add(40);
    store.add(50);
    store.print();

    // Use a const reference
    const DataStore& cstore = store;
    int idx = cstore.find(30);
    std::cout << "  find(30): index=" << idx << std::endl;
    // Expected: 2

    idx = cstore.find(99);
    std::cout << "  find(99): index=" << idx << std::endl;
    // Expected: -1

    idx = cstore.find(50);
    std::cout << "  find(50): index=" << idx << std::endl;
    // Expected: 4

    std::cout << "  Total lookups: " << cstore.getLookupCount() << std::endl;
    // Expected: 3
    std::cout << "  Last found index: " << cstore.getLastFoundIndex() << std::endl;
    // Expected: 4

    // --- Summary ---
    std::cout << "\n--- Summary ---" << std::endl;
    std::cout << "mutable allows modifying a member inside a const method." << std::endl;
    std::cout << "Use it for: caching, access counters, lazy init, mutexes." << std::endl;
    std::cout << "It preserves 'logical constness' while allowing" << std::endl;
    std::cout << "internal state changes that don't affect the object's" << std::endl;
    std::cout << "observable behavior." << std::endl;

    return 0;
}

/*
Expected Output:
=== C++98 mutable Keyword ===

--- 1. Caching (Circle::getArea) ---
First call (computes):
    (computing area...)
  Area = 78.5398
Second call (cached):
    (returning cached area)
  Area = 78.5398
After setRadius(10):
    (computing area...)
  Area = 314.159
Again (cached):
    (returning cached area)
  Area = 314.159

--- 2. Mutable through const reference ---
Calling getArea() on a const Circle:
    (computing area...)
  Area = 28.2743
    (returning cached area)
  Area = 28.2743

--- 3. Access counter (SecureData) ---
Via const reference:
  Data: TOP_SECRET_DATA
  Data: TOP_SECRET_DATA
  Access count: 2
  One more read: TOP_SECRET_DATA
  Total access count: 3
  After reset: 0

--- 4. Lazy initialization (Config) ---
  Loaded? no
    (loading config from "settings.ini"...)
  Content: key1=value1;key2=value2;key3=value3
  Loaded? yes
  Content: key1=value1;key2=value2;key3=value3

--- 5. Diagnostic counters (DataStore) ---
  DataStore [10, 20, 30, 40, 50]
  find(30): index=2
  find(99): index=-1
  find(50): index=4
  Total lookups: 3
  Last found index: 4

--- Summary ---
mutable allows modifying a member inside a const method.
Use it for: caching, access counters, lazy init, mutexes.
It preserves 'logical constness' while allowing
internal state changes that don't affect the object's
observable behavior.
*/
