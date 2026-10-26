#include <iostream>
#include <string>
#include <iomanip>

/**
 * ============================================================================
 * PART 03: FUNCTIONS, SCOPE & PARAMETER PASSING
 * ============================================================================
 * Concepts Covered:
 * 1. Forward declarations vs Function definitions.
 * 2. Parameter passing mechanisms:
 *    - Pass-by-Value (creates an isolated copy).
 *    - Pass-by-Reference (&) (allows modification of caller variable).
 *    - Pass-by-Const-Reference (const &) (zero-copy read-only efficiency).
 * 3. Function overloading (polymorphic dispatch based on parameter types).
 * 4. Default arguments (fallback parameters).
 * 5. constexpr functions (evaluated at compile time when given constants).
 * 6. Static local variables (persisting state across calls).
 * ============================================================================
 */

// --- 1. Forward Declarations ---
void printHeader(const std::string& title);
void passByValueDemo(int x);
void passByReferenceDemo(int& x);
void passByConstRefDemo(const std::string& largeData);
void incrementCounter();

// --- 2. Function Overloading ---
double calculateTax(double amount, double taxRate = 0.08); // with default argument
double calculateTax(double amount, int fixedSurcharge);

// --- 3. Compile-time evaluation (constexpr) ---
constexpr int computeFactorial(int n) {
    return (n <= 1) ? 1 : (n * computeFactorial(n - 1));
}

// Implementations
void printHeader(const std::string& title) {
    std::cout << "\n========================================\n";
    std::cout << " " << title << "\n";
    std::cout << "========================================\n";
}

void passByValueDemo(int x) {
    x += 50;
    std::cout << "  Inside passByValueDemo: x = " << x << "\n";
}

void passByReferenceDemo(int& x) {
    x += 50;
    std::cout << "  Inside passByReferenceDemo: x = " << x << "\n";
}

void passByConstRefDemo(const std::string& largeData) {
    // zero-copy: directly reads original memory address without copying string
    std::cout << "  Received string of length " << largeData.length() 
              << " without copying bytes.\n";
}

double calculateTax(double amount, double taxRate) {
    return amount * taxRate;
}

double calculateTax(double amount, int fixedSurcharge) {
    return amount + static_cast<double>(fixedSurcharge);
}

void incrementCounter() {
    // static local variable: allocated once, persists for program lifetime
    static int callCount = 0;
    ++callCount;
    std::cout << "  Function callCount is now: " << callCount << "\n";
}

int main() {
    printHeader("PART 3: FUNCTIONS, SCOPE & PARAMETER PASSING");

    // 1. Parameter Passing Modes
    std::cout << "[1] Testing Pass-by-Value vs Pass-by-Reference:\n";
    int num1 = 100;
    std::cout << "  Original num1 before passByValueDemo: " << num1 << "\n";
    passByValueDemo(num1);
    std::cout << "  Original num1 after passByValueDemo:  " << num1 << " (Unchanged!)\n\n";

    int num2 = 100;
    std::cout << "  Original num2 before passByReferenceDemo: " << num2 << "\n";
    passByReferenceDemo(num2);
    std::cout << "  Original num2 after passByReferenceDemo:  " << num2 << " (Modified!)\n\n";

    std::string document = "This is a long string representing hefty data in memory.";
    passByConstRefDemo(document);

    // 2. Overloading & Default Arguments
    printHeader("2. Function Overloading & Default Arguments");
    double orderAmount = 250.00;
    
    // Uses default taxRate = 0.08
    double tax1 = calculateTax(orderAmount);
    // Custom tax rate 12%
    double tax2 = calculateTax(orderAmount, 0.12);
    // Overload with int surcharge
    double totalWithFlatFee = calculateTax(orderAmount, 15);

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "  Default Tax (8%):      $" << tax1 << "\n";
    std::cout << "  Custom Tax (12%):     $" << tax2 << "\n";
    std::cout << "  Total with $15 fee:   $" << totalWithFlatFee << "\n";

    // 3. Compile-time Constexpr
    printHeader("3. Compile-time Constexpr Evaluation");
    constexpr int fact5 = computeFactorial(5);
    std::cout << "  Factorial of 5 (computed at compile-time): " << fact5 << "\n";

    // 4. Static Local Storage
    printHeader("4. Static Local State Persistence");
    incrementCounter();
    incrementCounter();
    incrementCounter();

    std::cout << "\n[Part 3 Lesson Completed Successfully]\n";
    return 0;
}
