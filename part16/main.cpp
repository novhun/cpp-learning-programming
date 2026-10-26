#include <iostream>
#include <string>
#include <stdexcept>
#include <utility>

/**
 * ============================================================================
 * PART 16: EXCEPTION HANDLING & ROBUST ERROR MANAGEMENT
 * ============================================================================
 * Concepts Covered:
 * 1. try, throw, and catch blocks.
 * 2. Standard library exception hierarchy (<stdexcept>).
 * 3. Catching by const reference to prevent slicing.
 * 4. Custom domain-specific exception classes.
 * 5. The noexcept keyword and move constructors.
 * 6. The Strong Exception Safety Guarantee.
 * ============================================================================
 */

// Custom Domain Exception
class InsufficientFundsException : public std::runtime_error {
private:
    double deficitAmount_;

public:
    InsufficientFundsException(const std::string& message, double deficit)
        : std::runtime_error(message), deficitAmount_(deficit) {}

    double getDeficit() const noexcept {
        return deficitAmount_;
    }
};

class SecureVault {
private:
    double balance_;

public:
    explicit SecureVault(double initialBalance) : balance_(initialBalance) {}

    // Demonstrating invariant enforcement via exceptions
    void withdraw(double amount) {
        if (amount <= 0.0) {
            throw std::invalid_argument("Withdrawal amount must be strictly greater than zero!");
        }
        if (amount > balance_) {
            double shortfall = amount - balance_;
            throw InsufficientFundsException("Account overdraft prohibited!", shortfall);
        }

        // Strong Exception Safety: state only mutates after all validations pass
        balance_ -= amount;
        std::cout << "  Withdrawal of $" << amount << " succeeded. New balance: $" << balance_ << "\n";
    }

    double getBalance() const noexcept {
        return balance_;
    }
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 16: Exception Handling       \n";
    std::cout << "======================================================\n";

    SecureVault vault(500.00);

    // Test 1: Successful operation
    std::cout << "\n1. Attempting legitimate withdrawal of $200:\n";
    try {
        vault.withdraw(200.00);
    } catch (const std::exception& e) {
        std::cerr << "  Unexpected error: " << e.what() << "\n";
    }

    // Test 2: Invalid Argument
    std::cout << "\n2. Attempting illegal withdrawal of -$50:\n";
    try {
        vault.withdraw(-50.00);
    } catch (const std::invalid_argument& e) {
        std::cout << "  Caught std::invalid_argument: " << e.what() << "\n";
    }

    // Test 3: Custom Exception Catching
    std::cout << "\n3. Attempting overdraft withdrawal of $1000:\n";
    try {
        vault.withdraw(1000.00);
    } catch (const InsufficientFundsException& e) {
        std::cout << "  Caught InsufficientFundsException: " << e.what() << "\n";
        std::cout << "  Shortfall amount needed: $" << e.getDeficit() << "\n";
    } catch (const std::exception& e) {
        std::cout << "  Generic exception handler: " << e.what() << "\n";
    }

    std::cout << "\nVault final intact balance: $" << vault.getBalance() << "\n";

    std::cout << "\n[Part 16 Lesson Completed Successfully]\n";
    return 0;
}
