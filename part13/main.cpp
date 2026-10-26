#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <iomanip>

/**
 * ============================================================================
 * PART 13: STL CONTAINERS (VECTORS, MAPS, SETS & DEQUES)
 * ============================================================================
 * Concepts Covered:
 * 1. Sequence containers: std::vector, std::deque, std::list.
 * 2. Ordered associative containers: std::map, std::set (Red-Black Trees, O(log N)).
 * 3. Unordered associative containers: std::unordered_map (Hash Tables, O(1)).
 * 4. Benchmarking lookup performance & container selection matrix.
 * ============================================================================
 */

void demonstrateVectorAndDeque() {
    std::cout << "\n========================================\n";
    std::cout << " 1. SEQUENCE CONTAINERS: VECTOR & DEQUE\n";
    std::cout << "========================================\n";

    // std::vector: Contiguous heap array, cache-friendly
    std::vector<int> numbers = {10, 20, 30};
    numbers.push_back(40);
    numbers.push_back(50);

    std::cout << "  vector size: " << numbers.size() 
              << " | capacity: " << numbers.capacity() << "\n  Elements: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    // std::deque: Fast insertion at both front and back
    std::deque<std::string> taskQueue;
    taskQueue.push_back("Task-Normal");
    taskQueue.push_front("Task-URGENT");
    taskQueue.push_back("Task-LowPriority");

    std::cout << "  deque order: ";
    for (const auto& task : taskQueue) {
        std::cout << "[" << task << "] ";
    }
    std::cout << "\n";
}

void demonstrateMapsAndSets() {
    std::cout << "\n========================================\n";
    std::cout << " 2. ASSOCIATIVE CONTAINERS: MAP & SET\n";
    std::cout << "========================================\n";

    // std::map: Automatically kept sorted by Key (O(log N))
    std::map<std::string, double> productCatalog;
    productCatalog["Laptop"] = 1299.99;
    productCatalog["Coffee Maker"] = 89.50;
    productCatalog["AirPods"] = 179.00;
    productCatalog["Desk Mat"] = 24.99;

    std::cout << "  Ordered Map (Alphabetical by Key):\n";
    for (const auto& [item, price] : productCatalog) {
        std::cout << "    " << std::left << std::setw(15) << item 
                  << " : $" << std::fixed << std::setprecision(2) << price << "\n";
    }

    // std::set: Unique sorted elements
    std::set<int> uniqueUserIds = {501, 102, 501, 304, 102, 999};
    std::cout << "  Unique sorted set of user IDs: ";
    for (int id : uniqueUserIds) {
        std::cout << id << " ";
    }
    std::cout << "\n";
}

void demonstrateUnorderedMap() {
    std::cout << "\n========================================\n";
    std::cout << " 3. UNORDERED_MAP (HASH TABLE O(1))\n";
    std::cout << "========================================\n";

    std::unordered_map<std::string, int> stockLevels;
    stockLevels["GPU-RTX4080"] = 14;
    stockLevels["CPU-I9-14900K"] = 8;
    stockLevels["RAM-DDR5-32GB"] = 45;

    // Fast O(1) average lookup
    std::string query = "GPU-RTX4080";
    auto it = stockLevels.find(query);
    if (it != stockLevels.end()) {
        std::cout << "  Item " << it->first << " in stock: " << it->second << " units.\n";
    }
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 13: STL Containers           \n";
    std::cout << "======================================================\n";

    demonstrateVectorAndDeque();
    demonstrateMapsAndSets();
    demonstrateUnorderedMap();

    std::cout << "\n[Part 13 Lesson Completed Successfully]\n";
    return 0;
}
