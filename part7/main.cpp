#include <iostream>
#include <string>
#include <iomanip>
#include <vector>

/**
 * ============================================================================
 * PART 07: STRUCTURES, MEMORY LAYOUT & STRUCTURED BINDINGS
 * ============================================================================
 * Concepts Covered:
 * 1. Struct declarations and member variables.
 * 2. Struct member functions (methods) and default values.
 * 3. Memory alignment, padding, and struct memory footprints.
 * 4. Aggregate initialization.
 * 5. C++17 Structured Bindings: auto [a, b, c] = structInstance.
 * 6. Product catalog record management.
 * ============================================================================
 */

// Memory layout demonstration struct
struct MemoryLayoutDemo {
    char flag1;    // 1 byte
    // 3 bytes padding here for 4-byte int alignment!
    int value;     // 4 bytes
    char flag2;    // 1 byte
    // 7 bytes padding here for 8-byte double alignment!
    double ratio;  // 8 bytes
};

// Clean domain struct for an Inventory Product
struct ProductRecord {
    int id;
    std::string name;
    double unitPrice;
    int stockQuantity;

    // Member function inside struct
    double computeInventoryValue() const {
        return unitPrice * static_cast<double>(stockQuantity);
    }

    void displayRow() const {
        std::cout << "  " << std::left << std::setw(6) << id
                  << std::setw(22) << name
                  << std::right << std::setw(12) << std::fixed << std::setprecision(2) << unitPrice
                  << std::setw(10) << stockQuantity
                  << std::setw(14) << computeInventoryValue() << "\n";
    }
};

void demonstrateStructBasics() {
    std::cout << "\n========================================\n";
    std::cout << " 1. STRUCT RECORD INVENTORY\n";
    std::cout << "========================================\n";

    // Aggregate initialization
    ProductRecord p1{101, "Wireless Keyboard", 49.99, 35};
    ProductRecord p2{102, "USB-C Fast Charger", 19.50, 80};
    ProductRecord p3{103, "UltraWide Monitor", 429.00, 12};

    std::cout << "  " << std::left << std::setw(6) << "ID"
              << std::setw(22) << "Product Name"
              << std::right << std::setw(12) << "Price ($)"
              << std::setw(10) << "Stock"
              << std::setw(14) << "Total Val ($)\n";
    std::cout << "  " << std::string(64, '-') << "\n";

    p1.displayRow();
    p2.displayRow();
    p3.displayRow();
}

void demonstrateStructuredBindings() {
    std::cout << "\n========================================\n";
    std::cout << " 2. C++17 STRUCTURED BINDINGS\n";
    std::cout << "========================================\n";

    ProductRecord featured{201, "Noise-Cancelling Headphones", 199.99, 15};

    // Modern C++17 structured binding unpacks members directly!
    auto [prodId, prodName, price, qty] = featured;

    std::cout << "  Unpacked Product ID:       " << prodId << "\n";
    std::cout << "  Unpacked Name:             " << prodName << "\n";
    std::cout << "  Unpacked Unit Price:       $" << price << "\n";
    std::cout << "  Unpacked Stock Units:      " << qty << "\n";
}

void demonstrateMemoryAlignment() {
    std::cout << "\n========================================\n";
    std::cout << " 3. MEMORY PADDING & ALIGNMENT\n";
    std::cout << "========================================\n";

    std::cout << "  sizeof(char):   " << sizeof(char) << " byte\n";
    std::cout << "  sizeof(int):    " << sizeof(int) << " bytes\n";
    std::cout << "  sizeof(double): " << sizeof(double) << " bytes\n";
    std::cout << "  Pure sum: 1 + 4 + 1 + 8 = 14 bytes.\n";
    std::cout << "  Actual sizeof(MemoryLayoutDemo): " 
              << sizeof(MemoryLayoutDemo) << " bytes (Compiler padded to 24 bytes for 64-bit alignment!)\n";
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 7: Structs & Bindings        \n";
    std::cout << "======================================================\n";

    demonstrateStructBasics();
    demonstrateStructuredBindings();
    demonstrateMemoryAlignment();

    std::cout << "\n[Part 7 Lesson Completed Successfully]\n";
    return 0;
}
