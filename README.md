# corex-library
A lightweight C++ library for compile-time type traits, macros, and utilities.

## Features
* **Type Traits:** Compile-time type inspection tools.
* **Preprocessor:** Macros for boilerplate reduction.
* **Utility:** Helper functions

### Examples

#### Perfect forwarding with `corex::forward`
```cpp
#include <corex/utility/forward.hpp>

#include <iostream>

void process(int &) { std::cout << "Lvalue processed\n"; }

void process(int &&) { std::cout << "Rvalue processed\n"; }

template <typename T> void wrapper(T &&arg) { process(corex::forward<T>(arg)); }
```
