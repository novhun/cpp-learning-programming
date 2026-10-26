# Part 16: Exception Handling & Robust Error Management

## Overview
Errors are inevitable in real-world software. C++ exceptions decouple the point where an anomalous condition is detected from the point where it is handled. In this lesson, you will master `try`/`catch`/`throw`, standard exception types, custom exception subclasses, `noexcept` optimizations, and exception safety guarantees.

---

## 1. Exception Hierarchy

All standard C++ exceptions derive from `std::exception` (defined in `<stdexcept>` and `<exception>`):

```
std::exception
 ├── std::logic_error
 │    ├── std::invalid_argument
 │    ├── std::out_of_range
 │    └── std::length_error
 └── std::runtime_error
      ├── std::overflow_error
      └── std::underflow_error
```

---

## 2. Catching by `const std::exception&`

> **Rule:** ALWAYS catch exceptions by `const &` (const reference)!
> Catching by value (`catch (std::exception e)`) causes **Object Slicing**, which truncates derived exception members and loses valuable diagnostic information.

```cpp
try {
    performNetworkCall();
} catch (const NetworkTimeoutException& e) {
    // Specific recovery
} catch (const std::exception& e) {
    // Fallback logging
    std::cerr << "Fatal: " << e.what() << "\n";
}
```

---

## 3. The Three Exception Safety Guarantees

1. **Basic Guarantee:** If an exception is thrown, no resources (memory, file handles) are leaked, and objects remain in a valid, usable internal state.
2. **Strong Guarantee (Commit or Rollback):** If an operation fails, the program state remains exactly as it was before the operation began.
3. **Nothrow / Noexcept Guarantee:** The operation is guaranteed never to throw an exception under any circumstances.

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part16/main.cpp -o part16/main
./part16/main
```

---

## 5. Hands-On Exercises

1. **Safe Integer Division:** Implement a function `int divide(int numerator, int denominator)` that throws `std::overflow_error` on divide-by-zero or `INT_MIN / -1`.
2. **Custom File Parsing Exception:** Create a `CorruptFileException` inheriting from `std::runtime_error` that stores line number and filename where parsing failed.
