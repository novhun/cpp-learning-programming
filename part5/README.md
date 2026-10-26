# Part 05: Pointers, Memory Addresses & Dynamic Allocation

## Overview
Understanding pointers and the computer memory model is the defining skill that distinguishes a true C++ engineer. In this lesson, you will master memory addresses, dereferencing, the distinction between the Stack and the Heap, dynamic memory allocation with `new` and `delete`, and how to prevent memory leaks and dangling pointers.

---

## 1. Pointers & Memory Architecture

Every variable in your application resides at a specific physical memory address (a hexadecimal byte offset in RAM).
- `&` (Address-of operator): Retrieves the memory address of a variable.
- `*` (Dereference operator): Accesses or modifies the value residing at the address pointed to.

```cpp
int age = 30;
int* pAge = &age; // pAge stores the memory address of age

*pAge = 35; // Modifies the value stored in 'age' to 35
```

---

## 2. Stack vs Heap (Free Store)

| Characteristic | Stack Memory | Heap (Free Store) Memory |
| :--- | :--- | :--- |
| **Allocation Speed** | Ultra-fast (CPU moves stack pointer register) | Slower (OS allocator finds free blocks) |
| **Lifetime** | Automatic (freed when scope `{}` ends) | Manual (persists until explicitly `delete`d) |
| **Size Limit** | Small (typically 1-8 MB per thread) | Huge (limited only by system RAM/virtual memory) |
| **Access Pattern** | LIFO (Last-In, First-Out) | Random access anywhere |

---

## 3. Dynamic Memory: `new` and `delete`

When data size is only known at runtime, allocate dynamically on the Heap:

### Single Objects:
```cpp
double* ptr = new double(49.99); // Allocate
// ... use *ptr ...
delete ptr;                      // Deallocate
ptr = nullptr;                   // Prevent dangling pointer
```

### Arrays:
```cpp
int* numbers = new int[100];     // Allocate array
// ... use numbers[i] ...
delete[] numbers;                // Must use delete[] for arrays!
numbers = nullptr;
```

---

## 4. The 3 Deadly Pointer Bugs

1. **Memory Leak:** Allocating memory with `new` without calling `delete`. Memory remains consumed until process termination.
2. **Dangling Pointer:** Continuing to read or write to a pointer after the memory it points to has already been `delete`d.
3. **Double Free:** Calling `delete` twice on the same memory address, corrupting the heap allocator and crashing the process.

> **Rule of Thumb:** Always set pointers to `nullptr` immediately after deleting them:
> ```cpp
> delete ptr;
> ptr = nullptr;
> ```

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part5/main.cpp -o part5/main
./part5/main
```

---

## 6. Hands-On Exercises

1. **Dynamic Array Resizer:** Write a program that asks the user for the number of items $N$, dynamically allocates an array of $N$ integers on the heap, fills it with multiples of 10, prints it, and safely frees the memory without leaks.
2. **Pointer Arithmetic Max:** Write a function `int* findMax(int* arr, int size)` that uses pointer traversal (without `[]` brackets) to return a pointer to the highest number in the array.
