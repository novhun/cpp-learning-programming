# Part 04: Arrays, Strings & String Views

## Overview
Sequence storage and string manipulation are central to practical software development. In this lesson, you will learn how modern C++ replaces unsafe C-style arrays and raw `char*` pointers with type-safe `std::array`, rich dynamic `std::string`, and blazing-fast, zero-allocation `std::string_view`.

---

## 1. `std::array<T, N>` vs Raw C-Arrays

Raw C-arrays (`int arr[5]`) degrade into raw pointers when passed to functions, losing their length information.
Modern `std::array<T, N>` preserves compile-time size, supports STL algorithms, and lives directly on the stack with zero heap overhead.

```cpp
#include <array>

std::array<int, 4> numbers = {10, 20, 30, 40};

// Fast direct access:
int val = numbers[0];

// Safe bounds-checked access (throws std::out_of_range):
int safeVal = numbers.at(2);

// Size inquiry:
std::size_t count = numbers.size(); // 4
```

---

## 2. Dynamic Text with `std::string`

`std::string` provides heap-allocated dynamic string management, handling memory resizing, concatenation, and memory deallocation automatically.

```cpp
#include <string>

std::string text = "Product: Gaming Mouse, Price: 49.99";

// Searching
std::size_t pos = text.find("Price: ");
if (pos != std::string::npos) {
    std::string pricePart = text.substr(pos + 7);
    double price = std::stod(pricePart); // Convert string to double
}
```

---

## 3. High-Performance `std::string_view` (C++17)

Historically, passing a string to a read-only function required `const std::string&`. However, passing a string literal like `"Hello"` to `const std::string&` incurs an unnecessary dynamic heap allocation to create a temporary `std::string` object!

`std::string_view` solves this by holding only **a pointer to the characters and a length** (16 bytes on 64-bit systems). It never allocates memory!

```cpp
#include <string_view>

// Best practice for read-only string parameters:
void printReport(std::string_view sv) {
    std::cout << "Report: " << sv << "\n";
}

printReport("C-string literal"); // Zero allocations!
printReport(myStdString);        // Zero allocations!
```

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part4/main.cpp -o part4/main
./part4/main
```

---

## 5. Hands-On Exercises

1. **Array Statistics:** Create a `std::array<double, 10>` of student test scores. Write functions to find the highest score, the lowest score, and the class average.
2. **CSV String Tokenizer:** Write a function taking `std::string_view` containing a CSV line (e.g. `"Apple,15,2.50"`) and print each individual token on a separate line.
