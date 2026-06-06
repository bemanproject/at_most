// examples/top_scores.cpp                                            -*-C++-*-
#define _GLIBCXX_DEBUG // Forces GCC STL to visibly complain about bad iterators!
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Prior to P3735R1, the code would look like this.
// Sorting at most N elements requires manual bounds checking (which is commented here) to avoid undefined behavior.
void run_standard(std::vector<int> scores, int n) {
    std::cout << "  std:   ";
    // if (n < 0) return;
    // if (n >= std::distance(scores.begin(), scores.end())) n = std::distance(scores.begin(), scores.end());

    std::partial_sort(scores.begin(), scores.begin() + n, scores.end(), std::greater<>{});

    for (int s : scores)
        std::cout << s << ' ';
    std::cout << "\n";
}

// After P3735R1, the code would look like this.
// Using partial_sort_at_most to handle bounds checking automatically.
void run_beman(std::vector<int> scores, int n) {
    std::cout << "  beman: ";
    beman::at_most::ranges::partial_sort_at_most(scores, n, std::greater<>{});

    for (int s : scores)
        std::cout << s << ' ';
    std::cout << "\n";
}

int main() {
    std::vector<int> scores = {9, 2, 7, 3, 1, 8, 4, 6, 5};

    std::cout << "\nTarget count: 6\n";
    run_beman(scores, 6);
    run_standard(scores, 6);

    std::cout << "\nTarget count: 999999 (Out of bounds)\n";
    run_beman(scores, 999999);

    // run_standard(scores, 999999); // Uncomment to see undefined behavior crash

    return 0;
}

// # build example:
// $ cmake --workflow --preset gcc-release
//
// # run example:
// $ ./build/gcc-release/examples/beman.at_most.examples.top_scores
