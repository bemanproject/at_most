// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/nth_element_at_most.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <array>

using namespace beman::at_most;

template <typename Container, typename Compare = std::less<>>
void expect_equivalent_to_std(Container v, int n, Compare comp = {}) {
    auto v_std     = v;
    auto v_at_most = v;
    auto size      = static_cast<std::ptrdiff_t>(std::distance(v_std.begin(), v_std.end()));

    if (n >= 0 && n < size) {
        std::nth_element(v_std.begin(), v_std.begin() + n, v_std.end(), comp);
    }

    nth_element_at_most(v_at_most.begin(), v_at_most.end(), n, comp);

    if (n >= 0 && n < size) {
        EXPECT_EQ(v_at_most[n], v_std[n]);
        for (std::ptrdiff_t i = 0; i < n; ++i) {
            EXPECT_FALSE(comp(v_at_most[n], v_at_most[i]));
        }
        for (std::ptrdiff_t i = n + 1; i < size; ++i) {
            EXPECT_FALSE(comp(v_at_most[i], v_at_most[n]));
        }
    } else {
        EXPECT_EQ(v_at_most, v_std);
    }
}

TEST(NthElementAtMostTest, Basic) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    expect_equivalent_to_std(v, 2);
}

TEST(NthElementAtMostTest, EdgeCases) {
    std::vector<int> v = {1, 2, 3};
    expect_equivalent_to_std(v, 0);
    expect_equivalent_to_std(v, 2);
    expect_equivalent_to_std(v, -1);
    expect_equivalent_to_std(v, 3);
    expect_equivalent_to_std(v, 100);
}

TEST(NthElementAtMostTest, ConstexprStaticAssert) {
    constexpr bool result = []() {
        std::array<int, 5> a = {5, 4, 3, 2, 1};
        nth_element_at_most(a.begin(), a.end(), 2);
        return a[2] == 3;
    }();
    static_assert(result);
    EXPECT_TRUE(result);
}

// Ranges

struct Holder {
    int  id;
    int  val;
    auto operator<=>(const Holder&) const = default;
};

template <typename Container, typename Compare = std::ranges::less, typename Proj = std::identity>
void expect_ranges_equivalent_to_std(Container v, int n, Compare comp = {}, Proj proj = {}) {
    auto v_std     = v;
    auto v_at_most = v;
    auto size      = static_cast<std::ptrdiff_t>(std::ranges::distance(v_std));

    if (n >= 0 && n < size) {
        std::ranges::nth_element(v_std, v_std.begin() + n, comp, proj);
    }

    ranges::nth_element_at_most(v_at_most, n, comp, proj);

    if (n >= 0 && n < size) {
        EXPECT_EQ(std::invoke(proj, v_at_most[n]), std::invoke(proj, v_std[n]));
    } else {
        EXPECT_EQ(v_at_most, v_std);
    }
}

TEST(NthElementAtMostTest, RangesBasic) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    expect_ranges_equivalent_to_std(v, 2);
}

struct ValueSentinel {
    int  value;
    bool operator==(auto it) const { return *it == value; }
};

TEST(NthElementAtMostTest, RangesSentinel) {
    std::vector<int> v         = {5, 4, 3, 2, 1, 99};
    auto             v_std     = v;
    auto             v_at_most = v;
    auto             last      = ValueSentinel{99};

    auto nth_std = std::ranges::next(v_std.begin(), 2, last);
    std::ranges::nth_element(v_std.begin(), nth_std, last);

    ranges::nth_element_at_most(v_at_most.begin(), last, 2);

    auto it1 = v_at_most.begin();
    auto it2 = v_std.begin();
    while (!(last == it1)) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(NthElementAtMostTest, RangesEmpty) {
    std::vector<int> v = {};
    expect_ranges_equivalent_to_std(v, 0);
    expect_ranges_equivalent_to_std(v, 1);
    expect_ranges_equivalent_to_std(v, -1);
}

TEST(NthElementAtMostTest, RangesEdgeCases) {
    std::vector<int> v = {1, 2, 3};
    expect_ranges_equivalent_to_std(v, 0);
    expect_ranges_equivalent_to_std(v, 2);
    expect_ranges_equivalent_to_std(v, -1);
    expect_ranges_equivalent_to_std(v, 3);
    expect_ranges_equivalent_to_std(v, 100);
}

TEST(NthElementAtMostTest, RangesSentinelEdgeCases) {
    std::vector<int> v    = {5, 4, 3, 2, 1, 99};
    auto             last = ValueSentinel{99};
    auto             v1   = v;
    ranges::nth_element_at_most(v1.begin(), last, -1);
    auto v2 = v;
    ranges::nth_element_at_most(v2.begin(), last, 100);
    auto v3 = v;
    ranges::nth_element_at_most(v3.begin(), last, 5); // n == size
}

TEST(NthElementAtMostTest, RangesProjection) {
    std::vector<Holder> v = {{1, 10}, {2, 5}, {3, 8}};
    expect_ranges_equivalent_to_std(v, 1, std::ranges::less{}, &Holder::val);
}

TEST(NthElementAtMostTest, RangesConstexprStaticAssert) {
    constexpr bool result = []() {
        std::array<int, 5> a = {5, 4, 3, 2, 1};
        ranges::nth_element_at_most(a, 0);
        return a[0] == 1;
    }();
    static_assert(result);
    EXPECT_TRUE(result);
}
