#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

/**
 * ============================================================================
 * PART 09: OOP: INHERITANCE, POLYMORPHISM & VIRTUAL FUNCTIONS
 * ============================================================================
 * Concepts Covered:
 * 1. Base classes and Derived classes.
 * 2. Virtual functions and runtime dynamic dispatch (VTable).
 * 3. The override and final keywords.
 * 4. Pure virtual functions (= 0) and Abstract Base Classes (Interfaces).
 * 5. Virtual destructors (mandatory for polymorphic base classes).
 * 6. Polymorphic payment processor system demo.
 * ============================================================================
 */

// Abstract Base Class (Interface)
class PaymentProcessor {
protected:
    std::string gatewayName_;

public:
    explicit PaymentProcessor(std::string gateway) : gatewayName_(std::move(gateway)) {}

    // Crucial: Base classes with virtual functions MUST have virtual destructors!
    virtual ~PaymentProcessor() {
        std::cout << "    [~PaymentProcessor] Cleaned up base gateway: " << gatewayName_ << "\n";
    }

    // Pure virtual function: subclasses MUST implement this
    virtual bool processPayment(double amount) = 0;

    // Concrete virtual function with default implementation
    virtual void printReceiptHeader() const {
        std::cout << "  Payment Gateway: " << gatewayName_ << "\n";
    }

    const std::string& getGatewayName() const { return gatewayName_; }
};

// Derived Class 1: Credit Card
class CreditCardPayment final : public PaymentProcessor {
private:
    std::string maskedCardNumber_;

public:
    CreditCardPayment(std::string cardNumber)
        : PaymentProcessor("Stripe Credit Services"),
          maskedCardNumber_("****-****-****-" + cardNumber.substr(cardNumber.length() - 4)) {}

    ~CreditCardPayment() override {
        std::cout << "    [~CreditCardPayment] Securely wiped card session memory.\n";
    }

    bool processPayment(double amount) override {
        std::cout << "  [CreditCard] Charging $" << std::fixed << std::setprecision(2) 
                  << amount << " to Card " << maskedCardNumber_ << " ... Approved!\n";
        return true;
    }
};

// Derived Class 2: PayPal
class PayPalPayment final : public PaymentProcessor {
private:
    std::string accountEmail_;

public:
    PayPalPayment(std::string email)
        : PaymentProcessor("PayPal Express Checkout"),
          accountEmail_(std::move(email)) {}

    ~PayPalPayment() override {
        std::cout << "    [~PayPalPayment] Closed PayPal OAuth session.\n";
    }

    bool processPayment(double amount) override {
        std::cout << "  [PayPal] Sending invoice for $" << std::fixed << std::setprecision(2) 
                  << amount << " to user " << accountEmail_ << " ... Confirmed!\n";
        return true;
    }
};

// Derived Class 3: Crypto
class CryptoPayment final : public PaymentProcessor {
private:
    std::string walletAddress_;

public:
    CryptoPayment(std::string wallet)
        : PaymentProcessor("Web3 Lightning Node"),
          walletAddress_(std::move(wallet)) {}

    ~CryptoPayment() override {
        std::cout << "    [~CryptoPayment] Disconnected Web3 RPC socket.\n";
    }

    bool processPayment(double amount) override {
        std::cout << "  [Crypto] Broadcasting tx of $" << std::fixed << std::setprecision(2) 
                  << amount << " to wallet " << walletAddress_ << " ... Mined on block!\n";
        return true;
    }
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 9: Inheritance & Polymorphism\n";
    std::cout << "======================================================\n";

    std::cout << "\n1. Demonstrating Polymorphic Payment Dispatch:\n\n";

    // Polymorphic collection: storing pointers to base class
    std::vector<std::unique_ptr<PaymentProcessor>> paymentGateways;
    paymentGateways.push_back(std::make_unique<CreditCardPayment>("4532119988441234"));
    paymentGateways.push_back(std::make_unique<PayPalPayment>("customer@company.com"));
    paymentGateways.push_back(std::make_unique<CryptoPayment>("0x71C...B29"));

    double billAmount = 149.50;

    // Dynamic runtime dispatch through base class interface
    for (const auto& gateway : paymentGateways) {
        gateway->printReceiptHeader();
        gateway->processPayment(billAmount);
        std::cout << "  --------------------------------------------------\n";
    }

    std::cout << "\n2. Cleaning up polymorphic objects (Observing Virtual Destructors):\n";
    paymentGateways.clear(); // Releases unique_ptrs, firing derived then base destructors!

    std::cout << "\n[Part 9 Lesson Completed Successfully]\n";
    return 0;
}
