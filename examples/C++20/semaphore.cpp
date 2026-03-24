// CodeNebula - C++20 Example: std::counting_semaphore and binary_semaphore
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example semaphore.cpp

#include <iostream>
#include <semaphore>
#include <thread>
#include <vector>

int main() {
    std::cout << "=== std::counting_semaphore ===\n";
    std::cout << "(Limits concurrent access to a resource)\n\n";

    // Allow up to 3 concurrent workers (like a connection pool)
    std::counting_semaphore<3> pool(3);

    auto worker = [&pool](int id) {
        pool.acquire();  // Wait if count is 0, then decrement
        std::cout << "Worker " << id << " acquired resource\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        std::cout << "Worker " << id << " releasing resource\n";
        pool.release();  // Increment count, potentially unblocking a waiter
    };

    std::vector<std::jthread> threads;
    for (int i = 0; i < 6; ++i) {
        threads.emplace_back(worker, i);
    }
    for (auto& t : threads) t.join();

    std::cout << "\n=== std::binary_semaphore ===\n";
    std::cout << "(Equivalent to counting_semaphore<1>, like a mutex)\n\n";

    // binary_semaphore for signaling between threads
    std::binary_semaphore signal(0);  // Start with 0 (blocked)

    std::jthread producer([&signal] {
        std::cout << "Producer: preparing data...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        std::cout << "Producer: data ready, signaling consumer\n";
        signal.release();  // Signal the consumer
    });

    std::jthread consumer([&signal] {
        std::cout << "Consumer: waiting for data...\n";
        signal.acquire();  // Block until producer signals
        std::cout << "Consumer: received signal, processing data\n";
    });

    producer.join();
    consumer.join();

    std::cout << "\n=== try_acquire (non-blocking) ===\n";

    std::counting_semaphore<2> limited(2);
    limited.acquire();
    limited.acquire();  // Both slots taken

    if (limited.try_acquire()) {
        std::cout << "Unexpected: acquired when full\n";
    } else {
        std::cout << "try_acquire returned false (as expected, no slots)\n";
    }

    limited.release();  // Free one slot
    if (limited.try_acquire()) {
        std::cout << "try_acquire succeeded after release\n";
        limited.release();
    }

    std::cout << "\n=== Ping-pong with binary_semaphores ===\n";

    std::binary_semaphore ping(1);  // Start with ping
    std::binary_semaphore pong(0);

    std::jthread pinger([&] {
        for (int i = 0; i < 3; ++i) {
            ping.acquire();
            std::cout << "Ping! ";
            pong.release();
        }
    });
    std::jthread ponger([&] {
        for (int i = 0; i < 3; ++i) {
            pong.acquire();
            std::cout << "Pong! ";
            ping.release();
        }
    });

    pinger.join();
    ponger.join();
    std::cout << "\nDone\n";

    return 0;
}
