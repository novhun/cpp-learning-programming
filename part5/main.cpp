#include <iostream>
#include <iomanip>
#include <cstddef>

/**
 * ============================================================================
 * PART 05: POINTERS, MEMORY ADDRESSES & DYNAMIC ALLOCATION
 * ============================================================================
 * Concepts Covered:
 * 1. Memory addresses (&) and pointer dereferencing (*).
 * 2. nullptr safety.
 * 3. Pointer arithmetic & traversal.
 * 4. Stack vs Heap (Free Store) architecture.
 * 5. Dynamic memory allocation: new and delete.
 * 6. Dynamic array allocation: new[] and delete[].
 * 7. Preventing memory leaks and dangling pointers.
 * ============================================================================
 */

void demonstratePointerBasics() {
    std::cout << "\n========================================\n";
    std::cout << " 1. POINTER BASICS & DEREFERENCING\n";
    std::cout << "========================================\n";

    int targetValue = 42;
    int* ptr = &targetValue; // ptr holds the memory address of targetValue

    std::cout << "  Value of targetValue:        " << targetValue << "\n";
    std::cout << "  Address of targetValue (&):  " << &targetValue << "\n";
    std::cout << "  Value stored in ptr:         " << ptr << "\n";
    std::cout << "  Value pointed to (*ptr):     " << *ptr << "\n";

    // Modifying the original variable through the pointer
    *ptr = 99;
    std::cout << "  After '*ptr = 99', targetValue is now: " << targetValue << "\n";

    // Nullptr check
    int* nullPointer = nullptr;
    if (nullPointer == nullptr) {
        std::cout << "  nullPointer safely confirmed to be nullptr.\n";
    }
}

void demonstratePointerArithmetic() {
    std::cout << "\n========================================\n";
    std::cout << " 2. POINTER ARITHMETIC\n";
    std::cout << "========================================\n";

    int numbers[5] = {10, 20, 30, 40, 50};
    int* startPtr = numbers; // Implicit decay to pointer to first element

    std::cout << "  Traversing array using pointer arithmetic (*(startPtr + i)):\n  ";
    for (int i = 0; i < 5; ++i) {
        std::cout << *(startPtr + i) << " ";
    }
    std::cout << "\n";

    // Memory stride difference
    std::cout << "  Address of numbers[0]: " << static_cast<void*>(startPtr) << "\n";
    std::cout << "  Address of numbers[1]: " << static_cast<void*>(startPtr + 1) 
              << " (+4 bytes for 32-bit int)\n";
}

void demonstrateDynamicMemory() {
    std::cout << "\n========================================\n";
    std::cout << " 3. DYNAMIC MEMORY ALLOCATION (HEAP)\n";
    std::cout << "========================================\n";

    // Allocate a single double on the heap
    double* dynamicPrice = new double(149.99);
    std::cout << "  Dynamically allocated price on Heap: $" << *dynamicPrice << "\n";

    // Free memory and prevent dangling pointer
    delete dynamicPrice;
    dynamicPrice = nullptr; // Reset to nullptr to avoid accidental reuse

    // Dynamic array allocation based on runtime size
    int arraySize = 4;
    int* dynamicScores = new int[static_cast<std::size_t>(arraySize)];

    dynamicScores[0] = 88;
    dynamicScores[1] = 92;
    dynamicScores[2] = 79;
    dynamicScores[3] = 95;

    std::cout << "  Dynamic heap array contents: ";
    for (int i = 0; i < arraySize; ++i) {
        std::cout << dynamicScores[i] << " ";
    }
    std::cout << "\n";

    // Crucial: Use delete[] for arrays, NOT delete!
    delete[] dynamicScores;
    dynamicScores = nullptr;
    std::cout << "  Successfully freed dynamic array memory.\n";
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 5: Pointers & Dynamic Memory \n";
    std::cout << "======================================================\n";

    demonstratePointerBasics();
    demonstratePointerArithmetic();
    demonstrateDynamicMemory();

    std::cout << "\n[Part 5 Lesson Completed Successfully]\n";
    return 0;
}
