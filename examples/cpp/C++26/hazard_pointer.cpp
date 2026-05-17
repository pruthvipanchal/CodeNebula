// CodeNebula - C++26 Example: std::hazard_pointer
// Compile: g++ -std=c++26 -Wall -Wextra -o example hazard_pointer.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <vector>

// C++26 adds std::hazard_pointer for safe memory reclamation in lock-free
// data structures. Readers "protect" pointers; writers defer deletion until
// no hazard pointer references the node.
// API: make_hazard_pointer(), hp.protect(atomic_ptr), hp.reset_protection(),
//      node->retire()

namespace hp_sim {
    struct hazard_registry {
        std::vector<void*> protected_ptrs;
        void protect(void* p) {
            protected_ptrs.push_back(p);
            std::cout << "  [HP] Protected pointer: " << p << "\n";
        }
        void reset() {
            protected_ptrs.clear();
            std::cout << "  [HP] Released all protections\n";
        }
        bool is_protected(void* p) const {
            for (auto* pp : protected_ptrs) if (pp == p) return true;
            return false;
        }
    };

    struct Node {
        int value; Node* next;
        Node(int v, Node* n = nullptr) : value(v), next(n) {}
    };

    void retire(Node* node, const hazard_registry& reg) {
        if (reg.is_protected(node))
            std::cout << "  [Retire] Node " << node->value << " protected, deferring\n";
        else {
            std::cout << "  [Retire] Node " << node->value << " safe to reclaim\n";
            delete node;
        }
    }
}

int main() {
    std::cout << "--- Hazard Pointer Demo ---\n\n";
    auto* node1 = new hp_sim::Node(42);
    auto* node2 = new hp_sim::Node(99, node1);
    hp_sim::hazard_registry hp;

    std::cout << "Reader protects top node:\n";
    hp.protect(node2);

    std::cout << "\nWriter tries to reclaim (still protected):\n";
    hp_sim::retire(node2, hp);

    std::cout << "\nReader releases protection:\n";
    hp.reset();

    std::cout << "\nWriter retries reclamation:\n";
    hp_sim::retire(node2, hp);  // Now safe

    delete node1;
    std::cout << "\nHazard pointer pattern demonstrated.\n";
    return 0;
}

// Expected output:
// --- Hazard Pointer Demo ---
//
// Reader protects top node:
//   [HP] Protected pointer: <address>
//
// Writer tries to reclaim (still protected):
//   [Retire] Node 99 protected, deferring
//
// Reader releases protection:
//   [HP] Released all protections
//
// Writer retries reclamation:
//   [Retire] Node 99 safe to reclaim
//
// Hazard pointer pattern demonstrated.
