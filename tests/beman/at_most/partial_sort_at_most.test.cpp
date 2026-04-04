// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/partial_sort_at_most.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <array>

using namespace beman::at_most;

/**
 * @brief Helper for testing.
 * Compares our beman::at_most::partial_sort_at_most output with 
 * a manual call to std::partial_sort.
 */
template <typename Container, typename Compare = std::less<>>
void expect_equivalent_to_std(Container v, int n, Compare comp = {}) {
    auto v_std = v;
    auto v_at_most = v;
    auto size = std::distance(v_std.begin(), v_std.end());
    auto k = std::min(static_cast<std::ptrdiff_t>(std::max(0, n)), size);
    
    std::partial_sort(v_std.begin(), v_std.begin() + k, v_std.end(), comp);
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
    std::vector<int> v = {10, 5, 2, 8, 1};
    int arr[] = {10, 5, 2, 8, 1};
    
    partial_sort_at_most(arr, arr + 5, 2);
    partial_sort_at_most(v.begin(), v.end(), 2);

    for(int i=0; i<5; ++i) { EXPECT_EQ(arr[i], v[i]); }
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
