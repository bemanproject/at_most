// examples/top_scores.cpp                                            -*-C++-*-
#define _GLIBCXX_DEBUG
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

namespace std20 {

// Sorting at most N elements requires manual bounds checking (to avoid UB).

void sort_top_n(std::vector<int>& v, int n) {
    // needs extra bounds checking
    
    // if (n < 0) {
    //     return;
    // }
    // if (n >= std::distance(v.begin(), v.end())) {
    //     n = std::distance(v.begin(), v.end());
    // }
    // std::partial_sort(v.begin(), v.begin() + n, v.end(), std::greater<>{});
    std::partial_sort(v.begin(), v.begin() + n, v.end(), std::greater<>{});
}

std::vector<int> api(std::vector<int> scores, int n) {
    sort_top_n(scores, n);
    return scores;
}

} // namespace std20

namespace beman_at_most {

// partial_sort_at_most includes bounds checking.

void sort_top_n(std::vector<int>& v, int n) {
    beman::at_most::ranges::partial_sort_at_most(v, n, std::greater<>{});
}

std::vector<int> api(std::vector<int> scores, int n) {
    sort_top_n(scores, n);
    return scores;
}

} // namespace beman_at_most

int example() {
    std::vector<int> scores = {9, 2, 7, 3, 1, 8, 4, 6, 5};

    auto run = [&](int target) {
        std::cout << "\nTarget: " << target << "\n";
        
        std::cout << "  beman: ";
        std::vector<int> new_results = beman_at_most::api(scores, target);
        for (int s : new_results) std::cout << s << ' ';
        std::cout << "\n";

        std::cout << "  std20: ";
        std::vector<int> old_results = std20::api(scores, target);
        for (int s : old_results) std::cout << s << ' ';
        std::cout << "\n";
    };

    run(6);
    run(999999);

    return 0;
}

int main() { example(); }

// # build example:
// $ cmake --workflow --preset gcc-release
//
// # run example:
// $ ./build/gcc-release/examples/top_scores
