// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/at_most.hpp>
#include <gtest/gtest.h>

TEST(AtMostTest, VersionTest) { EXPECT_EQ(beman::at_most::version(), 1); }
