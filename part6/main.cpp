#include <iostream>
#include <string>
#include <cstdint>

/**
 * ============================================================================
 * PART 06: REFERENCES, CONST CORRECTNESS & SCOPED ENUMS
 * ============================================================================
 * Concepts Covered:
 * 1. References (&): Aliases that cannot be null or reseated.
 * 2. Const pointers vs Pointers to const.
 * 3. Const correctness: Writing tamper-proof APIs.
 * 4. Scoped enumerations (enum class) vs legacy unscoped enums.
 * 5. Explicit underlying types (enum class : uint8_t).
 * 6. Order processing state machine demo.
 * ============================================================================
 */

// Strongly-typed scoped enum with explicit 8-bit underlying storage
enum class OrderStatus : uint8_t {
    Pending = 1,
    Processing = 2,
    Shipped = 3,
    Delivered = 4,
    Cancelled = 5
};

// Function returning string representation of enum
std::string getStatusName(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending:    return "Pending";
        case OrderStatus::Processing: return "Processing";
        case OrderStatus::Shipped:    return "Shipped";
        case OrderStatus::Delivered:  return "Delivered";
        case OrderStatus::Cancelled:  return "Cancelled";
    }
    return "Unknown";
}

void demonstrateReferences() {
    std::cout << "\n========================================\n";
    std::cout << " 1. REFERENCES VS POINTERS\n";
    std::cout << "========================================\n";

    int original = 100;
    int& ref = original; // ref is an alias to original

    std::cout << "  original: " << original << " | ref: " << ref << "\n";
    ref = 250;
    std::cout << "  After ref = 250 -> original is now: " << original << "\n";
    std::cout << "  Address of original: " << &original << "\n";
    std::cout << "  Address of ref:      " << &ref << " (Same address!)\n";
}

void demonstrateConstCorrectness() {
    std::cout << "\n========================================\n";
    std::cout << " 2. CONST CORRECTNESS MATRIX\n";
    std::cout << "========================================\n";

    int a = 10;
    int b = 20;

    // 1. Pointer to const data: Data cannot be changed, pointer CAN move
    const int* ptrToConst = &a;
    ptrToConst = &b; // OK!
    // *ptrToConst = 30; // ERROR! Data is const.

    // 2. Const pointer to mutable data: Pointer is locked, data CAN change
    int* const constPtr = &a;
    *constPtr = 15; // OK!
    // constPtr = &b; // ERROR! Pointer is const.

    // 3. Const pointer to const data: Neither can change
    const int* const immutable = &a;

    std::cout << "  Demonstrated: *ptrToConst=" << *ptrToConst 
              << ", *constPtr=" << *constPtr 
              << ", *immutable=" << *immutable << "\n";
}

void demonstrateScopedEnums() {
    std::cout << "\n========================================\n";
    std::cout << " 3. MODERN SCOPED ENUMS (enum class)\n";
    std::cout << "========================================\n";

    OrderStatus currentOrder = OrderStatus::Pending;
    std::cout << "  Initial State: " << getStatusName(currentOrder) 
              << " (Code: " << static_cast<int>(currentOrder) << ")\n";

    // Transition state
    currentOrder = OrderStatus::Shipped;
    std::cout << "  Updated State: " << getStatusName(currentOrder) 
              << " (Code: " << static_cast<int>(currentOrder) << ")\n";

    // Scoped enums prevent accidental comparison with integers or other enums
    if (currentOrder == OrderStatus::Shipped) {
        std::cout << "  Notification: Your package has departed our warehouse!\n";
    }
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 6: References & Enums        \n";
    std::cout << "======================================================\n";

    demonstrateReferences();
    demonstrateConstCorrectness();
    demonstrateScopedEnums();

    std::cout << "\n[Part 6 Lesson Completed Successfully]\n";
    return 0;
}
