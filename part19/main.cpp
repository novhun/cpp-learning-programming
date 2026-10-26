#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <iomanip>

/**
 * ============================================================================
 * PART 19: DESIGN PATTERNS IN MODERN C++
 * ============================================================================
 * Concepts Covered:
 * 1. Meyers' Singleton (Thread-safe, lazy-initialized in C++11+).
 * 2. Factory Method Pattern (Decoupling instantiation from usage).
 * 3. Strategy Pattern (Interchangeable runtime discount algorithms).
 * 4. Observer Pattern (Decoupled event broadcasting).
 * ============================================================================
 */

// --- 1. MEYERS' SINGLETON PATTERN ---
class AppConfig {
private:
    std::string appName_ = "Enterprise POS Engine";
    std::string version_ = "2.4.0";

    // Private constructor prevents external instantiation
    AppConfig() {
        std::cout << "  [Singleton] AppConfig initialized once.\n";
    }

public:
    // Delete copy and move semantics
    AppConfig(const AppConfig&) = delete;
    AppConfig& operator=(const AppConfig&) = delete;

    // Thread-safe Meyer's Singleton: guaranteed by C++11 standard
    static AppConfig& getInstance() {
        static AppConfig instance;
        return instance;
    }

    const std::string& getAppName() const { return appName_; }
    const std::string& getVersion() const { return version_; }
};

// --- 2. STRATEGY PATTERN (Discount Strategies) ---
class IDiscountStrategy {
public:
    virtual ~IDiscountStrategy() = default;
    virtual double applyDiscount(double rawAmount) const = 0;
    virtual std::string getStrategyName() const = 0;
};

class NoDiscountStrategy : public IDiscountStrategy {
public:
    double applyDiscount(double rawAmount) const override { return rawAmount; }
    std::string getStrategyName() const override { return "Standard Price (0%)"; }
};

class VIPDiscountStrategy : public IDiscountStrategy {
public:
    double applyDiscount(double rawAmount) const override { return rawAmount * 0.85; }
    std::string getStrategyName() const override { return "VIP Member (15% OFF)"; }
};

class HolidaySaleStrategy : public IDiscountStrategy {
public:
    double applyDiscount(double rawAmount) const override { return rawAmount * 0.70; }
    std::string getStrategyName() const override { return "Holiday Clearance (30% OFF)"; }
};

// --- 3. FACTORY METHOD PATTERN ---
enum class DiscountType { Standard, VIP, HolidaySale };

class DiscountStrategyFactory {
public:
    static std::unique_ptr<IDiscountStrategy> createStrategy(DiscountType type) {
        switch (type) {
            case DiscountType::Standard:
                return std::make_unique<NoDiscountStrategy>();
            case DiscountType::VIP:
                return std::make_unique<VIPDiscountStrategy>();
            case DiscountType::HolidaySale:
                return std::make_unique<HolidaySaleStrategy>();
        }
        return std::make_unique<NoDiscountStrategy>();
    }
};

// --- 4. OBSERVER PATTERN (Order Event Listener) ---
class IOrderObserver {
public:
    virtual ~IOrderObserver() = default;
    virtual void onOrderPlaced(const std::string& orderId, double finalAmount) = 0;
};

class EmailNotificationService : public IOrderObserver {
public:
    void onOrderPlaced(const std::string& orderId, double finalAmount) override {
        std::cout << "  [EmailService] Sent confirmation email for order " 
                  << orderId << " ($" << finalAmount << ").\n";
    }
};

class WarehouseDispatchService : public IOrderObserver {
public:
    void onOrderPlaced(const std::string& orderId, double /*finalAmount*/) override {
        std::cout << "  [WarehouseService] Printing packing slip for order " 
                  << orderId << ".\n";
    }
};

class OrderSubject {
private:
    std::vector<std::shared_ptr<IOrderObserver>> observers_;

public:
    void subscribe(std::shared_ptr<IOrderObserver> obs) {
        observers_.push_back(obs);
    }

    void notify(const std::string& orderId, double amount) {
        for (const auto& obs : observers_) {
            obs->onOrderPlaced(orderId, amount);
        }
    }
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 19: Design Patterns          \n";
    std::cout << "======================================================\n";

    // 1. Singleton Demo
    std::cout << "\n1. Singleton Pattern:\n";
    AppConfig& config = AppConfig::getInstance();
    std::cout << "  App: " << config.getAppName() << " (v" << config.getVersion() << ")\n";

    // 2. Factory & Strategy Demo
    std::cout << "\n2. Factory & Strategy Patterns:\n";
    double orderTotal = 200.00;

    auto strategy = DiscountStrategyFactory::createStrategy(DiscountType::VIP);
    double discountedAmount = strategy->applyDiscount(orderTotal);

    std::cout << "  Strategy: " << strategy->getStrategyName() << "\n";
    std::cout << "  Original: $" << std::fixed << std::setprecision(2) << orderTotal 
              << " -> Final: $" << discountedAmount << "\n";

    // 3. Observer Pattern Demo
    std::cout << "\n3. Observer Pattern:\n";
    OrderSubject orderManager;
    orderManager.subscribe(std::make_shared<EmailNotificationService>());
    orderManager.subscribe(std::make_shared<WarehouseDispatchService>());

    std::cout << "  Broadcasting new order placement event:\n";
    orderManager.notify("ORD-98421", discountedAmount);

    std::cout << "\n[Part 19 Lesson Completed Successfully]\n";
    return 0;
}
