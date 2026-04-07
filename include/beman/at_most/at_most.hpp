// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef BEMAN_AT_MOST_AT_MOST_HPP
#define BEMAN_AT_MOST_AT_MOST_HPP

#if (defined(_MSVC_LANG) ? _MSVC_LANG : __cplusplus) < 202002L
    #error "beman.at_most requires at least C++20."
#endif

#include <beman/at_most/partial_sort_at_most.hpp>
#include <beman/at_most/nth_element_at_most.hpp>

namespace beman::at_most {
/**
 * Returns the version of the beman.at_most library.
 * @return The version number.
 */
constexpr int version() noexcept { return 1; }

} // namespace beman::at_most

#endif // BEMAN_AT_MOST_AT_MOST_HPP
