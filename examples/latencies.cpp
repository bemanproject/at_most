// examples/latencies.cpp                                             -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>

#include <algorithm>
#include <iterator>
#include <vector>

namespace std20 {

// Prior to P3735R1, the code would look like this.
// Finding the Nth element requires manual bounds checking to avoid undefined behavior.

void isolate_nth(std::vector<int>& v, std::ptrdiff_t n) {
    if (n < 0 || n >= std::distance(v.begin(), v.end())) {
        return;
    }
    std::nth_element(v.begin(), v.begin() + n, v.end());
}

std::vector<int> api(std::vector<int> latencies) {
    isolate_nth(latencies, 4);
    return latencies;
}

} // namespace std20

namespace beman_at_most {

// After P3735R1, the code would look like this.
// Using nth_element_at_most to handle bounds checking automatically.

void isolate_nth(std::vector<int>& v, std::ptrdiff_t n) {
    beman::at_most::ranges::nth_element_at_most(v, n);
}

std::vector<int> api(std::vector<int> latencies) {
    isolate_nth(latencies, 4);
    return latencies;
}

} // namespace beman_at_most

int example() {
    // Example from P3735R1: nth_element_at_most.
    std::vector<int> latencies = {90, 20, 70, 30, 10, 80, 40, 60, 50};

    [[maybe_unused]] std::vector<int> old_latencies = std20::api(latencies);
    [[maybe_unused]] std::vector<int> new_latencies = beman_at_most::api(latencies);

    return 0;
}

int main() { example(); }

// # build example:
// $ cmake --workflow --preset gcc-release
//
// # run example:
// $ ./build/gcc-release/examples/latencies
