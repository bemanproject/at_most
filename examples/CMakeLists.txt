# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(ALL_EXAMPLES latencies top_scores partial_sort_at_most)

message("Examples to be built: ${ALL_EXAMPLES}")

foreach(example ${ALL_EXAMPLES})
    add_executable(beman.at_most.examples.${example})
    target_sources(beman.at_most.examples.${example} PRIVATE ${example}.cpp)
    target_link_libraries(
        beman.at_most.examples.${example}
        PRIVATE beman::at_most
    )
endforeach()
