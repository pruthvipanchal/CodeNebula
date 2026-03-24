// CodeNebula - C++26 Example: scheduler, sender, receiver Concepts
// Compile: g++ -std=c++26 -Wall -Wextra -o example execution_concepts.cpp
// Note: Requires C++26 compiler support

#include <iostream>
#include <concepts>
#include <exception>

// C++26 std::execution defines concepts for the async framework:
//   scheduler  - produces senders via .schedule()
//   sender     - describes async work, connectable to a receiver
//   receiver   - handles completion: set_value, set_error, set_stopped
//   operation_state - returned by connect(), started via start()

namespace exec_sim {
    template <typename R>
    concept receiver = requires(R r) {
        { r.set_value() } -> std::same_as<void>;
        { r.set_error(std::declval<std::exception_ptr>()) } -> std::same_as<void>;
        { r.set_stopped() } -> std::same_as<void>;
    };

    template <typename S>
    concept sender = requires(S s) {
        { s.tag } -> std::convertible_to<int>;
    };

    template <typename Sch>
    concept scheduler = requires(Sch sch) { { sch.schedule() }; };

    struct print_receiver {
        void set_value() { std::cout << "  Receiver: completed\n"; }
        void set_error(std::exception_ptr) { std::cout << "  Receiver: error\n"; }
        void set_stopped() { std::cout << "  Receiver: stopped\n"; }
    };

    struct simple_sender {
        int tag = 0;
        template <receiver R>
        void connect_and_start(R recv) { recv.set_value(); }
    };

    struct inline_scheduler {
        simple_sender schedule() {
            std::cout << "  Scheduler: work scheduled\n";
            return simple_sender{};
        }
    };

    static_assert(receiver<print_receiver>);
    static_assert(sender<simple_sender>);
    static_assert(scheduler<inline_scheduler>);
}

int main() {
    std::cout << "--- Execution Concepts Demo ---\n";
    exec_sim::inline_scheduler sched;
    auto sndr = sched.schedule();
    exec_sim::print_receiver recv;
    sndr.connect_and_start(recv);

    std::cout << "receiver satisfied:  " << exec_sim::receiver<exec_sim::print_receiver> << "\n";
    std::cout << "sender satisfied:    " << exec_sim::sender<exec_sim::simple_sender> << "\n";
    std::cout << "scheduler satisfied: " << exec_sim::scheduler<exec_sim::inline_scheduler> << "\n";
    return 0;
}

// Expected output:
// --- Execution Concepts Demo ---
//   Scheduler: work scheduled
//   Receiver: completed
// receiver satisfied:  1
// sender satisfied:    1
// scheduler satisfied: 1
