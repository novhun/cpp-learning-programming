# Part 03: Functions, Scope & Parameter Passing

## Overview
Functions are the primary unit of modular abstraction in C++. Writing high-performance, bug-free C++ code requires understanding parameter passing semantics (pass-by-value vs pass-by-reference vs pass-by-const-reference), function overloading rules, default arguments, and storage duration (automatic vs static).

---

## 1. Parameter Passing Modes

| Mode | Syntax Example | When to Use | Performance Impact |
| :--- | :--- | :--- | :--- |
| **Pass-by-Value** | `void fn(int x)` | Small primitive types (`int`, `double`, `char`, `bool`) | Copies bytes. Safe from side effects. |
| **Pass-by-Reference** | `void fn(int& x)` | When the function needs to modify caller state | Zero-copy. Caller variable is mutated. |
| **Pass-by-Const-Ref** | `void fn(const std::string& s)` | Complex types, objects, containers (`std::string`, `std::vector`) | **Zero-copy, read-only.** Peak performance! |

### Golden Rule of C++ Parameters:
- Pass cheap primitive types (`int`, `float`, `enum`, pointers) by value.
- Pass expensive objects (`std::string`, structs, classes) by `const &`.
- Pass by non-const reference `&` only if the caller expects the variable to be mutated (an "out" parameter).

---

## 2. Function Overloading & Default Arguments

### Function Overloading
C++ permits multiple functions to share the exact same name, as long as their parameter list differs in type, count, or order:
```cpp
double calculateTax(double amount, double rate);
double calculateTax(double amount, int fixedFee);
```

### Default Arguments
Default arguments allow callers to omit parameters. They must be declared from right to left in the prototype:
```cpp
// taxRate defaults to 0.08 if not supplied
double calculateTax(double amount, double taxRate = 0.08);

calculateTax(100.0);       // uses 0.08
calculateTax(100.0, 0.15); // overrides with 0.15
```

---

## 3. Compile-Time Functions (`constexpr`)

The `constexpr` keyword indicates that a function can be evaluated at compile time if its arguments are compile-time constants:
```cpp
constexpr int computeFactorial(int n) {
    return (n <= 1) ? 1 : (n * computeFactorial(n - 1));
}

// Evaluated during compilation; 120 is embedded directly into the binary!
constexpr int result = computeFactorial(5);
```

---

## 4. Static Local Storage

A `static` variable declared inside a function is initialized only once (on first entry) and retains its value across all subsequent invocations:
```cpp
void trackLogins() {
    static int loginCount = 0;
    ++loginCount;
    std::cout << "User login #" << loginCount << "\n";
}
```

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part3/main.cpp -o part3/main
./part3/main
```

---

## 6. Hands-On Exercises

1. **Swap Utility:** Write a function `void customSwap(int& a, int& b)` that swaps the contents of two integers using references. Verify that caller variables reflect the change.
2. **Safe Geometric Area Overloader:** Write three overloaded functions named `calculateArea`:
   - `calculateArea(double radius)` for a Circle ($\pi r^2$).
   - `calculateArea(double width, double height)` for a Rectangle ($w \times h$).
   - `calculateArea(double base, double height, bool isTriangle)` for a Triangle ($\frac{1}{2} b \times h$).
