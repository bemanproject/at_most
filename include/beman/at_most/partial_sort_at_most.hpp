// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP
#define BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP

// clang-format off
#if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) < 202002L
    #error "beman.at_most requires at least C++20."
#endif
// clang-format on

#include <algorithm>
#include <functional>
#include <iterator>
#include <ranges>

namespace beman::at_most {

template <typename RandomAccessIterator, typename Compare = std::less<>>
constexpr void partial_sort_at_most(RandomAccessIterator                                                 first,
                                    RandomAccessIterator                                                 last,
                                    typename std::iterator_traits<RandomAccessIterator>::difference_type n,
                                    Compare                                                              comp = {}) {
    if (n <= 0) {
        return;
    }
    auto dist = std::distance(first, last);
    if (n >= dist) {
        std::sort(first, last, comp);
        return;
    }
    auto mid = std::next(first, n);
    std::partial_sort(first, mid, last, comp);
}

namespace ranges {

namespace detail_partial_sort_at_most {

struct fn {
    template <std::random_access_iterator I,
              std::sentinel_for<I>        S,
              typename Comp = std::ranges::less,
              typename Proj = std::identity>
        requires std::sortable<I, Comp, Proj>
    constexpr I operator()(I first, S last, std::iter_difference_t<I> n, Comp comp = {}, Proj proj = {}) const {
        auto k   = std::max(std::iter_difference_t<I>(0), n);
        if (k == 0) {
            return std::ranges::next(first, last);
        }
        auto mid = std::ranges::next(first, k, last);
        return std::ranges::partial_sort(first, mid, last, comp, proj);
    }

    template <std::ranges::random_access_range R, typename Comp = std::ranges::less, typename Proj = std::identity>
        requires std::sortable<std::ranges::iterator_t<R>, Comp, Proj>
    constexpr std::ranges::borrowed_iterator_t<R>
    operator()(R&& r, std::ranges::range_difference_t<R> n, Comp comp = {}, Proj proj = {}) const {
        return operator()(std::ranges::begin(r), std::ranges::end(r), n, comp, proj);
    }
};

} // namespace detail_partial_sort_at_most

inline constexpr detail_partial_sort_at_most::fn partial_sort_at_most{};

} // namespace ranges

} // namespace beman::at_most

#endif // BEMAN_AT_MOST_PARTIAL_SORT_AT_MOST_HPP
