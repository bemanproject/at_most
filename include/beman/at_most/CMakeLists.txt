# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

target_sources(
    beman.at_most
    PUBLIC
        FILE_SET HEADERS
            FILES at_most.hpp partial_sort_at_most.hpp nth_element_at_most.hpp
)
