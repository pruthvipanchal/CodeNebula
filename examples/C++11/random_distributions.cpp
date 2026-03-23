// CodeNebula - C++11 Example: Random Distributions
// Compile: g++ -std=c++11 -Wall -Wextra -o example random_distributions.cpp

// C++11 provides many distribution classes that shape raw engine output
// into specific statistical distributions: uniform, normal, bernoulli,
// poisson, and more.

#include <iostream>
#include <random>
#include <iomanip>
#include <map>
#include <string>
#include <cmath>

// Print a simple horizontal histogram
void histogram(const std::string& title, std::map<int, int>& data, int scale) {
    std::cout << title << std::endl;
    for (auto& p : data) {
        std::cout << std::setw(4) << p.first << " | "
                  << std::string(p.second / scale, '*') << std::endl;
    }
}

int main() {
    std::mt19937 gen(42);

    // === Uniform Distributions ===
    std::cout << "=== Uniform ===" << std::endl;
    std::uniform_int_distribution<int> uid(1, 6);
    std::cout << "uniform_int [1,6]: ";
    for (int i = 0; i < 10; ++i) std::cout << uid(gen) << " ";
    std::cout << std::endl;

    std::uniform_real_distribution<double> urd(0.0, 1.0);
    std::cout << "uniform_real [0,1): ";
    std::cout << std::fixed << std::setprecision(3);
    for (int i = 0; i < 5; ++i) std::cout << urd(gen) << " ";
    std::cout << std::endl;

    // === Normal (Gaussian) Distribution ===
    std::cout << "\n=== Normal (mean=0, stddev=2) ===" << std::endl;
    std::normal_distribution<double> nd(0.0, 2.0);
    std::map<int, int> norm_hist;
    for (int i = 0; i < 5000; ++i) ++norm_hist[static_cast<int>(std::round(nd(gen)))];
    histogram("", norm_hist, 50);

    // === Bernoulli Distribution ===
    std::cout << "\n=== Bernoulli (p=0.3) ===" << std::endl;
    std::bernoulli_distribution bd(0.3);
    int true_count = 0;
    for (int i = 0; i < 1000; ++i) if (bd(gen)) ++true_count;
    std::cout << "true: " << true_count << "/1000 ("
              << (true_count / 10.0) << "%)" << std::endl;

    // === Binomial Distribution ===
    std::cout << "\n=== Binomial (n=10, p=0.5) ===" << std::endl;
    std::binomial_distribution<int> binom(10, 0.5);
    std::map<int, int> binom_hist;
    for (int i = 0; i < 3000; ++i) ++binom_hist[binom(gen)];
    histogram("", binom_hist, 30);

    // === Poisson Distribution ===
    std::cout << "\n=== Poisson (mean=4) ===" << std::endl;
    std::poisson_distribution<int> pd(4.0);
    std::map<int, int> pois_hist;
    for (int i = 0; i < 3000; ++i) ++pois_hist[pd(gen)];
    histogram("", pois_hist, 30);

    // === Exponential Distribution ===
    std::cout << "\n=== Exponential (lambda=1.5) ===" << std::endl;
    std::exponential_distribution<double> ed(1.5);
    std::cout << "5 samples: ";
    for (int i = 0; i < 5; ++i) std::cout << ed(gen) << " ";
    std::cout << std::endl;

    // === Discrete Distribution ===
    std::cout << "\n=== Discrete (weights: 1,1,1,1,6) ===" << std::endl;
    std::discrete_distribution<int> dd({1, 1, 1, 1, 6});
    std::map<int, int> dd_hist;
    for (int i = 0; i < 1000; ++i) ++dd_hist[dd(gen)];
    for (auto& p : dd_hist) {
        std::cout << "  " << p.first << ": " << p.second << std::endl;
    }

    return 0;
}

// Expected output (approximate, values are stochastic):
// === Uniform ===
// uniform_int [1,6]: 1 2 6 1 3 5 3 6 4 5
// uniform_real [0,1): 0.xxx 0.xxx ...
//
// === Normal (mean=0, stddev=2) ===
//   bell curve shape centered around 0
//
// === Bernoulli (p=0.3) ===
// true: ~300/1000 (~30%)
//
// === Binomial (n=10, p=0.5) ===
//   bell curve centered around 5
//
// === Poisson (mean=4) ===
//   peak around 4, right-skewed
//
// === Exponential (lambda=1.5) ===
// 5 samples: <positive values, mostly small>
//
// === Discrete (weights: 1,1,1,1,6) ===
//   0: ~100  1: ~100  2: ~100  3: ~100  4: ~600
