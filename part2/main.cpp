#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

/**
 * ============================================================================
 * PART 02: CONTROL FLOW, CONDITIONALS & LOOPS
 * ============================================================================
 * Concepts Covered:
 * 1. Branching: if, else if, else and nested conditions.
 * 2. Ternary operator (condition ? exprTrue : exprFalse).
 * 3. Multi-way branching: switch, case, break, and default.
 * 4. Loops: while, do-while, counting for, and range-based for.
 * 5. Loop jumps: break (early termination) and continue (skip iteration).
 * 6. Real-World Project: Interactive Multi-Item POS Terminal with Tiered Discounts.
 * ============================================================================
 */

void demonstrateConditionals() {
    std::cout << "\n========================================\n";
    std::cout << " 1. CONDITIONALS & TERNARY OPERATOR\n";
    std::cout << "========================================\n";

    int score = 85;
    char letterGrade;

    if (score >= 90) {
        letterGrade = 'A';
    } else if (score >= 80) {
        letterGrade = 'B';
    } else if (score >= 70) {
        letterGrade = 'C';
    } else if (score >= 60) {
        letterGrade = 'D';
    } else {
        letterGrade = 'F';
    }

    std::cout << "Score: " << score << " -> Grade: " << letterGrade << "\n";

    // Ternary operator: concise inline conditional
    bool isPassed = (score >= 60);
    std::string status = isPassed ? "Passed" : "Failed";
    std::cout << "Academic Status: " << status << "\n";
}

void demonstrateSwitchCase() {
    std::cout << "\n========================================\n";
    std::cout << " 2. SWITCH-CASE STATEMENTS\n";
    std::cout << "========================================\n";

    int membershipTier = 2; // 1: Bronze, 2: Silver, 3: Gold, 4: Platinum
    double discountPercentage = 0.0;

    switch (membershipTier) {
        case 1:
            discountPercentage = 5.0;
            std::cout << "Tier: Bronze (5% discount)\n";
            break;
        case 2:
            discountPercentage = 10.0;
            std::cout << "Tier: Silver (10% discount)\n";
            break;
        case 3:
            discountPercentage = 15.0;
            std::cout << "Tier: Gold (15% discount)\n";
            break;
        case 4:
            discountPercentage = 25.0;
            std::cout << "Tier: Platinum (25% discount)\n";
            break;
        default:
            discountPercentage = 0.0;
            std::cout << "Tier: Standard Guest (No discount)\n";
            break;
    }

    std::cout << "Applied member discount: " << discountPercentage << "%\n";
}

void demonstrateLoops() {
    std::cout << "\n========================================\n";
    std::cout << " 3. LOOPS (for, while, do-while)\n";
    std::cout << "========================================\n";

    // Traditional for loop: known number of iterations
    std::cout << "Counting for-loop (even numbers 2 to 10):\n";
    for (int i = 2; i <= 10; i += 2) {
        std::cout << i << " ";
    }
    std::cout << "\n";

    // While loop: condition evaluated before each iteration
    std::cout << "While-loop (powers of 2 under 100):\n";
    int power = 1;
    while (power < 100) {
        std::cout << power << " ";
        power *= 2;
    }
    std::cout << "\n";

    // Loop control: continue and break
    std::cout << "Demonstrating continue (skip 3) & break (stop at 7):\n";
    for (int i = 1; i <= 10; ++i) {
        if (i == 3) {
            continue; // Skip 3
        }
        if (i == 7) {
            break;    // Terminate loop
        }
        std::cout << i << " ";
    }
    std::cout << "\n";
}

void runInteractivePOSTerminal() {
    std::cout << "\n========================================\n";
    std::cout << " 4. MULTI-ITEM POS CHECKOUT TERMINAL\n";
    std::cout << "========================================\n";

    double runningSubtotal = 0.0;
    int totalItems = 0;
    char addMore = 'n';

    do {
        std::string itemName;
        int qty = 0;
        double price = 0.0;

        std::cout << "\nEnter product name: ";
        std::getline(std::cin, itemName);

        std::cout << "Enter quantity: ";
        while (!(std::cin >> qty) || qty <= 0) {
            std::cout << "Please enter a positive integer: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Enter unit price ($): ";
        while (!(std::cin >> price) || price < 0.0) {
            std::cout << "Please enter a valid price: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        double lineTotal = static_cast<double>(qty) * price;
        runningSubtotal += lineTotal;
        totalItems += qty;

        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Added: " << itemName << " x " << qty 
                  << " @ $" << price << " = $" << lineTotal << "\n";

        std::cout << "Add another item? (y/n): ";
        std::cin >> addMore;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (addMore == 'y' || addMore == 'Y');

    // Calculate tiered bulk discount based on total items purchased
    double discountRate = 0.0;
    if (totalItems >= 50) {
        discountRate = 0.20; // 20% discount
    } else if (totalItems >= 20) {
        discountRate = 0.10; // 10% discount
    } else if (totalItems >= 10) {
        discountRate = 0.05; // 5% discount
    }

    double discountAmount = runningSubtotal * discountRate;
    double discountedSubtotal = runningSubtotal - discountAmount;
    double taxRate = 0.07; // 7% sales tax
    double taxAmount = discountedSubtotal * taxRate;
    double grandTotal = discountedSubtotal + taxAmount;

    // Display formatted final receipt
    std::cout << "\n============================================\n";
    std::cout << "            FINAL STORE RECEIPT             \n";
    std::cout << "============================================\n";
    std::cout << std::left << std::setw(24) << "Total Units Purchased:" 
              << std::right << std::setw(15) << totalItems << "\n";
    std::cout << std::left << std::setw(24) << "Gross Subtotal:" 
              << std::right << std::setw(15) << ("$" + std::to_string(static_cast<int>(runningSubtotal)) + "." + 
                 std::to_string(static_cast<int>((runningSubtotal - static_cast<int>(runningSubtotal)) * 100))) << "\n";
    
    std::cout << std::left << std::setw(24) << "Volume Discount (" + std::to_string(static_cast<int>(discountRate * 100)) + "%):"
              << std::right << std::setw(14) << "-$" << std::fixed << std::setprecision(2) << discountAmount << "\n";
    std::cout << std::left << std::setw(24) << "Taxable Amount:" 
              << std::right << std::setw(14) << "$" << discountedSubtotal << "\n";
    std::cout << std::left << std::setw(24) << "Sales Tax (7%):" 
              << std::right << std::setw(14) << "$" << taxAmount << "\n";
    std::cout << std::string(44, '-') << "\n";
    std::cout << std::left << std::setw(24) << "TOTAL PAYABLE:" 
              << std::right << std::setw(14) << "$" << grandTotal << "\n";
    std::cout << "============================================\n";
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 2: Control Flow & Loops      \n";
    std::cout << "======================================================\n";

    demonstrateConditionals();
    demonstrateSwitchCase();
    demonstrateLoops();
    runInteractivePOSTerminal();

    std::cout << "\n[Part 2 Lesson Completed Successfully]\n";
    return 0;
}
