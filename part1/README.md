# Part 01: Variables, Data Types, Standard I/O & Formatting

## Overview
Welcome to the first lesson in the professional modern C++ masterclass. In this lesson, you will master the fundamental building blocks of C++ programs: how data is represented in memory, standard streams for input/output, safe user input parsing, and professional console formatting.

---

## 1. Data Types & Memory Allocation

Every variable in C++ has a specific type that determines:
1. How much memory it occupies (measured in bytes).
2. How the bits in memory are interpreted.
3. What operations can be performed on it.

| Data Type | Typical Size | Value Range | Common Usage |
| :--- | :--- | :--- | :--- |
| `bool` | 1 byte | `true` or `false` | Conditional flags |
| `char` | 1 byte | -128 to 127 (or 0 to 255) | Single ASCII character |
| `int` | 4 bytes | ~ -2.14 billion to +2.14 billion | General integer math |
| `float` | 4 bytes | 7 decimal digits of precision | Low-precision decimals |
| `double` | 8 bytes | 15-17 decimal digits of precision | Standard floating-point numbers |
| `int32_t` | exactly 4 bytes | -2,147,483,648 to 2,147,483,647 | Cross-platform fixed integer |
| `int64_t` | exactly 8 bytes | ~ -9 quintillion to +9 quintillion | Large numbers (timestamps, IDs) |
| `uint32_t` | exactly 4 bytes | 0 to 4,294,967,295 | Unsigned positive counts/indexes |

> **Pro-Tip (<cstdint>):** Standard types like `int` or `long` can have different sizes depending on the operating system and architecture. When writing professional or cross-platform code, use `<cstdint>` types like `int32_t`, `uint64_t` to guarantee the exact bit width across platforms.

---

## 2. Standard Streams & Safe Input

C++ provides four standard stream objects via `<iostream>`:
- `std::cout`: Standard buffered output stream.
- `std::cin`: Standard buffered input stream.
- `std::cerr`: Standard unbuffered error output stream (flushed immediately).
- `std::clog`: Standard buffered logging stream.

### The Classic `cin >>` vs `getline()` Trap
When reading numeric input using `std::cin >> x;`, the user enters a number followed by the Enter key (`\n`). 
`std::cin >>` reads the number but leaves the `\n` in the input stream buffer!
If you subsequently call `std::getline(std::cin, str);`, `getline` immediately encounters the newline and returns an empty string.

**The Fix:** Always discard the trailing newline using `std::cin.ignore()`:
```cpp
int age;
std::cin >> age;

// Clear the newline from the buffer:
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

std::string fullName;
std::getline(std::cin, fullName); // Now works correctly!
```

---

## 3. Advanced Output Formatting with `<iomanip>`

To format console output like a professional invoice or report, include `<iomanip>`:

- `std::setw(n)`: Sets the minimum field width for the next item.
- `std::left` / `std::right`: Specifies text alignment.
- `std::fixed`: Prints floating-point numbers in fixed-point decimal notation.
- `std::setprecision(n)`: When used with `std::fixed`, sets the exact number of decimal places.
- `std::setfill(c)`: Fills unused field spaces with a custom character (e.g. `'0'` or `'.'`).

```cpp
std::cout << std::left << std::setw(15) << "Item"
          << std::right << std::setw(10) << "Price" << "\n";
std::cout << std::string(25, '-') << "\n";
std::cout << std::left << std::setw(15) << "Coffee"
          << std::right << std::setw(10) << std::fixed << std::setprecision(2) << 3.50 << "\n";
```

---

## 4. Explicit Type Casting (`static_cast`)

Avoid legacy C-style casts like `(double)x`. Modern C++ provides `static_cast<NewType>(expression)`, which is checked at compile-time and explicitly states developer intent.

```cpp
int totalScore = 482;
int examCount = 5;

// WRONG: Integer division truncates 482 / 5 -> 96 (loses 0.4!)
double badAverage = totalScore / examCount;

// CORRECT: static_cast ensures floating-point division
double goodAverage = static_cast<double>(totalScore) / static_cast<double>(examCount); // 96.40
```

---

## 5. How to Compile & Run

Open your terminal in the workspace root or inside the `part1` folder:

```bash
# Compile with strict professional flags
clang++ -std=c++17 -Wall -Wextra -Wpedantic part1/main.cpp -o part1/main

# Run the binary
./part1/main
```

---

## 6. Hands-On Exercises

1. **Temperature Converter:** Write a program that asks the user for a temperature in Celsius (`double`) and outputs it in Fahrenheit ($F = C \times \frac{9}{5} + 32$) formatted to 1 decimal place.
2. **Student Grade Card:** Prompt for student name, student ID, and scores in 3 subjects. Print a formatted grade card table showing individual marks, total score, and calculated percentage with `std::setw` alignment.
