# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

set(ALL_EXAMPLES partial_sort_at_most)

foreach(example ${ALL_EXAMPLES})
    add_executable(beman.at_most.examples.${example})
    target_sources(beman.at_most.examples.${example} PRIVATE ${example}.cpp)
    target_link_libraries(
        beman.at_most.examples.${example}
        PRIVATE beman::at_most
    )
endforeach()
