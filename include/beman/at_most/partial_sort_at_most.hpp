// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP
#define BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP

// LCOV_EXCL_START
// clang-format off
#if defined(_MSVC_LANG)
    #if _MSVC_LANG < 202002L
        #error "beman.at_most requires at least C++20."
    #endif
#elif __cplusplus < 202002L
    #error "beman.at_most requires at least C++20."
#endif
// clang-format on
// LCOV_EXCL_STOP

#include <algorithm>
#include <functional>
#include <iterator>
#include <ranges>

namespace beman::at_most {

// LCOV_EXCL_START
template <typename RandomAccessIterator, typename Compare = std::less<>>
constexpr void partial_sort_at_most(RandomAccessIterator                                                 first,
                                    RandomAccessIterator                                                 last,
                                    typename std::iterator_traits<RandomAccessIterator>::difference_type n,
                                    Compare                                                              comp = {}) {
// LCOV_EXCL_STOP
    if (n <= 0) {
        return;
    } // LCOV_EXCL_LINE
    auto dist = std::distance(first, last);
    if (n >= dist) {
        std::sort(first, last, comp);
        return;
    } // LCOV_EXCL_LINE
    auto mid = std::next(first, n);
    std::partial_sort(first, mid, last, comp);
} // LCOV_EXCL_LINE

namespace ranges {

namespace detail_partial_sort_at_most {

struct fn {
    // LCOV_EXCL_START
    template <std::random_access_iterator I,
              std::sentinel_for<I>        S,
              typename Comp = std::ranges::less,
              typename Proj = std::identity>
        requires std::sortable<I, Comp, Proj>
    // LCOV_EXCL_STOP
    constexpr I operator()(I first, S last, std::iter_difference_t<I> n, Comp comp = {}, Proj proj = {}) const {
        auto k = std::max(std::iter_difference_t<I>(0), n);
        if (k == 0) {
            return std::ranges::next(first, last);
        }
        auto mid = std::ranges::next(first, k, last);
        return std::ranges::partial_sort(first, mid, last, comp, proj);
    }

    // LCOV_EXCL_START
    template <std::ranges::random_access_range R, typename Comp = std::ranges::less, typename Proj = std::identity>
        requires std::sortable<std::ranges::iterator_t<R>, Comp, Proj>
    constexpr std::ranges::borrowed_iterator_t<R>
    // LCOV_EXCL_STOP
    operator()(R&& r, std::ranges::range_difference_t<R> n, Comp comp = {}, Proj proj = {}) const {
        return operator()(std::ranges::begin(r), std::ranges::end(r), n, comp, proj);
    } // LCOV_EXCL_LINE
}; // LCOV_EXCL_LINE

} // namespace detail_partial_sort_at_most

inline constexpr detail_partial_sort_at_most::fn partial_sort_at_most{};

} // namespace ranges

} // namespace beman::at_most

#endif // BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP
