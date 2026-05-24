// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {5, 4, 3, 2, 1};

    // Sort at most 3 elements
    beman::at_most::partial_sort_at_most(v.begin(), v.end(), 3);

    // Output: 1 2 3 5 4 (first 3 are sorted)
    for (int x : v)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
