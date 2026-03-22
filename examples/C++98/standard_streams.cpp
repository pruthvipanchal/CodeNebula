// CodeNebula - C++98 Example: Standard Streams (cin/cout/cerr/clog)
// Compile: g++ -std=c++98 -Wall -Wextra -o example standard_streams.cpp

#include <iostream>
#include <string>

int main() {
    // std::cout - standard output (buffered)
    std::cout << "cout: standard output (buffered)" << std::endl;

    // std::cerr - standard error (unbuffered, flushed immediately)
    std::cerr << "cerr: standard error (unbuffered)" << std::endl;

    // std::clog - standard log (buffered, goes to stderr)
    std::clog << "clog: standard log (buffered to stderr)" << std::endl;

    // Demonstrate that cout and cerr go to different streams
    // (visible when redirecting: ./example > out.txt 2> err.txt)
    std::cout << "This goes to stdout" << std::endl;
    std::cerr << "This goes to stderr" << std::endl;

    // Stream state checking
    std::cout << "\nStream states:" << std::endl;
    std::cout << "cout good: " << std::cout.good() << std::endl;
    std::cout << "cerr good: " << std::cerr.good() << std::endl;

    // Tie: cin is tied to cout by default (cout is flushed before cin reads)
    std::cout << "cin tied to cout: "
              << (std::cin.tie() == &std::cout ? "yes" : "no") << std::endl;

    // Sync with C stdio
    std::cout << "sync_with_stdio: enabled by default" << std::endl;

    // flush vs endl
    std::cout << "Explicit flush" << std::flush;
    std::cout << " - done" << std::endl;

    return 0;
}

// Expected output:
// cout: standard output (buffered)
// cerr: standard error (unbuffered)
// clog: standard log (buffered to stderr)
// This goes to stdout
// This goes to stderr
//
// Stream states:
// cout good: 1
// cerr good: 1
// cin tied to cout: yes
// sync_with_stdio: enabled by default
// Explicit flush - done
