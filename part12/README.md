# Part 12: Modern Smart Pointers & RAII

## Overview
In modern C++, manual calls to `delete` are virtually obsolete. The **RAII (Resource Acquisition Is Initialization)** idiom binds the lifetime of resources to object scope. Smart pointers automate heap memory management with deterministic, leak-free deallocation.

---

## 1. Smart Pointer Comparison

| Smart Pointer | Ownership Model | Overhead | Use Case |
| :--- | :--- | :--- | :--- |
| `std::unique_ptr<T>` | **Exclusive** (1 owner) | **Zero** (Same as raw pointer) | Default choice for dynamically allocated objects. |
| `std::shared_ptr<T>` | **Shared** (Reference-counted) | Small (Control block + atomic ref-counter) | When multiple subsystems genuinely share lifetime ownership. |
| `std::weak_ptr<T>` | **Non-Owning** observer | None | Caches, observer patterns, breaking cyclic `shared_ptr` leaks. |

---

## 2. Exclusive Ownership with `std::unique_ptr`

- Created using `std::make_unique<T>(args...)`.
- Cannot be copied; must be moved via `std::move()`.
- Automatically calls `delete` when the pointer falls out of scope.

```cpp
#include <memory>

auto ptr = std::make_unique<DeviceSession>("ROUTER-01");
ptr->ping();

// Move ownership:
std::unique_ptr<DeviceSession> target = std::move(ptr);
// ptr is now nullptr!
```

---

## 3. Shared Ownership & Cyclic Memory Leaks

When two objects hold `std::shared_ptr` pointing to each other (Circular Reference), their reference counts can never drop to 0, causing a permanent memory leak!

**The Solution:** Break the cycle by having one side hold a `std::weak_ptr`:
- A `weak_ptr` does not increment the reference counter.
- Before accessing the target object, call `.lock()` to obtain a temporary `shared_ptr`.

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part12/main.cpp -o part12/main
./part12/main
```

---

## 5. Hands-On Exercises

1. **Smart File Handle:** Write a `unique_ptr` with a custom deleter lambda that manages a `FILE*` and calls `fclose` automatically when exiting scope.
2. **Observer Registry:** Implement a publisher-subscriber model where a `Subject` maintains a `std::vector<std::weak_ptr<Observer>>`. Broadcast messages to active observers and purge expired ones.
