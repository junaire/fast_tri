# fast_tri
> A blazing fast, branchless trigonometric library, it's header only

## Installation

To use `fast_tri` in your project, simply copy the `fast_tri.h` file into your project's directory and include it as follows:

```cpp
#include "fast_tri.h"
```

## Usage

This library only contains two functions:

* `double fast_sin(double)`
* `double fast_cos(double)`

> [!WARNING]  
> The functions above can only handle inputs between 0 - 2pi !!!

## Benchmark

```
Performance Benchmark:
  std::sin: 0.000339228 seconds
  fast_sin: 0.000154573 seconds
Speedup:
sin: 2.19461x

  std::cos: 0.000327002 seconds
  fast_cos: 0.000151847 seconds
Speedup:
cos: 2.1535x
```