// examples/latencies.cpp                                             -*-C++-*-
#define _GLIBCXX_DEBUG // Forces GCC STL to visibly complain about bad iterators!
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Prior to P3735R1, the code would look like this.
// Finding the Nth element requires manual bounds checking (which is commented here) to avoid undefined behavior.
void run_standard(std::vector<int> latencies, int n) {
    std::cout << "  std:   ";
    // if (n < 0 || n >= std::distance(latencies.begin(), latencies.end())) return;

    std::nth_element(latencies.begin(), latencies.begin() + n, latencies.end());

    for (int l : latencies)
        std::cout << l << ' ';
    std::cout << "\n";
}

// After P3735R1, the code would look like this.
// Using nth_element_at_most to handle bounds checking automatically.
void run_beman(std::vector<int> latencies, int n) {
    std::cout << "  beman: ";
    beman::at_most::ranges::nth_element_at_most(latencies, n);

    for (int l : latencies)
        std::cout << l << ' ';
    std::cout << "\n";
}

int main() {
    // Example from P3735R1: nth_element_at_most.
    std::vector<int> latencies = {90, 20, 70, 30, 10, 80, 40, 60, 50};

    std::cout << "\nTarget index: 6\n";
    run_beman(latencies, 6);
    run_standard(latencies, 6);

    std::cout << "\nTarget index: 0\n";
    run_beman(latencies, 0);

    std::cout << "\nTarget index: 999999 (Out of bounds)\n";
    run_beman(latencies, 999999);

    // run_standard(latencies, 999999); // Uncomment to see undefined behavior crash

    return 0;
}

// # build example:
// $ cmake --workflow --preset gcc-release
//
// # run example:
// $ ./build/gcc-release/examples/beman.at_most.examples.latencies
