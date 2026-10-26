# Part 06: References, Const Correctness & Scoped Enums

## Overview
C++ references provide safer, cleaner syntax compared to raw pointers. Paired with const correctness, they allow writing APIs that are both zero-copy performant and immune to accidental mutations. In this lesson, you will also explore modern scoped enumerations (`enum class`), which eliminate name collisions and implicit type conversions common in C.

---

## 1. References vs Pointers

| Feature | Reference (`int&`) | Pointer (`int*`) |
| :--- | :--- | :--- |
| **Can be null?** | **No** (Must bind to a valid object upon declaration) | Yes (`nullptr`) |
| **Can be reseated?** | **No** (Always refers to the initial object) | Yes (Can be reassigned to point elsewhere) |
| **Syntax** | Natural value syntax (`ref = 5;`) | Requires dereference (`*ptr = 5;`) |
| **Address** | Shares address with bound object (`&ref == &obj`) | Has its own distinct memory address |

---

## 2. Const Correctness Guide

Read pointer declarations from **right to left**:

1. `const int* p`: "p is a pointer to an integer that is constant." (Cannot change `*p`, but can change `p`).
2. `int* const p`: "p is a constant pointer to an integer." (Cannot change `p`, but can change `*p`).
3. `const int* const p`: "p is a constant pointer to a constant integer." (Neither can change).

```cpp
void inspectProduct(const Product& prod) {
    // prod cannot be modified inside this function!
    // Ensures compile-time read-only safety.
}
```

---

## 3. Scoped Enumerations (`enum class`)

Legacy C-style `enum Color { Red, Green }` leaks its identifiers into the surrounding scope and allows implicit conversion to integers (e.g., `Red == 0` evaluates to true!).

Modern `enum class` solves both problems:
- Values are strictly scoped: `Color::Red`.
- No implicit conversions to integers (must use `static_cast` if needed).
- Custom underlying integer storage can be specified (e.g. `: uint8_t` to save memory).

```cpp
enum class OrderStatus : uint8_t {
    Pending = 1,
    Processing = 2,
    Shipped = 3,
    Delivered = 4,
    Cancelled = 5
};

OrderStatus status = OrderStatus::Pending;
```

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part6/main.cpp -o part6/main
./part6/main
```

---

## 5. Hands-On Exercises

1. **Traffic Light Controller:** Create an `enum class TrafficLight : uint8_t { Red, Yellow, Green }`. Write a function `TrafficLight nextState(TrafficLight current)` that transitions in standard traffic cycle order.
2. **Const Reference Validator:** Write a function `bool isValidEmail(const std::string& email)` that checks if an email string contains `@` and `.`. Ensure zero memory copying occurs.
