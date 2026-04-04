// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/partial_sort_at_most.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <array>

using namespace beman::at_most;

template <typename Container, typename Compare = std::less<>>
void expect_equivalent_to_std(Container v, int n, Compare comp = {}) {
    auto v_std     = v;
    auto v_at_most = v;
    auto size      = std::distance(v_std.begin(), v_std.end());
    auto k         = std::max(static_cast<std::ptrdiff_t>(0), static_cast<std::ptrdiff_t>(n));

    if (k != 0) {
        k = std::min(k, size);
        std::partial_sort(v_std.begin(), v_std.begin() + k, v_std.end(), comp);
    }

    partial_sort_at_most(v_at_most.begin(), v_at_most.end(), n, comp);
    EXPECT_EQ(v_at_most, v_std);
}

// Boundary Clamping

TEST(PartialSortAtMostTest, ClampingZero) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    expect_equivalent_to_std(v, 0);
}

TEST(PartialSortAtMostTest, ClampingNegative) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    expect_equivalent_to_std(v, -10);
}

TEST(PartialSortAtMostTest, ClampingOverSize) {
    std::vector<int> v = {1, 5, 2, 4, 3};
    expect_equivalent_to_std(v, 100);
}

TEST(PartialSortAtMostTest, ClampingAtSize) {
    std::vector<int> v = {10, 20, 5, 1};
    expect_equivalent_to_std(v, 4);
}

// Iterator Variety

TEST(PartialSortAtMostTest, RawPointerArray) {
    std::vector<int> v     = {10, 5, 2, 8, 1};
    int              arr[] = {10, 5, 2, 8, 1};

    partial_sort_at_most(arr, arr + 5, 2);
    partial_sort_at_most(v.begin(), v.end(), 2);

    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(arr[i], v[i]);
    }
}

TEST(PartialSortAtMostTest, DequeVariety) {
    std::deque<int> d = {10, 5, 2, 8, 1};
    expect_equivalent_to_std(d, 3);
}

// Comparator Variety

TEST(PartialSortAtMostTest, CustomGreater) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    expect_equivalent_to_std(v, 3, std::greater<int>());
}

TEST(PartialSortAtMostTest, CustomLambda) {
    std::vector<int> v = {10, 5, 8, 1, 4};
    expect_equivalent_to_std(v, 2, [](int a, int b) { return a < b; });
}

struct CustomLess {
    bool operator()(int a, int b) const { return a < b; }
};

TEST(PartialSortAtMostTest, CustomStruct) {
    std::vector<int> v = {10, 5, 8, 1, 4};
    expect_equivalent_to_std(v, 2, CustomLess{});
}

// Compile-Time tests

TEST(PartialSortAtMostTest, ConstexprStaticAssert) {
    constexpr bool result = []() {
        std::array<int, 5> a = {5, 4, 3, 2, 1};
        partial_sort_at_most(a.begin(), a.end(), 2);
        return a[0] == 1 && a[1] == 2;
    }();
    static_assert(result, "partial_sort_at_most failed at compile-time");
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

    std::ranges::partial_sort(
        v_std,
        std::ranges::next(v_std.begin(), std::max(std::ptrdiff_t(0), std::ptrdiff_t(n)), v_std.end()),
        comp,
        proj);
    ranges::partial_sort_at_most(v_at_most, n, comp, proj);

    EXPECT_EQ(v_at_most, v_std);
}

TEST(PartialSortAtMostTest, RangesBasic) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    expect_ranges_equivalent_to_std(v, 3);
}

TEST(PartialSortAtMostTest, RangesProjection) {
    std::vector<Holder> v = {{1, 10}, {2, 5}, {3, 8}};
    expect_ranges_equivalent_to_std(v, 2, std::ranges::less{}, &Holder::val);
}

struct ValueSentinel {
    int  value;
    bool operator==(auto it) const { return *it == value; }
};

TEST(PartialSortAtMostTest, RangesSentinel) {
    std::vector<int> v         = {5, 4, 3, 2, 1, 99};
    auto             v_std     = v;
    auto             v_at_most = v;
    auto             last      = ValueSentinel{99};

    auto mid_std = std::ranges::next(v_std.begin(), 2, last);
    std::ranges::partial_sort(v_std.begin(), mid_std, last);

    ranges::partial_sort_at_most(v_at_most.begin(), last, 2);

    auto it1 = v_at_most.begin();
    auto it2 = v_std.begin();
    while (!(last == it1)) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(PartialSortAtMostTest, RangesConstexprStaticAssert) {
    constexpr bool result = []() {
        std::array<int, 5> a = {5, 4, 3, 2, 1};
        ranges::partial_sort_at_most(a, 2);
        return a[0] == 1 && a[1] == 2;
    }();
    static_assert(result);
    EXPECT_TRUE(result);
}
