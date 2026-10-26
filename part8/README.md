# Part 08: Object-Oriented Programming: Classes & Encapsulation

## Overview
Object-Oriented Programming (OOP) models software systems through self-contained entities called classes that combine data (attributes) and behavior (methods). In this lesson, you will learn data hiding, access modifiers, constructors with member initializer lists, delegating constructors, deterministic destructors, and const member functions.

---

## 1. Encapsulation & Data Hiding

Encapsulation restricts direct external access to internal object state. It ensures that internal variables can only be altered through controlled methods that enforce validation rules (invariants).

```cpp
class BankAccount {
private:
    double balance_; // Hidden from external access

public:
    // Controlled mutation with invariant validation
    bool withdraw(double amount) {
        if (amount > balance_ || amount <= 0.0) return false;
        balance_ -= amount;
        return true;
    }
};
```

---

## 2. Member Initializer Lists

Always prefer **member initializer lists** over assignments inside the constructor body:

```cpp
// BEST PRACTICE: Initializer list directly constructs members in place!
BankAccount(const std::string& id, double bal)
    : accountNumber_(id), balance_(bal) {}

// INFERIOR: Default-constructs first, then overwrites in body (double work!)
BankAccount(const std::string& id, double bal) {
    accountNumber_ = id; 
    balance_ = bal;
}
```

> **Mandatory Case:** `const` members and reference members **must** be initialized in the initializer list because they cannot be assigned to inside the constructor body.

---

## 3. Destructors (`~ClassName()`)

A destructor is called automatically when an object reaches the end of its lifetime (e.g. going out of scope or being `delete`d). Destructors enable C++'s signature strength: **deterministic cleanup** (closing files, releasing locks, freeing memory).

---

## 4. Const Member Functions

Marking a member function with `const` at the end promises that it will not modify any member variables of the object:

```cpp
double getBalance() const {
    // balance_ += 10; // COMPILE ERROR! Const method cannot modify members.
    return balance_;
}
```

This permits the function to be invoked on `const` instances: `const BankAccount acc; acc.getBalance();`.

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part8/main.cpp -o part8/main
./part8/main
```

---

## 6. Hands-On Exercises

1. **Digital Stopwatch Class:** Create a `Stopwatch` class with `start()`, `stop()`, and `getElapsedSeconds() const`. Prevent starting an already running watch.
2. **Rectangle Geometry Class:** Design a `Rectangle` class with private `width_` and `height_`. Enforce in the constructor and setters that dimensions must be strictly positive ($> 0$). Provide `getArea() const` and `getPerimeter() const`.
