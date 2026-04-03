// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/partial_sort_at_most.hpp>
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <algorithm>
#include <array>

using namespace beman::at_most;

// Boundary Clamping

TEST(PartialSortAtMostTest, BoundaryZero) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> original = v;
    partial_sort_at_most(v.begin(), v.end(), 0);
    EXPECT_EQ(v, original);
}

TEST(PartialSortAtMostTest, BoundaryNegative) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    std::vector<int> original = v;
    partial_sort_at_most(v.begin(), v.end(), -10);
    EXPECT_EQ(v, original);
}

TEST(PartialSortAtMostTest, BoundarySize) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    partial_sort_at_most(v.begin(), v.end(), 5);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

TEST(PartialSortAtMostTest, BoundaryOverSize) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    partial_sort_at_most(v.begin(), v.end(), 100);
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
}

// Iterator Variety

TEST(PartialSortAtMostTest, IteratorVector) {
    std::vector<int> v = {10, 9, 8, 7, 6};
    partial_sort_at_most(v.begin(), v.end(), 2);
    EXPECT_EQ(v[0], 6);
    EXPECT_EQ(v[1], 7);
}

TEST(PartialSortAtMostTest, IteratorRawPointer) {
    int arr[] = {10, 9, 8, 7, 6};
    partial_sort_at_most(arr, arr + 5, 2);
    EXPECT_EQ(arr[0], 6);
    EXPECT_EQ(arr[1], 7);
}

TEST(PartialSortAtMostTest, IteratorDeque) {
    std::deque<int> d = {10, 9, 8, 7, 6};
    partial_sort_at_most(d.begin(), d.end(), 2);
    EXPECT_EQ(d[0], 6);
    EXPECT_EQ(d[1], 7);
}

// Comparator Variety

TEST(PartialSortAtMostTest, ComparatorGreater) {
    std::vector<int> v = {1, 2, 3, 4, 5};
    partial_sort_at_most(v.begin(), v.end(), 2, std::greater<int>());
    EXPECT_EQ(v[0], 5);
    EXPECT_EQ(v[1], 4);
}

TEST(PartialSortAtMostTest, ComparatorLambda) {
    std::vector<int> v = {5, 4, 3, 2, 1};
    partial_sort_at_most(v.begin(), v.end(), 2, [](int a, int b) { return a < b; });
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 2);
}

struct CustomLess {
    bool operator()(int a, int b) const { return a < b; }
};

TEST(PartialSortAtMostTest, ComparatorStruct) {
    std::vector<int> v = {10, 20, 5, 1};
    partial_sort_at_most(v.begin(), v.end(), 2, CustomLess{});
    EXPECT_EQ(v[0], 1);
    EXPECT_EQ(v[1], 5);
}

// Compile-Time (constexpr)

TEST(PartialSortAtMostTest, ConstexprStaticAssert) {
    constexpr bool result = []() {
        std::array<int, 5> a = {5, 4, 3, 2, 1};
        partial_sort_at_most(a.begin(), a.end(), 2);
        return a[0] == 1 && a[1] == 2;
    }();
    static_assert(result, "partial_sort_at_most failed at compile-time");
    EXPECT_TRUE(result);
}
