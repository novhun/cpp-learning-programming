# Part 18: Concurrency & Multithreading

## Overview
Modern processors feature multiple CPU cores. Concurrency enables programs to execute multiple execution paths simultaneously to maximize hardware throughput and maintain responsive applications. In this lesson, you will master `std::thread`, data races, mutex synchronization, `std::lock_guard`, lock-free atomics (`std::atomic`), and asynchronous tasks (`std::async`/`std::future`).

---

## 1. Threads and Data Races

A **Data Race** occurs when two or more concurrent threads access the same memory location without synchronization, and at least one access is a write. Data races trigger **Undefined Behavior**.

```cpp
#include <thread>

void worker(int id) {
    std::cout << "Thread " << id << " running.\n";
}

std::thread t1(worker, 1);
t1.join(); // Always join or detach before std::thread is destroyed!
```

---

## 2. Synchronization: `std::mutex` & `std::lock_guard`

Never call `mutex.lock()` and `mutex.unlock()` manually! If an exception occurs between lock and unlock, the mutex remains locked forever (**Deadlock**).
Always use the RAII wrapper `std::lock_guard`:

```cpp
#include <mutex>

std::mutex accountMutex;

void deposit(double amount) {
    std::lock_guard<std::mutex> lock(accountMutex); // Automatically acquires lock
    balance += amount;
} // Automatically releases lock when exiting scope!
```

---

## 3. Lock-Free Atomic Operations: `std::atomic<T>`

For simple counters and status flags, mutexes introduce thread scheduling overhead. `std::atomic<T>` leverages hardware-level atomic CPU instructions (like compare-and-swap) to execute thread-safe reads and writes without locks:

```cpp
#include <atomic>

std::atomic<int> completedTasks{0};

// Lock-free atomic increment:
++completedTasks;
```

---

## 4. Asynchronous Tasks: `std::async` & `std::future`

`std::async` abstracts thread management by running a task asynchronously and returning a `std::future<T>` that will eventually yield the return value:

```cpp
#include <future>

auto futureResult = std::async(std::launch::async, []() {
    return calculateHeavyMetrics();
});

// Do other work on main thread...

// Wait and retrieve answer:
int answer = futureResult.get();
```

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part18/main.cpp -o part18/main
./part18/main
```

---

## 6. Hands-On Exercises

1. **Parallel Array Sum:** Given a vector of $1,000,000$ integers, divide it into 4 chunks and calculate the sum using 4 concurrent threads. Compare execution time with a single-threaded loop.
2. **Thread-Safe Log Queue:** Implement a thread-safe logger class where multiple producer threads can push log messages, and a single dedicated background thread flushes them to disk.
