# Part 19: Design Patterns in Modern C++

## Overview
Design Patterns are battle-tested architectural blueprints for recurring software design challenges. In modern C++, design patterns leverage smart pointers, RAII, and move semantics for clean, memory-safe implementations without raw pointers.

---

## 1. Meyers' Singleton

In C++11 and newer, static local variables with initializers are guaranteed by the language standard to be initialized in a **thread-safe manner** on first execution. This makes Scott Meyers' Singleton pattern the gold standard:

```cpp
class AppConfig {
private:
    AppConfig() = default;
public:
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    static AppConfig& getInstance() {
        static AppConfig instance; // Thread-safe lazy initialization!
        return instance;
    }
};
```

---

## 2. Strategy Pattern

The Strategy pattern defines a family of interchangeable algorithms and encapsulates each one inside a strategy class implementing a common interface.

```cpp
class IDiscountStrategy {
public:
    virtual ~IDiscountStrategy() = default;
    virtual double applyDiscount(double amount) const = 0;
};
```

This allows swapping discount policies at runtime without modifying the checkout or cart classes (Open/Closed Principle).

---

## 3. Factory Method Pattern

Decouples object creation from consumption. The client code depends only on abstract interfaces rather than concrete subclasses:

```cpp
auto strategy = DiscountStrategyFactory::createStrategy(DiscountType::VIP);
```

---

## 4. Observer Pattern (Pub/Sub)

Enables one-to-many dependency broadcasting. When a central subject's state changes, all registered observers are automatically notified without tightly coupling the subject to specific consumer classes.

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part19/main.cpp -o part19/main
./part19/main
```

---

## 6. Hands-On Exercises

1. **Logger Adapter:** Write an Adapter class that adapts a legacy third-party logging interface `LegacyLogger::logMessage(int level, const char* str)` to a clean modern C++ interface `ILogger::info(std::string_view msg)`.
2. **Payment Gateway Factory:** Extend the Factory pattern to instantiate payment processors based on user configuration settings loaded from disk.
