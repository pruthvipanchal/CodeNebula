// CodeNebula - C++11 Example: std::weak_ptr
// Compile: g++ -std=c++11 -Wall -Wextra -o example weak_ptr.cpp
//
// This example demonstrates:
// - std::weak_ptr for non-owning references to shared objects
// - Breaking circular references that cause memory leaks
// - lock() to safely obtain a shared_ptr from weak_ptr
// - expired() to check if the referenced object still exists
// - Observer pattern using weak_ptr

#include <iostream>
#include <memory>
#include <string>
#include <vector>

// ============================================================
// 1. Circular reference problem (solved by weak_ptr)
// ============================================================
class Person {
    std::string name_;
public:
    // Using weak_ptr to break the cycle
    std::weak_ptr<Person> bestFriend;

    Person(const std::string& name) : name_(name) {
        std::cout << "  Person \"" << name_ << "\" created" << std::endl;
    }

    ~Person() {
        std::cout << "  Person \"" << name_ << "\" destroyed" << std::endl;
    }

    void greet() const {
        std::cout << "  " << name_ << " says hello";
        if (auto f = bestFriend.lock()) {
            std::cout << " (best friend exists)";
        } else {
            std::cout << " (best friend gone)";
        }
        std::cout << std::endl;
    }

    const std::string& name() const { return name_; }
};

// ============================================================
// 2. Cache using weak_ptr
// ============================================================
class ResourceCache {
    std::vector<std::weak_ptr<std::string>> cache_;
public:
    void store(std::shared_ptr<std::string> resource) {
        cache_.push_back(resource);  // Only stores weak reference
    }

    void printAvailable() const {
        std::cout << "  Cache contents:" << std::endl;
        int alive = 0, expired = 0;
        for (const auto& weak : cache_) {
            if (auto sp = weak.lock()) {
                std::cout << "    alive: \"" << *sp << "\"" << std::endl;
                ++alive;
            } else {
                ++expired;
            }
        }
        std::cout << "    (" << alive << " alive, " << expired << " expired)" << std::endl;
    }
};

// ============================================================
// 3. Observer pattern with weak_ptr
// ============================================================
class EventSource {
    std::vector<std::weak_ptr<std::string>> observers_;
public:
    void addObserver(std::shared_ptr<std::string> obs) {
        observers_.push_back(obs);
    }

    void notify(const std::string& event) {
        std::cout << "  Notifying observers of: " << event << std::endl;
        for (auto& weak : observers_) {
            if (auto obs = weak.lock()) {
                std::cout << "    -> " << *obs << " received event" << std::endl;
            } else {
                std::cout << "    -> (observer expired)" << std::endl;
            }
        }
    }
};

int main() {
    std::cout << "=== std::weak_ptr ===" << std::endl;

    // Breaking circular references
    std::cout << "\n--- Breaking circular references ---" << std::endl;
    {
        auto alice = std::make_shared<Person>("Alice");
        auto bob = std::make_shared<Person>("Bob");

        alice->bestFriend = bob;
        bob->bestFriend = alice;

        std::cout << "  alice use_count: " << alice.use_count() << std::endl;
        std::cout << "  bob use_count: " << bob.use_count() << std::endl;

        alice->greet();
        bob->greet();
    }
    std::cout << "  Both destroyed (no leak!)" << std::endl;

    // lock() and expired()
    std::cout << "\n--- lock() and expired() ---" << std::endl;
    std::weak_ptr<int> weak;
    {
        auto shared = std::make_shared<int>(42);
        weak = shared;

        std::cout << "  expired: " << weak.expired() << std::endl;
        std::cout << "  use_count: " << weak.use_count() << std::endl;

        if (auto locked = weak.lock()) {
            std::cout << "  Locked value: " << *locked << std::endl;
        }
    }
    std::cout << "  After shared destroyed:" << std::endl;
    std::cout << "  expired: " << weak.expired() << std::endl;
    if (auto locked = weak.lock()) {
        std::cout << "  Value: " << *locked << std::endl;
    } else {
        std::cout << "  lock() returned nullptr (object gone)" << std::endl;
    }

    // Cache pattern
    std::cout << "\n--- Cache pattern ---" << std::endl;
    ResourceCache cache;
    auto res1 = std::make_shared<std::string>("Resource A");
    auto res2 = std::make_shared<std::string>("Resource B");
    auto res3 = std::make_shared<std::string>("Resource C");

    cache.store(res1);
    cache.store(res2);
    cache.store(res3);

    cache.printAvailable();

    res2.reset();  // Release Resource B
    std::cout << "  After releasing Resource B:" << std::endl;
    cache.printAvailable();

    // Observer pattern
    std::cout << "\n--- Observer pattern ---" << std::endl;
    EventSource source;
    auto obs1 = std::make_shared<std::string>("Logger");
    auto obs2 = std::make_shared<std::string>("UI");
    auto obs3 = std::make_shared<std::string>("Metrics");

    source.addObserver(obs1);
    source.addObserver(obs2);
    source.addObserver(obs3);

    source.notify("startup");

    obs2.reset();  // UI observer destroyed
    std::cout << "  After UI observer destroyed:" << std::endl;
    source.notify("shutdown");

    return 0;
}

// Expected output:
// === std::weak_ptr ===
//
// --- Breaking circular references ---
//   Person "Alice" created
//   Person "Bob" created
//   alice use_count: 1
//   bob use_count: 1
//   Alice says hello (best friend exists)
//   Bob says hello (best friend exists)
//   Person "Bob" destroyed
//   Person "Alice" destroyed
//   Both destroyed (no leak!)
//
// --- lock() and expired() ---
//   expired: 0
//   use_count: 1
//   Locked value: 42
//   After shared destroyed:
//   expired: 1
//   lock() returned nullptr (object gone)
//
// --- Cache pattern ---
//   Cache contents:
//     alive: "Resource A"
//     alive: "Resource B"
//     alive: "Resource C"
//     (3 alive, 0 expired)
//   After releasing Resource B:
//   Cache contents:
//     alive: "Resource A"
//     alive: "Resource C"
//     (2 alive, 1 expired)
//
// --- Observer pattern ---
//   Notifying observers of: startup
//     -> Logger received event
//     -> UI received event
//     -> Metrics received event
//   After UI observer destroyed:
//   Notifying observers of: shutdown
//     -> Logger received event
//     -> (observer expired)
//     -> Metrics received event
