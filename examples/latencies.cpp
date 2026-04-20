// examples/latencies.cpp                                             -*-C++-*-
#define _GLIBCXX_DEBUG // Forces GCC STL to visibly complain about bad iterators!
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <thread>
#include <vector>

namespace std20 {

// Prior to P3735R1, the code would look like this.
// Finding the Nth element requires manual bounds checking to avoid undefined behavior.

void isolate_nth(std::vector<int>& v, int n) {
    // if (n < 0 || n >= std::distance(v.begin(), v.end())) {
    //     return;
    // }
    std::nth_element(v.begin(), v.begin() + n, v.end());
}

std::vector<int> api(std::vector<int> latencies, int n) {
    isolate_nth(latencies, n);
    return latencies;
}

} // namespace std20

namespace beman_at_most {

// After P3735R1, the code would look like this.
// Using nth_element_at_most to handle bounds checking automatically.

void isolate_nth(std::vector<int>& v, int n) {
    beman::at_most::ranges::nth_element_at_most(v, n);
}

std::vector<int> api(std::vector<int> latencies, int n) {
    isolate_nth(latencies, n);
    return latencies;
}

} // namespace beman_at_most

void run(const std::vector<int>& latencies, int target) {
    std::cout << "\nTarget: " << target << "\n"; 
    std::cout << "  beman: ";
    std::vector<int> new_results = beman_at_most::api(latencies, target);
    for (int l : new_results) std::cout << l << ' ';
    std::cout << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    std::cout << "  std20: ";
    std::vector<int> old_results = std20::api(latencies, target);
    for (int l : old_results) std::cout << l << ' ';
    std::cout << "\n";
}

int example() {
    // Example from P3735R1: nth_element_at_most.
    std::vector<int> latencies = {90, 20, 70, 30, 10, 80, 40, 60, 50};

    run(latencies, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    run(latencies, 999999);

    return 0;
}

int main() { example(); }

// # build example:
// $ cmake --workflow --preset gcc-release
//
// # run example:
// $ ./build/gcc-release/examples/latencies
