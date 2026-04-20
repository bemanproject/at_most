// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_AT_MOST_NTH_ELEMENT_AT_MOST_HPP
#define BEMAN_AT_MOST_NTH_ELEMENT_AT_MOST_HPP

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
constexpr void nth_element_at_most(RandomAccessIterator                                                 first,
                                   RandomAccessIterator                                                 last,
                                   typename std::iterator_traits<RandomAccessIterator>::difference_type n,
                                   Compare                                                              comp = {}) {
    if (n < 0) {
        return;
    }
    auto dist = std::distance(first, last);
    if (n >= dist) {
        return;
    }
    auto nth = std::next(first, n);
    std::nth_element(first, nth, last, comp);
}

namespace ranges {

namespace detail_nth_element_at_most {

struct fn {
    template <std::random_access_iterator I,
              std::sentinel_for<I>        S,
              typename Comp = std::ranges::less,
              typename Proj = std::identity>
        requires std::sortable<I, Comp, Proj>
    constexpr I operator()(I first, S last, std::iter_difference_t<I> n, Comp comp = {}, Proj proj = {}) const {
        if (n < 0) {
            return std::ranges::next(first, last);
        }
        auto k   = n;
        auto nth = std::ranges::next(first, k, last);
        if (nth == last) {
            return nth;
        }
        return std::ranges::nth_element(first, nth, last, comp, proj);
    }

    template <std::ranges::random_access_range R, typename Comp = std::ranges::less, typename Proj = std::identity>
        requires std::sortable<std::ranges::iterator_t<R>, Comp, Proj>
    constexpr std::ranges::borrowed_iterator_t<R>
    operator()(R&& r, std::ranges::range_difference_t<R> n, Comp comp = {}, Proj proj = {}) const {
        return operator()(std::ranges::begin(r), std::ranges::end(r), n, comp, proj);
    }
};

} // namespace detail_nth_element_at_most

inline constexpr detail_nth_element_at_most::fn nth_element_at_most{};

} // namespace ranges

} // namespace beman::at_most

#endif // BEMAN_AT_MOST_NTH_ELEMENT_AT_MOST_HPP
