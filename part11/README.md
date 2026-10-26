# Part 11: Templates & Generic Programming

## Overview
Templates are the backbone of modern C++ and the Standard Template Library (STL). They allow writing type-agnostic code that generates optimized, strongly-typed machine code at compile time without any runtime virtual dispatch overhead.

---

## 1. Function Templates

Instead of writing separate duplicate functions for `int`, `double`, and `float`, declare a template:

```cpp
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

// Compiler instantiates findMax<int> and findMax<double> automatically:
int m1 = findMax(10, 20);
double m2 = findMax(3.14, 2.71);
```

---

## 2. Class Templates & Non-Type Parameters

Templates can accept types (`typename T`) as well as constant values (`std::size_t N`):

```cpp
template <typename T, std::size_t Capacity>
class FixedStack {
private:
    T buffer_[Capacity];
    std::size_t size_ = 0;
public:
    // ...
};

FixedStack<int, 100> intStack;
FixedStack<std::string, 20> nameStack;
```

---

## 3. Template Specialization

When a generic algorithm needs a specialized implementation for a specific type (e.g. `const char*` which requires `strcmp` instead of `>`):

```cpp
template <typename T>
void inspect(T val);

// Full specialization for const char*
template <>
void inspect<const char*>(const char* val) {
    // specialized handling
}
```

---

## 4. Compile-Time Branching (`if constexpr`)

Introduced in C++17, `if constexpr` enables code elimination at compile time based on type introspection traits from `<type_traits>`:

```cpp
template <typename T>
void logValue(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "Integer: " << val << "\n";
    } else {
        std::cout << "Other: " << val << "\n";
    }
}
```

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part11/main.cpp -o part11/main
./part11/main
```

---

## 6. Hands-On Exercises

1. **Generic Pair Container:** Create a class template `Pair<T, U>` holding two values of potentially different types with `getFirst()` and `getSecond()`.
2. **Generic Array Accumulator:** Write a function template `T sumArray(const T* arr, std::size_t count)` that computes the arithmetic sum of any numeric array.
