// CodeNebula - C++23 Example: std::forward_like
// Compile: g++ -std=c++23 -Wall -Wextra -o example forward_like.cpp
// Note: Requires GCC 13+ / Clang 17+

#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// std::forward_like<T>(u) forwards u with the same value category and
// const-qualification as T. This preserves the "ownership" semantics
// of an outer wrapper when accessing inner members.

struct Inner {
    std::string name = "widget";
};

struct Wrapper {
    Inner inner;

    // Without forward_like, accessing inner from an rvalue Wrapper
    // would still yield an lvalue reference. forward_like fixes this.

    // C++23: propagate the value category of *this to inner
    template <typename Self>
    auto&& get(this Self&& self) {
        return std::forward_like<Self>(self.inner);
    }
};

// Demonstrate value category detection
void observe(Inner& /*x*/)        { std::cout << "  -> lvalue ref\n"; }
void observe(const Inner& /*x*/)  { std::cout << "  -> const lvalue ref\n"; }
void observe(Inner&& /*x*/)       { std::cout << "  -> rvalue ref\n"; }
void observe(const Inner&& /*x*/) { std::cout << "  -> const rvalue ref\n"; }

// forward_like in a generic context
template <typename Outer, typename Inner_>
void access_member(Outer&& outer, Inner_ Outer::*member) {
    // Forward the member with the same category as the outer object
    using OuterRef = Outer&&;
    auto&& val = std::forward_like<OuterRef>(outer.*member);
    observe(std::forward<decltype(val)>(val));
}

int main() {
    std::cout << "=== std::forward_like ownership-preserving forwarding ===\n\n";

    Wrapper w;
    const Wrapper cw;

    // Deducing this + forward_like
    std::cout << "w.get() [mutable lvalue]:\n";
    observe(w.get());

    std::cout << "cw.get() [const lvalue]:\n";
    observe(cw.get());

    std::cout << "Wrapper{}.get() [rvalue]:\n";
    observe(Wrapper{}.get());

    std::cout << "std::move(cw).get() [const rvalue]:\n";
    observe(std::move(cw).get());

    std::cout << "\n--- Direct forward_like examples ---\n";

    Inner inner;
    std::cout << "forward_like<int&>(inner):        ";
    observe(std::forward_like<int&>(inner));

    std::cout << "forward_like<const int&>(inner):  ";
    observe(std::forward_like<const int&>(inner));

    std::cout << "forward_like<int&&>(inner):       ";
    observe(std::forward_like<int&&>(inner));

    std::cout << "forward_like<const int&&>(inner): ";
    observe(std::forward_like<const int&&>(inner));

    return 0;
}

// Expected output:
// === std::forward_like ownership-preserving forwarding ===
//
// w.get() [mutable lvalue]:
//   -> lvalue ref
// cw.get() [const lvalue]:
//   -> const lvalue ref
// Wrapper{}.get() [rvalue]:
//   -> rvalue ref
// std::move(cw).get() [const rvalue]:
//   -> const rvalue ref
//
// --- Direct forward_like examples ---
// forward_like<int&>(inner):        -> lvalue ref
// forward_like<const int&>(inner):  -> const lvalue ref
// forward_like<int&&>(inner):       -> rvalue ref
// forward_like<const int&&>(inner): -> const rvalue ref
