// CodeNebula - C++20 Example: std::stop_token, stop_source, stop_callback
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example stop_token.cpp

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void worker_function(std::stop_token stoken, const char* name) {
    int iterations = 0;
    while (!stoken.stop_requested()) {
        ++iterations;
        std::this_thread::sleep_for(20ms);
    }
    std::cout << name << " ran " << iterations << " iterations before stop\n";
}

int main() {
    std::cout << "=== std::stop_source and stop_token ===\n";

    // Create a stop_source (the controller)
    std::stop_source source;

    // Get tokens (read-only views) from the source
    std::stop_token token1 = source.get_token();
    std::stop_token token2 = source.get_token();

    std::cout << "stop_possible: " << token1.stop_possible() << "\n";
    std::cout << "stop_requested: " << token1.stop_requested() << "\n";

    // Launch threads with shared stop tokens
    std::jthread t1(worker_function, token1, "Worker-A");
    std::jthread t2(worker_function, token2, "Worker-B");

    std::this_thread::sleep_for(100ms);

    // One request stops all threads sharing this source
    std::cout << "Requesting stop...\n";
    source.request_stop();
    std::cout << "stop_requested: " << token1.stop_requested() << "\n";

    t1.join();
    t2.join();

    std::cout << "\n=== std::stop_callback ===\n";

    std::stop_source src2;
    std::stop_token tok2 = src2.get_token();

    // Register callbacks that fire when stop is requested
    std::stop_callback cb1(tok2, [] {
        std::cout << "Callback 1: cleanup resources\n";
    });
    std::stop_callback cb2(tok2, [] {
        std::cout << "Callback 2: notify observers\n";
    });

    std::cout << "Requesting stop with callbacks...\n";
    src2.request_stop();  // Both callbacks fire here

    std::cout << "\n=== Empty stop_source (no associated state) ===\n";
    std::stop_source empty{std::nostopstate};
    std::cout << "stop_possible (empty): " << empty.stop_possible() << "\n";
    std::stop_token empty_tok = empty.get_token();
    std::cout << "token stop_possible: " << empty_tok.stop_possible() << "\n";

    std::cout << "\n=== Callback with jthread ===\n";
    {
        std::jthread t([](std::stop_token st) {
            std::stop_callback on_stop(st, [] {
                std::cout << "Thread received stop notification via callback\n";
            });
            while (!st.stop_requested()) {
                std::this_thread::sleep_for(10ms);
            }
        });
        std::this_thread::sleep_for(50ms);
        t.request_stop();
    }
    std::cout << "Done\n";

    return 0;
}
