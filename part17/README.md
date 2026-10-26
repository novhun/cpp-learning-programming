# Part 17: Modern C++ Features (C++17 / C++20)

## Overview
C++17 and C++20 significantly modernized the language, bringing functional programming paradigms, enhanced type safety, and clean syntax constructs. In this lesson, you will master `std::optional` (safe nullability), `std::variant` (type-safe sum types), `std::visit`, and selection statements with initializers.

---

## 1. Safe Nullability with `std::optional<T>`

In legacy C++, functions that might not find a result typically returned magic sentinel values (`-1`, `nullptr`, empty string), which frequently caused crashes when forgotten.
`std::optional<T>` represents a value that may or may not be present:

```cpp
#include <optional>

std::optional<User> findUser(int id) {
    if (found) return user;
    return std::nullopt; // Explicit absence of value
}

auto result = findUser(42);
if (result.has_value()) {
    std::cout << result->name << "\n";
}
// Or provide an effortless default fallback:
std::string role = result.value_or(guestUser).role;
```

---

## 2. Type-Safe Tagged Unions: `std::variant<Ts...>`

A `std::variant` can hold a value of any of its template parameter types in the same memory footprint, knowing at all times which type it currently holds.

Pairing `std::variant` with `std::visit` enables elegant pattern matching:

```cpp
using JSONPrimitive = std::variant<int, double, std::string, bool>;

std::visit(Overloaded{
    [](int i) { std::cout << "Integer: " << i << "\n"; },
    [](double d) { std::cout << "Float: " << d << "\n"; },
    [](const std::string& s) { std::cout << "String: " << s << "\n"; },
    [](bool b) { std::cout << "Bool: " << std::boolalpha << b << "\n"; }
}, myVal);
```

---

## 3. If-Statements with Initializers

Restricts the scope of temporary variables exclusively to the `if` and `else` blocks:

```cpp
if (auto it = inventory.find(sku); it != inventory.end()) {
    // 'it' is available here
    std::cout << "Stock: " << it->second << "\n";
} else {
    // 'it' is available here as well
    std::cout << "Item not found.\n";
}
// 'it' is NOT leaked into the outer scope!
```

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part17/main.cpp -o part17/main
./part17/main
```

---

## 5. Hands-On Exercises

1. **Safe Square Root:** Write a function `std::optional<double> safeSqrt(double x)` that returns `std::nullopt` for negative numbers and the calculated square root for non-negative inputs.
2. **Polymorphic Result Type:** Build a `Result<T, Error>` type using `std::variant<T, std::string>` and demonstrate processing both success and failure outcomes without throwing exceptions.
