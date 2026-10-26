# C++ Basics: "Hello World" & Fundamental Concepts

## Welcome to C++!
C++ is a high-performance, compiled, general-purpose programming language created by **Bjarne Stroustrup**. It powers game engines (Unreal Engine), operating systems (Windows, macOS, Linux), web browsers (Chrome), database engines (MySQL, MongoDB), high-frequency financial trading systems, and embedded hardware.

This lesson is your starting point. You will learn how a C++ program is structured from the very first line of code.

---

## 1. Anatomy of "Hello World"

Here is the simplest C++ program:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
```

Let's dissect every single token line-by-line:

### 1. `#include <iostream>`
- `#`: Signifies a **preprocessor directive**. It runs *before* the actual compiler parses your code.
- `include`: Tells the compiler to copy-paste the contents of another file into this file.
- `<iostream>`: The standard header file for **I**nput/**O**utput **Stream** operations. It provides `std::cout` (printing to screen) and `std::cin` (reading from keyboard).

### 2. `int main()`
- Every C++ program **must** have exactly one `main()` function. This is the **entry point** where execution begins.
- `int`: The return type. The program communicates an integer status code back to the operating system when it exits (`0` means success).
- `()`: The parameter list (empty here, or can accept command-line arguments).

### 3. `{ ... }`
- Curly braces define a **code block** or body of the function. All statements inside are executed sequentially.

### 4. `std::cout << "Hello, World!\n";`
- `std::`: Refers to the **Standard Namespace**. All standard C++ library utilities live inside `std::` to prevent naming collisions.
- `cout`: Stands for **C**haracter **OUT**put. It represents your terminal screen.
- `<<`: The **Stream Insertion Operator**. Think of it as an arrow sending the data on its right directly into the screen (`std::cout`).
- `"Hello, World!\n"`: A string literal. The `\n` is an escape character that prints a **new line** (Enter key).
- `;` (Semicolon): Marks the **end of a statement**. Missing a semicolon is the most common beginner error!

### 5. `return 0;`
- Exits the `main()` function and returns status code `0` to the operating system, indicating that the program executed without errors.

---

## 2. Escape Sequences & Newlines

| Symbol | Name | Description |
| :--- | :--- | :--- |
| `\n` | Newline | Moves the cursor to the beginning of the next line |
| `\t` | Tab | Inserts a horizontal tab space (usually 4 or 8 spaces) |
| `\\` | Backslash | Prints an actual backslash character `\` |
| `\"` | Double Quote | Prints an actual quotation mark `"` inside a string |

### `\n` vs `std::endl`:
- `\n`: Simply prints a newline character. **Fast and recommended**.
- `std::endl`: Prints a newline **AND forces a buffer flush** (`std::flush`). Flushing repeatedly in loops causes unnecessary performance slowdowns. Use `\n` for regular printing.

---

## 3. Basic Data Types (Variables)

A **variable** is a named storage location in your computer's memory (RAM).

```cpp
#include <string>

int age = 20;               // Whole numbers (integer)
double price = 19.99;       // Decimal floating-point numbers
char grade = 'A';           // Single character (in single quotes '')
std::string name = "Maria"; // Text strings (in double quotes "")
bool isStudent = true;      // Boolean flag: true (1) or false (0)
```

---

## 4. Basic Console Input with `std::cin`

To ask the user for information from the keyboard, use `std::cin` with the **extraction operator** `>>` (arrows point into the variable):

```cpp
std::string favoriteColor;
std::cout << "What is your favorite color? ";
std::cin >> favoriteColor;

std::cout << "Awesome! " << favoriteColor << " is a great color.\n";
```

> **Notice the Arrow Directions:**
> - `std::cout << variable;` (Push into the screen)
> - `std::cin >> variable;`  (Extract from keyboard into the variable)

---

## 5. How to Compile & Run

Open your terminal in the workspace directory and execute:

```bash
# 1. Compile using clang++
clang++ -std=c++17 -Wall -Wextra basic/main.cpp -o basic/main

# 2. Run the executable
./basic/main
```

Or using the master runner script:
```bash
./run.sh basic
```

---

## 6. Beginner Exercises

1. **Self-Introduction Card:** Write a program that prints your name, your country, and your favorite hobby, each on a separate line with a decorative border around it (using asterisks `*` or hyphens `-`).
2. **Simple Calculator:** Ask the user for two integers ($A$ and $B$). Print their sum ($A + B$), difference ($A - B$), and product ($A \times B$).
3. **Age in Months:** Ask the user for their age in years. Compute and print how many months old they are ($\text{age} \times 12$).
