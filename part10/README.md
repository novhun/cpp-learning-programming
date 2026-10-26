# Part 10: Operator Overloading & The Rule of 3 / 5 / 0

## Overview
Operator overloading allows custom types to integrate naturally with C++ operators like `+`, `==`, and `<<`. When classes manage raw resources (like heap memory or file descriptors), understanding copy and move semantics is critical to prevent shallow-copy crashes and enable peak performance.

---

## 1. Deep Copy vs Shallow Copy

By default, the compiler provides a memberwise copy constructor. If a class contains a raw pointer `char* ptr`, copying the object merely copies the pointer address (**Shallow Copy**).
When both objects go out of scope, both destructors will call `delete` on the same address, triggering a catastrophic **Double Free crash**!

A **Deep Copy** allocates brand-new heap memory and duplicates the underlying data bytes.

---

## 2. The Rule of Three (C++98)

If a class requires a user-defined version of **any** of these three, it almost certainly needs **all three**:
1. **Destructor** (`~Class()`)
2. **Copy Constructor** (`Class(const Class& other)`)
3. **Copy Assignment Operator** (`Class& operator=(const Class& other)`)

---

## 3. Move Semantics & The Rule of Five (C++11)

C++11 introduced Rvalue references (`&&`) and Move Semantics. Instead of performing expensive deep copies of temporary objects, move semantics allows **stealing (pilfering)** the internal pointer from the source object in $O(1)$ time, leaving the source object in a hollow, valid empty state.

The Rule of Five adds:
4. **Move Constructor** (`Class(Class&& other) noexcept`)
5. **Move Assignment Operator** (`Class& operator=(Class&& other) noexcept`)

---

## 4. The Rule of Zero

> **Modern C++ Philosophy:** Design your classes such that you do not need to write ANY custom copy/move/destructor operations at all! Use existing RAII wrappers like `std::vector`, `std::string`, and `std::unique_ptr` to handle memory automatically.

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part10/main.cpp -o part10/main
./part10/main
```

---

## 6. Hands-On Exercises

1. **Fraction Class:** Implement a `Fraction` class with `numerator_` and `denominator_`. Overload `operator+`, `operator*`, `operator==`, and `operator<<` to print fractions like `3/4`.
2. **Dynamic Int Array:** Implement a custom `IntVector` class from scratch that manages `int* data_`, `size_`, and `capacity_`. Implement the complete Rule of Five.
