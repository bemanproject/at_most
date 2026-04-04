// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP
#define BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP

#include <algorithm>
#include <iterator>

namespace beman::at_most {

/**
 * @brief Rearranges the elements in the range [first, last), such that the first min(n, last - first) elements 
 * are sorted in ascending order and the remaining elements are left in an undefined order.
 *
 * Equivalent to:
 * @code
 * auto mid = first + std::min(n, std::distance(first, last));
 * std::partial_sort(first, mid, last, comp);
 * @endcode
 */
template <typename RandomAccessIterator, typename Compare = std::less<>>
constexpr void partial_sort_at_most(RandomAccessIterator first,
                                    RandomAccessIterator last,
                                    typename std::iterator_traits<RandomAccessIterator>::difference_type n,
                                    Compare comp = {}) {
    if (n <= 0) {
        return;
    }
    auto dist = std::distance(first, last);
    auto k = std::min(n, dist);
    auto mid = std::next(first, k);
    std::ranges::partial_sort(std::ranges::subrange(first, last), mid, comp);
}

} // namespace beman::at_most

#endif // BEMAN_AT_MOST_PARTIAL_SORT_PASS_HPP
