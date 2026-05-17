// CodeNebula - C++26 Example: std::rcu Reader-Copy-Update Pattern
// Compile: g++ -std=c++26 -Wall -Wextra -o example rcu.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <string>
#include <atomic>

// C++26 adds RCU (Read-Copy-Update) for scalable concurrent reads.
// Readers access data without locking; writers create copies and defer reclamation.
// Key API: std::rcu_reader (RAII guard), std::rcu_synchronize(), ptr->retire()

namespace rcu_sim {
    struct Config {
        std::string name; int version;
        Config(std::string n, int v) : name(std::move(n)), version(v) {}
    };

    struct rcu_reader {
        rcu_reader() { std::cout << "  [RCU] Reader entered critical section\n"; }
        ~rcu_reader() { std::cout << "  [RCU] Reader exited critical section\n"; }
    };

    void rcu_synchronize() {
        std::cout << "  [RCU] Synchronize: all readers done, safe to reclaim\n";
    }

    std::atomic<Config*> shared_config{nullptr};

    void reader() {
        rcu_reader lock;
        Config* cfg = shared_config.load(std::memory_order_acquire);
        if (cfg)
            std::cout << "  Read: name=\"" << cfg->name << "\", v=" << cfg->version << "\n";
    }

    void writer(const std::string& new_name, int new_version) {
        Config* new_cfg = new Config(new_name, new_version);
        Config* old = shared_config.exchange(new_cfg, std::memory_order_release);
        std::cout << "  Writer: published version " << new_version << "\n";
        if (old) { rcu_synchronize(); delete old; }
    }
}

int main() {
    std::cout << "--- RCU (Read-Copy-Update) Demo ---\n\n";
    rcu_sim::writer("AppConfig", 1);
    std::cout << "\n";
    rcu_sim::reader();
    std::cout << "\n";
    rcu_sim::writer("AppConfig-v2", 2);
    std::cout << "\n";
    rcu_sim::reader();
    delete rcu_sim::shared_config.load();
    std::cout << "\nRCU pattern demonstrated.\n";
    return 0;
}

// Expected output:
// --- RCU (Read-Copy-Update) Demo ---
//
//   Writer: published version 1
//
//   [RCU] Reader entered critical section
//   Read: name="AppConfig", v=1
//   [RCU] Reader exited critical section
//
//   Writer: published version 2
//   [RCU] Synchronize: all readers done, safe to reclaim
//
//   [RCU] Reader entered critical section
//   Read: name="AppConfig-v2", v=2
//   [RCU] Reader exited critical section
//
// RCU pattern demonstrated.
