# Part 07: Structures, Memory Layout & Structured Bindings

## Overview
Structures (`struct`) group related variables into a single cohesive composite type. Unlike C, in C++ a `struct` is a full-fledged type capable of holding member functions, constructors, and access specifiers. In this lesson, you will learn how to model data with `struct`, inspect CPU memory alignment and padding, and unpack objects elegantly using C++17 Structured Bindings.

---

## 1. Structs in C++

In C++, the **only** syntactic difference between a `struct` and a `class` is the default visibility:
- `struct` members are **public** by default.
- `class` members are **private** by default.

```cpp
struct ProductRecord {
    int id;
    std::string name;
    double unitPrice;
    int stockQuantity;

    // Member function:
    double computeInventoryValue() const {
        return unitPrice * stockQuantity;
    }
};
```

---

## 2. Memory Alignment and Padding

CPUs access memory much faster when data addresses are aligned to multiples of their natural word size (e.g., 4-byte boundaries for 32-bit `int`, 8-byte boundaries for 64-bit `double`).
To satisfy this hardware requirement, the compiler automatically inserts invisible "padding bytes":

```cpp
struct Demo {
    char a;   // 1 byte
    // [3 bytes padding]
    int b;    // 4 bytes
    char c;   // 1 byte
    // [7 bytes padding]
    double d; // 8 bytes
};
// Total size: 24 bytes (even though data alone is only 14 bytes!)
```

> **Optimization Tip:** Arrange struct members from largest to smallest size to minimize padding holes.

---

## 3. C++17 Structured Bindings

Structured bindings provide clean syntax to unpack public members into individual local variables:

```cpp
ProductRecord p{101, "Mechanical Keyboard", 89.99, 20};

// Unpack members directly:
auto [id, name, price, qty] = p;

std::cout << "Name: " << name << ", Price: $" << price << "\n";
```

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part7/main.cpp -o part7/main
./part7/main
```

---

## 5. Hands-On Exercises

1. **2D Point Geometry:** Define a `struct Point` with coordinates `x` and `y` (`double`). Add a member function `double distanceTo(const Point& other) const` using the Pythagorean theorem $\sqrt{(x_2-x_1)^2 + (y_2-y_1)^2}$.
2. **Employee Payroll:** Define an `Employee` struct containing `id`, `name`, `hourlyRate`, and `hoursWorked`. Write a function that calculates total salary including overtime ($1.5\times$ for hours over 40) and unpacks the record using structured bindings.
