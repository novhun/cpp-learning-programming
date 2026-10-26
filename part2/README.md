# Part 02: Control Flow, Conditionals & Loops

## Overview
Control flow dictates the execution path of a program based on runtime decisions and iterative algorithms. In this lesson, you will master conditional branching (`if`, `else if`, `else`, `switch`), ternary expressions, and the three fundamental loop constructs (`while`, `do-while`, `for`), along with loop flow interruptions (`break`, `continue`).

---

## 1. Conditional Logic

### `if`, `else if`, and `else`
Enables branch selection based on boolean expressions. Conditions are evaluated sequentially from top to bottom; as soon as one branch evaluates to `true`, its block executes and remaining branches are skipped.

```cpp
if (score >= 90) {
    grade = 'A';
} else if (score >= 80) {
    grade = 'B';
} else {
    grade = 'F';
}
```

### Ternary Operator (`?:`)
An inline shorthand for simple conditional value assignments:
```cpp
std::string status = (balance >= 0) ? "In Good Standing" : "Overdrawn";
```

---

## 2. Multi-Way Branching with `switch`

The `switch` statement evaluates an integral or enumeration expression and matches it against `case` labels.

```cpp
switch (tier) {
    case 1:
        discount = 0.05;
        break; // Crucial: prevents fall-through to next case
    case 2:
        discount = 0.10;
        break;
    default:
        discount = 0.0;
        break;
}
```

> **Warning:** Forgetting `break;` causes execution to "fall through" to the subsequent case, which is a frequent source of bugs in legacy code.

---

## 3. Repetition & Loops

### 1. `for` Loop (Count-Controlled)
Best used when the number of iterations is known before loop entry:
```cpp
for (int i = 0; i < 10; ++i) {
    std::cout << i << " ";
}
```

### 2. `while` Loop (Pre-Condition)
Best used when looping continues until an arbitrary condition changes, potentially executing 0 times:
```cpp
int number = 1;
while (number < 100) {
    number *= 2;
}
```

### 3. `do-while` Loop (Post-Condition)
Guaranteed to execute **at least once** before evaluating the exit condition. Ideal for interactive menus and retry prompts:
```cpp
char response;
do {
    // Process order
    std::cout << "Add another product? (y/n): ";
    std::cin >> response;
} while (response == 'y' || response == 'Y');
```

### 4. `break` vs `continue`
- `break`: Terminates the nearest enclosing loop immediately.
- `continue`: Skips the remainder of the current iteration and jumps to the loop's next increment/condition check.

---

## 4. Real-World Project: Multi-Item POS Terminal

The companion program `main.cpp` expands on basic single-item calculation by:
- Allowing endless multi-item entries in a dynamic `do-while` loop.
- Validating positive quantities and non-negative unit prices.
- Applying tiered bulk discounts based on cumulative cart item count.
- Calculating applicable sales tax and producing a professional ASCII receipt.

---

## 5. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part2/main.cpp -o part2/main
./part2/main
```

---

## 6. Hands-On Exercises

1. **ATM PIN Validator:** Write a `do-while` loop allowing a user up to 3 attempts to enter a 4-digit PIN. If correct, display "Access Granted"; if all 3 attempts fail, display "Card Blocked".
2. **Multiplication Matrix:** Using nested `for` loops and `std::setw(4)`, print an aligned $10 \times 10$ multiplication table.
