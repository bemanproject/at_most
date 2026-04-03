# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

target_sources(
    beman.at_most
    PUBLIC
        FILE_SET HEADERS
            BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
            FILES 
                at_most.hpp
                partial_sort_at_most.hpp
)
