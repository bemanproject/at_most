// examples/top_scores.cpp                                            -*-C++-*-
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>

#include <algorithm>
#include <iterator>
#include <vector>

namespace std20 {

// Prior to P3735R1, the code would look like this.
// Sorting at most N elements requires manual bounds checking to avoid undefined behavior.

void sort_top_n(std::vector<int>& v, std::ptrdiff_t n) {
    auto n_clamped = std::min<std::ptrdiff_t>(n, std::distance(v.begin(), v.end()));
    std::partial_sort(v.begin(), v.begin() + n_clamped, v.end(), std::greater<>{});
}

std::vector<int> api(std::vector<int> scores) {
    sort_top_n(scores, 3);
    return scores;
}

} // namespace std20

namespace beman_at_most {

// After P3735R1, the code would look like this.
// Using partial_sort_at_most to handle bounds checking automatically.

void sort_top_n(std::vector<int>& v, std::ptrdiff_t n) {
    beman::at_most::ranges::partial_sort_at_most(v, n, std::greater<>{});
}

std::vector<int> api(std::vector<int> scores) {
    sort_top_n(scores, 3);
    return scores;
}

} // namespace beman_at_most

int example() {
    // Example from P3735R1: partial_sort_at_most.
    std::vector<int> scores = {9, 2, 7, 3, 1, 8, 4, 6, 5};

    [[maybe_unused]] std::vector<int> old_scores = std20::api(scores);
    [[maybe_unused]] std::vector<int> new_scores = beman_at_most::api(scores);

    return 0;
}

int main() { example(); }

// # build example:
// $ cmake --workflow --preset gcc-release
//
// # run example:
// $ ./build/gcc-release/examples/top_scores
