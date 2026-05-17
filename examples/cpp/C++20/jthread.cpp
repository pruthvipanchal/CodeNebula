// CodeNebula - C++20 Example: std::jthread (Auto-joining Thread)
// Compile: g++ -std=c++20 -Wall -Wextra -pthread -o example jthread.cpp

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main() {
    std::cout << "=== std::jthread - auto-joining thread ===\n";

    // jthread automatically joins in its destructor (no manual join needed)
    {
        std::jthread t([] {
            std::cout << "Worker: running in jthread\n";
            std::this_thread::sleep_for(50ms);
            std::cout << "Worker: done\n";
        });
        std::cout << "Main: jthread created (id: " << t.get_id() << ")\n";
        // No need to call t.join() - happens automatically at scope exit
    }
    std::cout << "Main: jthread automatically joined\n";

    std::cout << "\n=== jthread with stop_token ===\n";

    // jthread can pass a stop_token as first parameter to the callable
    {
        std::jthread worker([](std::stop_token stoken) {
            int count = 0;
            while (!stoken.stop_requested()) {
                std::cout << "Worker: iteration " << ++count << "\n";
                std::this_thread::sleep_for(30ms);
            }
            std::cout << "Worker: stop requested, exiting\n";
        });

        std::this_thread::sleep_for(100ms);
        std::cout << "Main: requesting stop...\n";
        worker.request_stop();
        // Destructor joins automatically
    }
    std::cout << "Main: worker finished\n";

    std::cout << "\n=== stop_source from jthread ===\n";

    {
        std::jthread t([](std::stop_token st) {
            while (!st.stop_requested()) {
                std::this_thread::sleep_for(20ms);
            }
            std::cout << "Thread stopped via stop_source\n";
        });

        // Get the stop_source associated with this jthread
        std::stop_source ss = t.get_stop_source();
        std::cout << "Stop possible: " << ss.stop_possible() << "\n";
        std::cout << "Stop requested: " << ss.stop_requested() << "\n";

        ss.request_stop();
        std::cout << "Stop requested now: " << ss.stop_requested() << "\n";
    }

    std::cout << "\n=== Multiple jthreads (RAII cleanup) ===\n";
    {
        std::jthread t1([] { std::cout << "Thread 1 done\n"; });
        std::jthread t2([] { std::cout << "Thread 2 done\n"; });
        std::jthread t3([] { std::cout << "Thread 3 done\n"; });
        // All three automatically joined when scope exits
        // Even if an exception were thrown!
    }
    std::cout << "All threads joined safely\n";

    return 0;
}
