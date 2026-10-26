#include <iostream>
#include <array>
#include <string>
#include <string_view>
#include <iomanip>
#include <cstddef>

/**
 * ============================================================================
 * PART 04: ARRAYS, STRINGS & STRING_VIEW
 * ============================================================================
 * Concepts Covered:
 * 1. Traditional C-arrays vs Modern std::array<T, N>.
 * 2. Bounds checking with .at() vs direct indexing [].
 * 3. 2D arrays & matrix iteration.
 * 4. C-strings (null-terminated '\0') vs std::string.
 * 5. std::string operations (substrings, searches, replacements).
 * 6. Modern C++17 std::string_view for zero-allocation performance.
 * ============================================================================
 */

void demonstrateModernArrays() {
    std::cout << "\n========================================\n";
    std::cout << " 1. STD::ARRAY VS C-STYLE ARRAYS\n";
    std::cout << "========================================\n";

    // Modern std::array is fixed-size, stack-allocated, but carries size metadata
    std::array<double, 5> productPrices = {19.99, 45.50, 9.99, 120.00, 32.75};

    std::cout << "Array size: " << productPrices.size() << " elements\n";
    std::cout << "Prices: ";
    for (double price : productPrices) {
        std::cout << "$" << price << " ";
    }
    std::cout << "\n";

    // Bounds safety: .at() throws std::out_of_range exception if invalid index
    try {
        std::cout << "Safe access at index 2: $" << productPrices.at(2) << "\n";
        // productPrices.at(10); // Uncommenting this throws std::out_of_range
    } catch (const std::out_of_range& e) {
        std::cerr << "Out of bounds error: " << e.what() << "\n";
    }

    // 2D Matrix
    std::cout << "\n2D Grid (3x3 Identity Matrix):\n";
    std::array<std::array<int, 3>, 3> matrix = {{
        {{1, 0, 0}},
        {{0, 1, 0}},
        {{0, 0, 1}}
    }};

    for (const auto& row : matrix) {
        std::cout << "  [ ";
        for (int cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "]\n";
    }
}

void demonstrateStringManipulations() {
    std::cout << "\n========================================\n";
    std::cout << " 2. STD::STRING MANIPULATION\n";
    std::cout << "========================================\n";

    std::string text = "SKU-9482-ELECTRONICS-LAPTOP";

    // Finding substrings
    std::size_t firstDash = text.find('-');
    std::size_t secondDash = text.find('-', firstDash + 1);

    if (firstDash != std::string::npos && secondDash != std::string::npos) {
        std::string skuCode = text.substr(firstDash + 1, secondDash - firstDash - 1);
        std::cout << "Extracted SKU Code: " << skuCode << "\n";
    }

    // Modifying strings
    std::string sentence = "C++ is old.";
    sentence.replace(7, 3, "modern and blazing fast");
    std::cout << "Updated sentence: \"" << sentence << "\"\n";

    // Conversions
    std::string priceStr = "149.95";
    double priceVal = std::stod(priceStr);
    std::cout << "Parsed string to double: $" << priceVal << " (with tax: $" 
              << (priceVal * 1.08) << ")\n";
}

// Pass by std::string_view: zero heap allocation, read-only view of any string source!
void processReadOnly(std::string_view sv) {
    std::cout << "  StringView length: " << sv.length() 
              << " | First char: " << sv.front() 
              << " | Full View: \"" << sv << "\"\n";
}

void demonstrateStringView() {
    std::cout << "\n========================================\n";
    std::cout << " 3. MODERN C++17 STD::STRING_VIEW\n";
    std::cout << "========================================\n";

    // Works seamlessly on C-style string literals without converting to std::string:
    processReadOnly("Direct C-string literal");

    // Works on std::string without allocating new memory:
    std::string dynamicStr = "Allocated std::string object";
    processReadOnly(dynamicStr);

    // Cheap slicing: O(1) time without copying characters!
    std::string_view slice = std::string_view(dynamicStr).substr(10, 11);
    std::cout << "  Sliced view without memory allocation: \"" << slice << "\"\n";
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 4: Arrays & Strings          \n";
    std::cout << "======================================================\n";

    demonstrateModernArrays();
    demonstrateStringManipulations();
    demonstrateStringView();

    std::cout << "\n[Part 4 Lesson Completed Successfully]\n";
    return 0;
}
