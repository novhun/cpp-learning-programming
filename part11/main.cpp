#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstddef>

/**
 * ============================================================================
 * PART 11: TEMPLATES & GENERIC PROGRAMMING
 * ============================================================================
 * Concepts Covered:
 * 1. Function templates for type-independent logic.
 * 2. Class templates: Building a generic LIFO Stack data structure.
 * 3. Non-type template parameters (compile-time constants).
 * 4. Template specialization for specialized type handling.
 * 5. Modern C++ compile-time type introspection (type_traits).
 * ============================================================================
 */

// 1. Generic Function Template
template <typename T>
T findMax(T a, T b) {
    return (a > b) ? a : b;
}

// 2. Generic Class Template: Stack Container
template <typename T, std::size_t Capacity = 10>
class FixedStack {
private:
    T elements_[Capacity];
    std::size_t topIndex_ = 0;

public:
    bool push(const T& item) {
        if (topIndex_ >= Capacity) {
            std::cerr << "  Stack Overflow! Cannot push into full stack.\n";
            return false;
        }
        elements_[topIndex_++] = item;
        return true;
    }

    bool pop(T& outItem) {
        if (topIndex_ == 0) {
            std::cerr << "  Stack Underflow! Stack is empty.\n";
            return false;
        }
        outItem = elements_[--topIndex_];
        return true;
    }

    std::size_t size() const { return topIndex_; }
    bool isEmpty() const { return topIndex_ == 0; }
};

// 3. Template Specialization for pointer types
template <typename T>
void inspectType(T val) {
    std::cout << "  Generic value: " << val << "\n";
}

// Full specialization for const char* (C-strings)
template <>
void inspectType<const char*>(const char* val) {
    std::cout << "  [Specialized for C-string]: \"" << val << "\"\n";
}

// 4. Type Traits Demo
template <typename T>
void printCategory(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "  Value " << val << " is an Integral Type.\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "  Value " << val << " is a Floating-Point Type.\n";
    } else {
        std::cout << "  Value " << val << " is a Non-Arithmetic Custom Type.\n";
    }
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 11: Generic Templates        \n";
    std::cout << "======================================================\n";

    std::cout << "\n1. Function Templates:\n";
    std::cout << "  Max of (15, 42):          " << findMax(15, 42) << "\n";
    std::cout << "  Max of (3.1415, 2.7182):  " << findMax(3.1415, 2.7182) << "\n";
    std::cout << "  Max of ('Z', 'A'):        " << findMax('Z', 'A') << "\n";

    std::cout << "\n2. Generic FixedStack Container:\n";
    FixedStack<std::string, 5> stringStack;
    stringStack.push("Item-Alfa");
    stringStack.push("Item-Bravo");
    stringStack.push("Item-Charlie");

    std::cout << "  Stack size: " << stringStack.size() << "\n";
    std::string popped;
    while (stringStack.pop(popped)) {
        std::cout << "  Popped: " << popped << "\n";
    }

    std::cout << "\n3. Template Specialization:\n";
    inspectType(500);
    inspectType("C-Style String Literal");

    std::cout << "\n4. Compile-Time Type Traits (if constexpr):\n";
    printCategory(100);
    printCategory(99.95);
    printCategory(std::string("Hello"));

    std::cout << "\n[Part 11 Lesson Completed Successfully]\n";
    return 0;
}
