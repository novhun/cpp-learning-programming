# Modern C++ Masterclass: From Fundamentals to Professional Systems

A structured, 20-part curriculum designed for modern C++ (C++17 / C++20). Each lesson contains a dedicated self-contained, runnable program (`main.cpp`) and an in-depth textbook guide (`README.md`) complete with theory, architecture diagrams, code explanations, and hands-on exercises.

All code is compiled and verified with **zero warnings** under strict production-grade compiler flags:
```bash
-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
```

---

## Curriculum Table of Contents

| Lesson | Topic | Core Concepts Covered | Runnable Code | Study Guide |
| :---: | :--- | :--- | :---: | :---: |
| **Basic** | **"Hello World" & Fundamentals** | Preprocessor `#include`, `main()`, `cout`/`cin`, `\n` vs `endl`, basic types, math | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/basic/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/basic/README.md) |
| **01** | **Variables, Types & I/O** | Memory sizes, `<cstdint>`, `cin`/`cout`, `<iomanip>` tables, `static_cast` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part1/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part1/README.md) |
| **02** | **Control Flow & Loops** | `if`/`switch`, `for`/`while`/`do-while`, `break`/`continue`, Multi-item POS Terminal | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part2/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part2/README.md) |
| **03** | **Functions & Scope** | Pass-by-value vs `&` vs `const &`, Overloading, Default args, `constexpr` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part3/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part3/README.md) |
| **04** | **Arrays & Strings** | `std::array`, Bounds safety `.at()`, `std::string`, Zero-copy `std::string_view` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part4/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part4/README.md) |
| **05** | **Pointers & Memory** | Addresses `&`, Dereference `*`, `nullptr`, Stack vs Heap, `new`/`delete` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part5/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part5/README.md) |
| **06** | **References & Enums** | Reference semantics, Const correctness matrix, Scoped `enum class : uint8_t` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part6/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part6/README.md) |
| **07** | **Structs & Bindings** | `struct`, Memory padding/alignment, C++17 Structured Bindings `auto [a, b]` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part7/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part7/README.md) |
| **08** | **OOP I: Encapsulation** | Classes, Private invariants, Member initializer lists, Destructors, `const` methods | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part8/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part8/README.md) |
| **09** | **OOP II: Polymorphism**| Dynamic dispatch, VTable, Pure virtuals, Abstract interfaces, Virtual destructors | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part9/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part9/README.md) |
| **10** | **Rule of 3 / 5 / 0** | Operator overloading, Deep copying, Move semantics (`&&`, `std::move`), Rule of 5 | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part10/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part10/README.md) |
| **11** | **Generic Templates** | Function/Class templates, Non-type parameters, Specialization, `<type_traits>` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part11/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part11/README.md) |
| **12** | **Smart Pointers & RAII**| `std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`, Preventing cyclic leaks | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part12/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part12/README.md) |
| **13** | **STL Containers** | `std::vector`, `std::deque`, `std::list`, `std::map`, `std::unordered_map`, Big-O | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part13/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part13/README.md) |
| **14** | **STL Algorithms** | Modern Lambdas, `std::sort`, Predicates, Erase-Remove idiom, `std::accumulate` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part14/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part14/README.md) |
| **15** | **File I/O Streams** | Text & CSV parsing, Stream modes, Binary struct serialization, RAII files | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part15/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part15/README.md) |
| **16** | **Exception Handling**| `try`/`catch`/`throw`, Exception hierarchy, Custom exceptions, `noexcept` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part16/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part16/README.md) |
| **17** | **Modern C++ Features** | `std::optional`, `std::variant`, `std::visit`, `if` with initializers | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part17/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part17/README.md) |
| **18** | **Multithreading** | `std::thread`, `std::mutex`, `std::lock_guard`, `std::atomic<T>`, `std::async` | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part18/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part18/README.md) |
| **19** | **Design Patterns** | Thread-safe Meyers Singleton, Factory Method, Strategy Pattern, Observer Pattern | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part19/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part19/README.md) |
| **20** | **Capstone Project** | Enterprise POS & Inventory Engine combining all concepts into an interactive app | [main.cpp](file:///Users/mrhun/Desktop/CPP-LESSON/part20/main.cpp) | [README.md](file:///Users/mrhun/Desktop/CPP-LESSON/part20/README.md) |

---

## Quick Start: How to Run Any Lesson

### Option 1: Interactive Runner Script (Recommended)
Launch the interactive terminal menu:
```bash
./run.sh
```
Or execute any specific lesson directly:
```bash
# Run Part 1
./run.sh 1

# Run Part 10
./run.sh 10

# Run Part 20 (Capstone)
./run.sh 20

# Compile and verify all 20 lessons
./run.sh all
```

### Option 2: Using Makefile
```bash
make run PART=5
make all
make clean
```

### Option 3: Direct Clang++ Invocation
```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part1/main.cpp -o part1/main
./part1/main
```

---

## Compiler Warnings Setup
In `.vscode/settings.json`, your workspace is configured with strict compiler flags to enforce best practices and eliminate subtle bugs before runtime:
- `-Wall -Wextra -Wpedantic`: Enable all standard and pedantic ISO C++ warnings.
- `-Wshadow`: Warn whenever a local variable shadows another variable or parameter.
- `-Wconversion -Wsign-conversion`: Flag unintended precision loss or signed/unsigned mismatches.
- `-Wnull-dereference`: Flag potential null pointer dereferences at compile-time.
