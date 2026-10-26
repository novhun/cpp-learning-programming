#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <optional>
#include <stdexcept>
#include <limits>
#include <chrono>

/**
 * ============================================================================
 * PART 20: CAPSTONE PROJECT: ENTERPRISE POS & INVENTORY SYSTEM
 * ============================================================================
 * Concepts Integrated:
 * 1. Clean Modern C++ Architecture (C++17).
 * 2. RAII & Smart Pointers (std::unique_ptr).
 * 3. STL Containers: unordered_map, vector, optional.
 * 4. STL Algorithms & Lambda expressions.
 * 5. Robust Exception Handling (Custom domain exceptions).
 * 6. File I/O & Receipt Export (fstream).
 * 7. Strategy Design Pattern for dynamic discounts.
 * 8. Formatted terminal output with clean receipt generation.
 * ============================================================================
 */

// Custom Domain Exceptions
class POSException : public std::runtime_error {
public:
    explicit POSException(const std::string& msg) : std::runtime_error(msg) {}
};

class ProductNotFoundException : public POSException {
public:
    explicit ProductNotFoundException(const std::string& sku)
        : POSException("Product SKU '" + sku + "' not found in inventory!") {}
};

class InsufficientStockException : public POSException {
public:
    InsufficientStockException(const std::string& sku, int requested, int available)
        : POSException("SKU '" + sku + "' insufficient stock! Requested: " + 
                       std::to_string(requested) + ", Available: " + std::to_string(available)) {}
};

// Domain Model: Product
class Product {
private:
    std::string sku_;
    std::string name_;
    double price_;
    int stockQuantity_;

public:
    Product(std::string sku, std::string name, double price, int stock)
        : sku_(std::move(sku)), name_(std::move(name)), price_(price), stockQuantity_(stock) {}

    const std::string& getSku() const { return sku_; }
    const std::string& getName() const { return name_; }
    double getPrice() const { return price_; }
    int getStock() const { return stockQuantity_; }

    void deductStock(int quantity) {
        if (quantity > stockQuantity_) {
            throw InsufficientStockException(sku_, quantity, stockQuantity_);
        }
        stockQuantity_ -= quantity;
    }

    void restock(int quantity) {
        if (quantity > 0) {
            stockQuantity_ += quantity;
        }
    }
};

// Cart Line Item
struct CartItem {
    std::shared_ptr<Product> product;
    int quantity;

    double getLineTotal() const {
        return product->getPrice() * static_cast<double>(quantity);
    }
};

// Strategy Pattern for Discounts
class IDiscountPolicy {
public:
    virtual ~IDiscountPolicy() = default;
    virtual double calculateDiscount(double subtotal, int totalItemCount) const = 0;
    virtual std::string getPolicyDescription() const = 0;
};

class StandardDiscountPolicy : public IDiscountPolicy {
public:
    double calculateDiscount(double /*subtotal*/, int /*totalItemCount*/) const override {
        return 0.0;
    }
    std::string getPolicyDescription() const override {
        return "Standard Retail (No Discount)";
    }
};

class TieredBulkDiscountPolicy : public IDiscountPolicy {
public:
    double calculateDiscount(double subtotal, int totalItemCount) const override {
        if (totalItemCount >= 50) return subtotal * 0.20; // 20%
        if (totalItemCount >= 20) return subtotal * 0.10; // 10%
        if (totalItemCount >= 10) return subtotal * 0.05; // 5%
        return 0.0;
    }
    std::string getPolicyDescription() const override {
        return "Bulk Volume Tier (5% to 20%)";
    }
};

class VIPMemberDiscountPolicy : public IDiscountPolicy {
public:
    double calculateDiscount(double subtotal, int /*totalItemCount*/) const override {
        return subtotal * 0.15; // Flat 15% VIP discount
    }
    std::string getPolicyDescription() const override {
        return "VIP Membership Club (15% Flat Discount)";
    }
};

// Store Inventory Management System
class InventoryManager {
private:
    std::unordered_map<std::string, std::shared_ptr<Product>> catalog_;

public:
    void addProduct(const std::string& sku, const std::string& name, double price, int stock) {
        catalog_[sku] = std::make_shared<Product>(sku, name, price, stock);
    }

    std::shared_ptr<Product> getProduct(const std::string& sku) {
        auto it = catalog_.find(sku);
        if (it == catalog_.end()) {
            throw ProductNotFoundException(sku);
        }
        return it->second;
    }

    void displayCatalog() const {
        std::cout << "\n+--------+--------------------------------+------------+--------+\n";
        std::cout << "| SKU    | Product Name                   | Price ($)  | Stock  |\n";
        std::cout << "+--------+--------------------------------+------------+--------+\n";
        std::cout << std::fixed << std::setprecision(2);
        for (const auto& entry : catalog_) {
            const auto& sku = entry.first;
            const auto& prod = entry.second;
            std::cout << "| " << std::left << std::setw(6) << sku 
                      << " | " << std::setw(30) << prod->getName()
                      << " | " << std::right << std::setw(10) << prod->getPrice()
                      << " | " << std::setw(6) << prod->getStock() << " |\n";
        }
        std::cout << "+--------+--------------------------------+------------+--------+\n";
    }
};

// Shopping Cart & Order Checkout
class ShoppingCart {
private:
    std::vector<CartItem> items_;
    std::unique_ptr<IDiscountPolicy> discountPolicy_;

public:
    ShoppingCart() : discountPolicy_(std::make_unique<TieredBulkDiscountPolicy>()) {}

    void setDiscountPolicy(std::unique_ptr<IDiscountPolicy> policy) {
        discountPolicy_ = std::move(policy);
    }

    void addItem(std::shared_ptr<Product> product, int quantity) {
        if (quantity <= 0) {
            throw POSException("Quantity to add must be positive!");
        }
        if (quantity > product->getStock()) {
            throw InsufficientStockException(product->getSku(), quantity, product->getStock());
        }

        // Check if item already exists in cart
        for (auto& item : items_) {
            if (item.product->getSku() == product->getSku()) {
                if (item.quantity + quantity > product->getStock()) {
                    throw InsufficientStockException(product->getSku(), item.quantity + quantity, product->getStock());
                }
                item.quantity += quantity;
                return;
            }
        }

        items_.push_back({product, quantity});
    }

    void clear() {
        items_.clear();
    }

    bool isEmpty() const {
        return items_.empty();
    }

    void checkoutAndGenerateReceipt(const std::string& customerName, const std::string& receiptFile) {
        if (items_.empty()) {
            std::cerr << "  Cart is empty! Nothing to checkout.\n";
            return;
        }

        double subtotal = 0.0;
        int totalUnits = 0;

        for (const auto& item : items_) {
            subtotal += item.getLineTotal();
            totalUnits += item.quantity;
        }

        double discount = discountPolicy_->calculateDiscount(subtotal, totalUnits);
        double taxableSubtotal = subtotal - discount;
        double tax = taxableSubtotal * 0.08; // 8% tax
        double grandTotal = taxableSubtotal + tax;

        // Deduct actual stock from inventory
        for (auto& item : items_) {
            item.product->deductStock(item.quantity);
        }

        // Output to both console and disk file
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2);
        ss << "\n=======================================================\n";
        ss << "            ENTERPRISE STORE OFFICIAL RECEIPT          \n";
        ss << "=======================================================\n";
        ss << "Customer: " << customerName << "\n";
        ss << "Discount Policy: " << discountPolicy_->getPolicyDescription() << "\n";
        ss << "-------------------------------------------------------\n";
        ss << std::left << std::setw(25) << "Item"
           << std::right << std::setw(6) << "Qty"
           << std::setw(11) << "Unit ($)"
           << std::setw(12) << "Total ($)\n";
        ss << "-------------------------------------------------------\n";

        for (const auto& item : items_) {
            ss << std::left << std::setw(25) << item.product->getName()
               << std::right << std::setw(6) << item.quantity
               << std::setw(11) << item.product->getPrice()
               << std::setw(12) << item.getLineTotal() << "\n";
        }

        ss << "-------------------------------------------------------\n";
        ss << std::left << std::setw(30) << "Gross Subtotal:" 
           << std::right << std::setw(24) << ("$" + std::to_string(static_cast<int>(subtotal)) + "." + 
              std::to_string(static_cast<int>((subtotal - static_cast<int>(subtotal)) * 100))) << "\n";
        ss << std::left << std::setw(30) << "Applied Discount:" 
           << std::right << std::setw(23) << "-$" << discount << "\n";
        ss << std::left << std::setw(30) << "Sales Tax (8%):" 
           << std::right << std::setw(23) << "$" << tax << "\n";
        ss << "=======================================================\n";
        ss << std::left << std::setw(30) << "FINAL TOTAL PAID:" 
           << std::right << std::setw(23) << "$" << grandTotal << "\n";
        ss << "=======================================================\n";
        ss << "  Thank you for your purchase! Come back soon.\n\n";

        std::string receiptText = ss.str();
        std::cout << receiptText;

        // Persist receipt to disk
        std::ofstream file(receiptFile);
        if (file.is_open()) {
            file << receiptText;
            std::cout << "  [Receipt successfully saved to disk: " << receiptFile << "]\n";
        }

        clear();
    }
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 20: Enterprise POS Capstone  \n";
    std::cout << "======================================================\n";

    InventoryManager inventory;
    inventory.addProduct("SKU-101", "MacBook Pro 16-inch M3", 2499.00, 15);
    inventory.addProduct("SKU-102", "Dell UltraSharp 32-inch 4K", 649.50, 25);
    inventory.addProduct("SKU-103", "Ergonomic Mechanical Keyboard", 149.00, 60);
    inventory.addProduct("SKU-104", "Wireless Gaming Mouse Pro", 79.99, 100);
    inventory.addProduct("SKU-105", "Noise Cancelling Headphones", 299.00, 40);

    std::cout << "\n1. Current Store Inventory Catalog:\n";
    inventory.displayCatalog();

    ShoppingCart cart;

    std::cout << "\n2. Adding Items to Customer Cart:\n";
    try {
        cart.addItem(inventory.getProduct("SKU-101"), 2);
        cart.addItem(inventory.getProduct("SKU-103"), 5);
        cart.addItem(inventory.getProduct("SKU-104"), 15); // Total 22 units triggers bulk discount!

        std::cout << "  Successfully added products to cart.\n";
    } catch (const POSException& e) {
        std::cerr << "  Cart Error: " << e.what() << "\n";
    }

    std::cout << "\n3. Testing Error Handling (Attempting to add invalid SKU):\n";
    try {
        cart.addItem(inventory.getProduct("SKU-999_DOES_NOT_EXIST"), 1);
    } catch (const ProductNotFoundException& e) {
        std::cout << "  Safely handled error: " << e.what() << "\n";
    }

    std::cout << "\n4. Setting Discount Policy to VIP Membership:\n";
    cart.setDiscountPolicy(std::make_unique<VIPMemberDiscountPolicy>());

    std::cout << "\n5. Executing Checkout & Generating Persistent Receipt:\n";
    cart.checkoutAndGenerateReceipt("TechCorp Enterprises LLC", "receipt_capstone.txt");

    std::cout << "\n6. Updated Inventory After Checkout (Observing stock deductions):\n";
    inventory.displayCatalog();

    std::cout << "\n[Part 20 Capstone Lesson Completed Successfully]\n";
    return 0;
}
