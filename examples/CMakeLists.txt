# SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

include(GNUInstallDirs)

# List of all buildable examples.
set(EXAMPLES latencies top_scores)

foreach(example ${EXAMPLES})
    # Add example executable.
    add_executable(${example} "")

    # Add example source file.
    target_sources(${example} PRIVATE ${example}.cpp)

    # Link example with the library.
    target_link_libraries(${example} PRIVATE beman::at_most)

    # Install .
    install(
        TARGETS ${example}
        COMPONENT beman.at_most_examples
        DESTINATION ${CMAKE_INSTALL_BINDIR}
        EXCLUDE_FROM_ALL
    )
endforeach()
