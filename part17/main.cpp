#include <iostream>
#include <string>
#include <optional>
#include <variant>
#include <unordered_map>
#include <iomanip>

/**
 * ============================================================================
 * PART 17: MODERN C++ (C++17 / C++20 FEATURES)
 * ============================================================================
 * Concepts Covered:
 * 1. std::optional<T>: Eliminating sentinel values and null pointer bugs.
 * 2. std::variant<Ts...>: Type-safe tagged union replacing raw C unions.
 * 3. Visiting variants with std::visit and overloaded lambda structs.
 * 4. Selection statements with initializers (if (init; condition)).
 * 5. Structured bindings refresher.
 * ============================================================================
 */

// Helper struct template for std::visit pattern matching
template <class... Ts>
struct Overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
Overloaded(Ts...) -> Overloaded<Ts...>;

// Function returning std::optional instead of error codes or null pointers
std::optional<double> findDiscount(const std::string& couponCode) {
    static const std::unordered_map<std::string, double> validCoupons = {
        {"SAVE10", 0.10},
        {"VIP20", 0.20},
        {"BLACKFRIDAY", 0.35}
    };

    // If-statement with initializer (C++17)
    if (auto it = validCoupons.find(couponCode); it != validCoupons.end()) {
        return it->second; // Found!
    }
    return std::nullopt; // Not found!
}

void testOptionalFeature() {
    std::cout << "\n========================================\n";
    std::cout << " 1. STD::OPTIONAL<T> (C++17)\n";
    std::cout << "========================================\n";

    auto discount1 = findDiscount("SAVE10");
    if (discount1.has_value()) {
        std::cout << "  Coupon 'SAVE10' applied: " << (*discount1 * 100) << "% OFF!\n";
    }

    auto discount2 = findDiscount("EXPIRED99");
    // .value_or provides a safe default fallback value!
    double actualDiscount = discount2.value_or(0.0);
    std::cout << "  Coupon 'EXPIRED99' fallback discount: " << (actualDiscount * 100) << "%\n";
}

void testVariantFeature() {
    std::cout << "\n========================================\n";
    std::cout << " 2. STD::VARIANT & PATTERN MATCHING\n";
    std::cout << "========================================\n";

    // A variant can hold an int, double, or std::string safely in the same memory slot
    using ConfigValue = std::variant<int, double, std::string>;

    std::vector<ConfigValue> settings = {
        8080,
        15.5,
        std::string("Production-Cluster-EU")
    };

    for (const auto& setting : settings) {
        std::visit(Overloaded{
            [](int i) { std::cout << "  Integer setting: " << i << "\n"; },
            [](double d) { std::cout << "  Floating setting: " << d << "\n"; },
            [](const std::string& s) { std::cout << "  String setting: \"" << s << "\"\n"; }
        }, setting);
    }
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 17: Modern C++ Features      \n";
    std::cout << "======================================================\n";

    testOptionalFeature();
    testVariantFeature();

    std::cout << "\n[Part 17 Lesson Completed Successfully]\n";
    return 0;
}
