# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

find_package(GTest REQUIRED)

add_executable(beman.at_most.tests.identity)
target_sources(beman.at_most.tests.identity PRIVATE identity.test.cpp)
target_link_libraries(
    beman.at_most.tests.identity
    PRIVATE beman::at_most GTest::gtest GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(beman.at_most.tests.identity)
