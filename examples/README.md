# Examples for beman.at_most

<!--
SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
-->

List of usage examples for `beman.at_most`.

## Samples

Check basic `beman.at_most` library usages demonstrating safe bounded algorithms vs standard C++20 algorithms:

* local [./latencies.cpp](./latencies.cpp) (`beman::at_most::nth_element_at_most`)
* local [./top_scores.cpp](./top_scores.cpp) (`beman::at_most::partial_sort_at_most`)

### Local Build and Run

```shell
# build
$ cmake --workflow --preset gcc-release

# run latencies.cpp
$ ./build/gcc-release/examples/latencies

Target: 6
  beman: 20 10 50 30 40 60 70 90 80
  std20: 20 10 50 30 40 60 70 90 80

[SLEEPING] Pausing 2 seconds before the underlying out-of-bounds error triggers...

Target: 999999
  beman: 90 20 70 30 10 80 40 60 50
  std20:
Error: attempt to advance a dereferenceable (start-of-sequence) iterator
999999 steps, which falls outside its valid range.


# run top_scores.cpp
$ ./build/gcc-release/examples/top_scores

Target: 6
  beman: 9 8 7 6 5 4 1 2 3
  std20: 9 8 7 6 5 4 1 2 3

[SLEEPING] Pausing 2 seconds before the underlying out-of-bounds error triggers...

Target: 999999
  beman: 9 8 7 6 5 4 3 2 1
  std20:
Error: attempt to advance a dereferenceable (start-of-sequence) iterator
999999 steps, which falls outside its valid range.
```
