# beman.at_most: Safe versions of partial_sort and get_nth_element (P3735)

<!--
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
-->

<!-- markdownlint-disable-next-line line-length -->
![Library Status](https://raw.githubusercontent.com/bemanproject/beman/refs/heads/main/images/badges/beman_badge-beman_library_under_development.svg) ![Continuous Integration Tests](https://github.com/bemanproject/at_most/actions/workflows/ci_tests.yml/badge.svg) ![Lint Check (pre-commit)](https://github.com/bemanproject/at_most/actions/workflows/pre-commit-check.yml/badge.svg) [![Coverage](https://coveralls.io/repos/github/bemanproject/at_most/badge.svg?branch=main)](https://coveralls.io/github/bemanproject/at_most?branch=main) ![Standard Target](https://github.com/bemanproject/beman/blob/main/images/badges/cpp29.svg) [![Compiler Explorer Example](https://img.shields.io/badge/Try%20it%20on%20Compiler%20Explorer-grey?logo=compilerexplorer&logoColor=67c52a)](https://wg21.link/P3735R1)

`beman.at_most` is a minimal C++ library conforming to [The Beman Standard](https://github.com/bemanproject/beman/blob/main/docs/beman_standard.md).
This can be used as a template for those intending to write Beman libraries.
It may also find use as a minimal and modern  C++ project structure.

**Implements**: `partial_sort_at_most` and `nth_element_at_most` proposed in [partial_sort_at_most, nth_element_at_most (P3735R1)](https://wg21.link/P3735R1).

**Status**: [Under development and not yet ready for production use.](https://github.com/bemanproject/beman/blob/main/docs/beman_library_maturity_model.md#under-development-and-not-yet-ready-for-production-use)

## License

`beman.at_most` is licensed under the Apache License v2.0 with LLVM Exceptions.

## Usage

`partial_sort_at_most` and `nth_element_at_most` provide safer, count-based alternatives to `partial_sort` and `nth_element`.

### Usage: partial_sort_at_most

The following code snippet illustrates how we can sort the "at most" 3 smallest elements of a vector:

```cpp
#include <beman/at_most/at_most.hpp>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {5, 4, 3, 2, 1};

    // Sort at most 3 elements
    beman::at_most::partial_sort_at_most(v.begin(), v.end(), 3);

    // Output: 1 2 3 5 4 (first 3 are sorted)
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
```

Full runnable examples can be found in [`examples/`](examples/).

## Dependencies

### Build Environment

This project requires at least the following to build:

* A C++ compiler that conforms to the C++20 standard or greater
* CMake 3.30 or later
* (Test Only) GoogleTest

You can disable building tests by setting CMake option `BEMAN_AT_MOST_BUILD_TESTS` to
`OFF` when configuring the project.

### Supported Platforms

| Compiler   | Version | C++ Standards | Standard Library  |
|------------|---------|---------------|-------------------|
| GCC        | 15-13   | C++26-C++17   | libstdc++         |
| GCC        | 12-11   | C++23-C++17   | libstdc++         |
| Clang      | 22-19   | C++26-C++17   | libstdc++, libc++ |
| Clang      | 18-17   | C++26-C++17   | libc++            |
| Clang      | 18-17   | C++20, C++17  | libstdc++         |
| AppleClang | latest  | C++26-C++17   | libc++            |
| MSVC       | latest  | C++23         | MSVC STL          |

## Development

See the [Contributing Guidelines](CONTRIBUTING.md).

## Integrate beman.at_most into your project

### Build

You can build at_most using a CMake workflow preset:

```bash
cmake --workflow --preset gcc-release
```

To list available workflow presets, you can invoke:

```bash
cmake --list-presets=workflow
```

For details on building beman.at_most without using a CMake preset, refer to the
[Contributing Guidelines](CONTRIBUTING.md).

### Installation

To install beman.at_most globally after building with the `gcc-release` preset, you can
run:

```bash
sudo cmake --install build/gcc-release
```

Alternatively, to install to a prefix, for example `/opt/beman`, you can run:

```bash
sudo cmake --install build/gcc-release --prefix /opt/beman
```

This will generate the following directory structure:

```txt
/opt/beman
├── include
│   └── beman
│       └── at_most
│           ├── at_most.hpp
│           └── ...
└── lib
    └── cmake
        └── beman.at_most
            ├── beman.at_most-config-version.cmake
            ├── beman.at_most-config.cmake
            └── beman.at_most-targets.cmake
```

### CMake Configuration

If you installed beman.at_most to a prefix, you can specify that prefix to your CMake
project using `CMAKE_PREFIX_PATH`; for example, `-DCMAKE_PREFIX_PATH=/opt/beman`.

You need to bring in the `beman.at_most` package to define the `beman::at_most` CMake
target:

```cmake
find_package(beman.at_most REQUIRED)
```

You will then need to add `beman::at_most` to the link libraries of any libraries or
executables that include `beman.at_most` headers.

```cmake
target_link_libraries(yourlib PUBLIC beman::at_most)
```

### Using beman.at_most

To use `beman.at_most` in your C++ project,
include an appropriate `beman.at_most` header from your source code.

```c++
#include <beman/at_most/at_most.hpp>
```

> [!NOTE]
>
> `beman.at_most` headers are to be included with the `beman/at_most/` prefix.
> Altering include search paths to spell the include target another way (e.g.
> `#include <at_most.hpp>`) is unsupported.
