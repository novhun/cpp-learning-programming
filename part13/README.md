# Part 13: Standard Template Library (STL) Containers

## Overview
The Standard Template Library (STL) provides industry-grade, highly optimized data structures. Understanding each container's internal architecture, Big-O time complexity, and memory cache locality is crucial for writing efficient C++ software.

---

## 1. Container Decision Matrix

| Container | Underlying Structure | Access | Search | Insert/Delete | Best Use Case |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `std::vector` | Contiguous dynamic array | $O(1)$ | $O(N)$ | Amortized $O(1)$ at end | **Default container for 90% of use cases.** Cache-friendly. |
| `std::deque` | Chunky array buffers | $O(1)$ | $O(N)$ | $O(1)$ at front & back | Double-ended queues, FIFO pipelines. |
| `std::list` | Doubly-linked list | $O(N)$ | $O(N)$ | $O(1)$ once node is found | Frequent insertions/removals in the middle. |
| `std::map` | Red-Black Tree (Self-balancing) | $O(\log N)$ | $O(\log N)$ | $O(\log N)$ | Key-value store where keys must stay sorted. |
| `std::unordered_map`| Hash Table with buckets | $O(1)$ avg | $O(1)$ avg | $O(1)$ avg | Ultra-fast key-value lookup where order does not matter. |
| `std::set` | Red-Black Tree | N/A | $O(\log N)$ | $O(\log N)$ | Enforcing uniqueness with sorted ordering. |

---

## 2. Why `std::vector` is King

Even when theoretical Big-O suggests a linked list has $O(1)$ insertion, modern CPU hardware is heavily optimized for contiguous memory cache lines (L1/L2/L3 caches).
Because `std::vector` elements reside side-by-side in RAM, CPU cache prefetching makes vector iterations orders of magnitude faster than pointer-chasing node structures like `std::list`.

---

## 3. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part13/main.cpp -o part13/main
./part13/main
```

---

## 4. Hands-On Exercises

1. **Word Frequency Counter:** Read a sentence from the user, split it into words, and use `std::unordered_map<std::string, int>` to count the occurrence frequency of each unique word.
2. **Priority Task Scheduler:** Use `std::priority_queue` to schedule tasks with different integer priority levels, popping and executing higher-priority tasks first.
