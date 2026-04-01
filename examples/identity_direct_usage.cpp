// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <beman/at_most/identity.hpp>

#include <iostream>

namespace exe = beman::at_most;

int main() {
    std::cout << exe::identity()(2024) << '\n';
    return 0;
}
