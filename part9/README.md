# Part 09: OOP: Inheritance, Polymorphism & Virtual Functions

## Overview
Inheritance establishes "is-a" relationships between classes, while polymorphism allows treating derived objects uniformly through a common base pointer or reference. In this lesson, you will master virtual functions, the Virtual Method Table (VTable), abstract classes, interface design, and the critical importance of virtual destructors.

---

## 1. Inheritance Syntax

Derived classes inherit member variables and methods from base classes:

```cpp
class Animal {
public:
    virtual void speak() const = 0; // Pure virtual
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Woof!\n";
    }
};
```

Access modifiers in inheritance:
- `public`: `public` in base remains `public` in derived.
- `protected`: Accessible within the class and its derived classes, but hidden from the outside world.
- `private`: Accessible only within the declaring class.

---

## 2. Dynamic Polymorphism & The VTable

When a class declares a `virtual` function, the compiler generates a hidden pointer (called `_vptr`) inside each instance pointing to a **Virtual Method Table (VTable)**. 
At runtime, calling `basePtr->virtualMethod()` looks up the actual derived function pointer in the VTable and executes it, enabling dynamic dispatch.

---

## 3. Abstract Classes (Interfaces)

A class containing at least one **pure virtual function** (`= 0`) is an Abstract Class:
```cpp
class PaymentProcessor {
public:
    virtual ~PaymentProcessor() = default;
    virtual bool processPayment(double amount) = 0; // Pure virtual
};
```
- You **cannot instantiate** an abstract class directly (`PaymentProcessor p;` will fail to compile).
- Derived classes must override all pure virtual functions to become concrete instantiable classes.

---

## 4. Why Virtual Destructors are Mandatory

If you delete a derived object through a base pointer, and the base class destructor is **not virtual**, the compiler will only call the base destructor! The derived destructor will be skipped, causing serious memory leaks and resource corruption:

```cpp
// INCORRECT (Undefined Behavior / Memory Leak):
class BadBase {
public:
    ~BadBase() {} // NOT VIRTUAL!
};

// CORRECT:
class GoodBase {
public:
    virtual ~GoodBase() = default; // VIRTUAL! Derived destructors will run properly.
};
```

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part9/main.cpp -o part9/main
./part9/main
```

---

## 6. Hands-On Exercises

1. **Shape Hierarchy:** Create an abstract base class `Shape` with pure virtual functions `double getArea() const = 0` and `double getPerimeter() const = 0`. Implement concrete derived classes `Circle` and `Rectangle`. Store a collection of `unique_ptr<Shape>` and calculate total surface area.
2. **Game Character Hierarchy:** Build a base class `GameCharacter` with a virtual `attack()` method. Subclass `Warrior`, `Mage`, and `Archer`, each dealing different damage types.
