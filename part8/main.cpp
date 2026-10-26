#include <iostream>
#include <string>
#include <iomanip>

/**
 * ============================================================================
 * PART 08: OBJECT-ORIENTED PROGRAMMING: CLASSES & ENCAPSULATION
 * ============================================================================
 * Concepts Covered:
 * 1. Classes, data hiding, and encapsulation.
 * 2. Access specifiers: public vs private.
 * 3. Member initializer lists (preferred over body assignment).
 * 4. Delegating constructors.
 * 5. Destructors and deterministic lifecycle cleanup.
 * 6. Const member functions (read-only member methods).
 * 7. Invariant protection via setter validation.
 * ============================================================================
 */

class BankAccount {
private:
    std::string accountNumber_;
    std::string ownerName_;
    double balance_;

public:
    // Delegating constructor
    BankAccount() : BankAccount("ACC-UNKNOWN", "Guest", 0.0) {}

    // Parameterized constructor with member initializer list
    BankAccount(const std::string& accountNum, const std::string& owner, double initialDeposit)
        : accountNumber_(accountNum),
          ownerName_(owner),
          balance_(initialDeposit >= 0.0 ? initialDeposit : 0.0) {
        std::cout << "  [Constructor] Account " << accountNumber_ 
                  << " created for " << ownerName_ << ".\n";
    }

    // Destructor
    ~BankAccount() {
        std::cout << "  [Destructor] Account " << accountNumber_ 
                  << " closed and cleaned up.\n";
    }

    // Const member functions: guarantee no modification to object state
    const std::string& getAccountNumber() const { return accountNumber_; }
    const std::string& getOwnerName() const { return ownerName_; }
    double getBalance() const { return balance_; }

    // Mutator methods enforcing business invariants
    bool deposit(double amount) {
        if (amount <= 0.0) {
            std::cerr << "  Error: Deposit amount must be positive.\n";
            return false;
        }
        balance_ += amount;
        std::cout << "  Deposited $" << std::fixed << std::setprecision(2) 
                  << amount << ". New Balance: $" << balance_ << "\n";
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0.0) {
            std::cerr << "  Error: Withdrawal amount must be positive.\n";
            return false;
        }
        if (amount > balance_) {
            std::cerr << "  Error: Insufficient funds! Current balance: $" 
                      << balance_ << "\n";
            return false;
        }
        balance_ -= amount;
        std::cout << "  Withdrew $" << std::fixed << std::setprecision(2) 
                  << amount << ". Remaining Balance: $" << balance_ << "\n";
        return true;
    }

    void printStatement() const {
        std::cout << "  +------------------------------------+\n";
        std::cout << "  | Account: " << std::left << std::setw(25) << accountNumber_ << "|\n";
        std::cout << "  | Owner:   " << std::left << std::setw(25) << ownerName_ << "|\n";
        std::cout << "  | Balance: $" << std::left << std::setw(24) << std::fixed 
                  << std::setprecision(2) << balance_ << "|\n";
        std::cout << "  +------------------------------------+\n";
    }
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 8: OOP & Encapsulation       \n";
    std::cout << "======================================================\n";

    std::cout << "\nCreating bank account objects:\n";
    {
        // Scope block to observe constructor and destructor lifecycle
        BankAccount acct1("CHASE-84920", "Alice Johnson", 1500.00);
        acct1.printStatement();

        std::cout << "\nExecuting banking transactions:\n";
        acct1.deposit(350.50);
        acct1.withdraw(200.00);
        acct1.withdraw(5000.00); // Should fail validation

        std::cout << "\nFinal Statement:\n";
        acct1.printStatement();
        std::cout << "\nExiting block scope (destructor will fire immediately):\n";
    }

    std::cout << "\n[Part 8 Lesson Completed Successfully]\n";
    return 0;
}
