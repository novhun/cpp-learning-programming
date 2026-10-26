# Part 14: STL Algorithms, Iterators & Modern Lambdas

## Overview
C++ adheres to the philosophy: *"Never write a raw `for` loop if a standard STL algorithm can do it better."* STL algorithms in `<algorithm>` and `<numeric>` are heavily optimized by compiler vendors and pair seamlessly with modern C++ Lambda expressions.

---

## 1. Lambda Expressions Syntax

Lambdas are anonymous inline function objects:

```
[capture_clause](parameters) -> return_type { body }
```

### Capture Modes:
- `[]`: Captures nothing from the enclosing scope.
- `[=]`: Captures all outer variables used by value (creates local copies).
- `[&]`: Captures all outer variables by reference.
- `[x, &y]`: Explicit capture (`x` by value, `y` by reference).

```cpp
double discountMultiplier = 0.90;
auto applyDiscount = [discountMultiplier](double price) {
    return price * discountMultiplier;
};
```

---

## 2. The Core Algorithms

### 1. `std::sort`
Sorts elements in $O(N \log N)$ average and worst-case time using introsort:
```cpp
std::sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
    return a.price < b.price; // Ascending
});
```

### 2. The Erase-Remove Idiom
To remove elements satisfying a condition from a `std::vector`, combine `std::remove_if` with `vector::erase`:
```cpp
// 1. remove_if shifts non-matching elements forward and returns new logical end
// 2. vector::erase truncates the vector to the new end
items.erase(std::remove_if(items.begin(), items.end(), [](const auto& item) {
    return item.isExpired;
}), items.end());
```

### 3. `std::transform` (Map function)
Transforms elements from a source container and writes results to a destination:
```cpp
std::transform(source.begin(), source.end(), std::back_inserter(dest), [](int n) {
    return n * 2;
});
```

---

## 3. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part14/main.cpp -o part14/main
./part14/main
```

---

## 4. Hands-On Exercises

1. **Filtering High Scorers:** Given a `std::vector<int>` of test scores, use `std::copy_if` to extract all scores $\ge 80$ into an honors list.
2. **Custom String Sorter:** Sort a list of strings by **length ascending**, and if lengths are equal, alphabetically ascending.
