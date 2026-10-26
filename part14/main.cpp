#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <iomanip>

/**
 * ============================================================================
 * PART 14: STL ALGORITHMS, ITERATORS & LAMBDAS
 * ============================================================================
 * Concepts Covered:
 * 1. Iterators: begin, end, and reverse iterators.
 * 2. Modern C++ Lambda expressions and capture modes.
 * 3. Sorting with custom lambda comparators (std::sort).
 * 4. Filtering and transforming data (std::transform, std::copy_if).
 * 5. Modern Erase-Remove idiom (std::remove_if + vector::erase).
 * 6. Numeric reductions with std::accumulate.
 * ============================================================================
 */

struct InventoryItem {
    std::string name;
    double price;
    int stock;
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 14: Algorithms & Lambdas     \n";
    std::cout << "======================================================\n";

    std::vector<InventoryItem> items = {
        {"Wireless Mouse", 29.99, 15},
        {"Gaming Laptop", 1499.00, 4},
        {"HDMI Cable", 12.50, 50},
        {"Mechanical Keyboard", 89.99, 8},
        {"USB Flash Drive", 15.00, 0} // Out of stock
    };

    // 1. Sorting with custom Lambda comparator (Sort by price descending)
    std::cout << "\n1. Items sorted by Price (Descending):\n";
    std::sort(items.begin(), items.end(), [](const InventoryItem& a, const InventoryItem& b) {
        return a.price > b.price;
    });

    for (const auto& item : items) {
        std::cout << "  " << std::left << std::setw(22) << item.name 
                  << " : $" << std::fixed << std::setprecision(2) << item.price 
                  << " (" << item.stock << " in stock)\n";
    }

    // 2. Count condition with std::count_if
    std::cout << "\n2. Counting elements matching predicate:\n";
    auto lowStockCount = std::count_if(items.begin(), items.end(), [](const InventoryItem& item) {
        return item.stock < 10;
    });
    std::cout << "  Items with low stock (< 10 units): " << lowStockCount << "\n";

    // 3. Modern Erase-Remove Idiom: Purging out-of-stock items
    std::cout << "\n3. Removing out-of-stock items (Erase-Remove Idiom):\n";
    items.erase(std::remove_if(items.begin(), items.end(), [](const InventoryItem& item) {
        return item.stock == 0;
    }), items.end());

    std::cout << "  Items remaining after purge: " << items.size() << "\n";

    // 4. Transform: Extracting just the product names into a new vector
    std::cout << "\n4. Transforming to list of names:\n";
    std::vector<std::string> itemNames;
    itemNames.reserve(items.size());
    std::transform(items.begin(), items.end(), std::back_inserter(itemNames),
                   [](const InventoryItem& item) { return item.name; });

    for (const auto& name : itemNames) {
        std::cout << "  - " << name << "\n";
    }

    // 5. Total inventory valuation using std::accumulate
    std::cout << "\n5. Numeric reduction with std::accumulate:\n";
    double totalValue = std::accumulate(items.begin(), items.end(), 0.0,
        [](double sum, const InventoryItem& item) {
            return sum + (item.price * static_cast<double>(item.stock));
        });

    std::cout << "  Total warehouse inventory value: $" << std::fixed 
              << std::setprecision(2) << totalValue << "\n";

    std::cout << "\n[Part 14 Lesson Completed Successfully]\n";
    return 0;
}
