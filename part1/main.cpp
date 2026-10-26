#include <iostream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <limits>

/**
 * ============================================================================
 * PART 01: VARIABLES, DATA TYPES, STANDARD I/O & FORMATTING
 * ============================================================================
 * Concepts Covered:
 * 1. Primitive data types and their memory sizes (sizeof).
 * 2. Fixed-width integer types (<cstdint>).
 * 3. Standard console streams: std::cout, std::cin, std::cerr, std::clog.
 * 4. Reading full lines with std::getline() vs word reading with std::cin >>.
 * 5. Formatting console tables with <iomanip> (setw, setprecision, fixed, left, right).
 * 6. Explicit type conversion with static_cast<T>.
 * ============================================================================
 */

void demonstrateDataTypes() {
    std::cout << "\n========================================\n";
    std::cout << " 1. PRIMITIVE DATA TYPES & MEMORY SIZES\n";
    std::cout << "========================================\n";

    int age = 25;
    double accountBalance = 12500.75;
    float interestRate = 3.5f;
    char grade = 'A';
    bool isActive = true;

    // Fixed-width types (recommended for portable code)
    int32_t fixedInt = 100000;
    int64_t largeWorldPopulation = 8000000000LL;
    uint8_t smallByte = 255;

    std::cout << std::left << std::setw(20) << "Type" 
              << std::setw(15) << "Sample Value" 
              << std::setw(10) << "Size (Bytes)" << "\n";
    std::cout << std::string(45, '-') << "\n";

    std::cout << std::left << std::setw(20) << "int" 
              << std::setw(15) << age 
              << std::setw(10) << sizeof(int) << "\n";

    std::cout << std::left << std::setw(20) << "double" 
              << std::setw(15) << accountBalance 
              << std::setw(10) << sizeof(double) << "\n";

    std::cout << std::left << std::setw(20) << "float" 
              << std::setw(15) << interestRate 
              << std::setw(10) << sizeof(float) << "\n";

    std::cout << std::left << std::setw(20) << "char" 
              << std::setw(15) << grade 
              << std::setw(10) << sizeof(char) << "\n";

    std::cout << std::left << std::setw(20) << "bool" 
              << std::setw(15) << (isActive ? "true" : "false") 
              << std::setw(10) << sizeof(bool) << "\n";

    std::cout << std::left << std::setw(20) << "int32_t" 
              << std::setw(15) << fixedInt 
              << std::setw(10) << sizeof(int32_t) << "\n";

    std::cout << std::left << std::setw(20) << "int64_t" 
              << std::setw(15) << largeWorldPopulation 
              << std::setw(10) << sizeof(int64_t) << "\n";

    std::cout << std::left << std::setw(20) << "uint8_t" 
              << std::setw(15) << static_cast<int>(smallByte) 
              << std::setw(10) << sizeof(uint8_t) << "\n";
}

void demonstrateTypeCasting() {
    std::cout << "\n========================================\n";
    std::cout << " 2. SAFE TYPE CASTING (static_cast)\n";
    std::cout << "========================================\n";

    int examCount = 5;
    int testScore = 482;
    double badAverage = testScore / examCount; // Truncated!
    double goodAverage = static_cast<double>(testScore) / static_cast<double>(examCount);

    std::cout << "Without static_cast (482 / 5): " << badAverage << " (Data loss!)\n";
    std::cout << "With static_cast<double>:      " << std::fixed << std::setprecision(2) 
              << goodAverage << " (Exact!)\n";
}

void demonstrateFormattedTable() {
    std::cout << "\n========================================\n";
    std::cout << " 3. ADVANCED OUTPUT FORMATTING (<iomanip>)\n";
    std::cout << "========================================\n";

    std::cout << std::left << std::setw(10) << "ID" 
              << std::setw(20) << "Item Name" 
              << std::right << std::setw(10) << "Qty" 
              << std::setw(12) << "Price ($)" 
              << std::setw(14) << "Total ($)" << "\n";
    std::cout << std::string(66, '=') << "\n";

    std::cout << std::fixed << std::setprecision(2);

    std::cout << std::left << std::setw(10) << "SKU-001" 
              << std::setw(20) << "Mechanical Keyboard" 
              << std::right << std::setw(10) << 3 
              << std::setw(12) << 89.99 
              << std::setw(14) << (3 * 89.99) << "\n";

    std::cout << std::left << std::setw(10) << "SKU-002" 
              << std::setw(20) << "Gaming Mouse" 
              << std::right << std::setw(10) << 5 
              << std::setw(12) << 49.50 
              << std::setw(14) << (5 * 49.50) << "\n";

    std::cout << std::left << std::setw(10) << "SKU-003" 
              << std::setw(20) << "4K Monitor 27-inch" 
              << std::right << std::setw(10) << 1 
              << std::setw(12) << 349.00 
              << std::setw(14) << (1 * 349.00) << "\n";

    std::cout << std::string(66, '-') << "\n";
}

void interactiveStoreReceipt() {
    std::cout << "\n========================================\n";
    std::cout << " 4. INTERACTIVE PRODUCT RECEIPT GENERATOR\n";
    std::cout << "========================================\n";

    std::string customerName;
    std::string productName;
    int quantity = 0;
    double unitPrice = 0.0;

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin, customerName);

    std::cout << "Enter Product Name: ";
    std::getline(std::cin, productName);

    std::cout << "Enter Quantity: ";
    while (!(std::cin >> quantity) || quantity <= 0) {
        std::cout << "Invalid input. Please enter a positive integer: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Enter Unit Price ($): ";
    while (!(std::cin >> unitPrice) || unitPrice < 0.0) {
        std::cout << "Invalid input. Please enter a valid non-negative price: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Flush newline character left in input stream
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    double subtotal = static_cast<double>(quantity) * unitPrice;
    double taxRate = 0.08; // 8% sales tax
    double taxAmount = subtotal * taxRate;
    double grandTotal = subtotal + taxAmount;

    // Output formatted receipt
    std::cout << "\n" << std::string(40, '*') << "\n";
    std::cout << "           OFFICIAL RECEIPT            \n";
    std::cout << std::string(40, '*') << "\n";
    std::cout << std::left << std::setw(18) << "Customer:" << customerName << "\n";
    std::cout << std::left << std::setw(18) << "Product:"  << productName << "\n";
    std::cout << std::left << std::setw(18) << "Quantity:" << quantity << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(18) << "Unit Price:" << "$" << unitPrice << "\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << std::left << std::setw(18) << "Subtotal:"   << "$" << subtotal << "\n";
    std::cout << std::left << std::setw(18) << "Tax (8%):"   << "$" << taxAmount << "\n";
    std::cout << std::left << std::setw(18) << "Grand Total:" << "$" << grandTotal << "\n";
    std::cout << std::string(40, '*') << "\n";
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 1: Variables, Types & I/O    \n";
    std::cout << "======================================================\n";

    demonstrateDataTypes();
    demonstrateTypeCasting();
    demonstrateFormattedTable();
    interactiveStoreReceipt();

    std::cout << "\n[Part 1 Lesson Completed Successfully]\n";
    return 0;
}
