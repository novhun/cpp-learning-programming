#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

/**
 * ============================================================================
 * PART 15: FILE I/O, FILE STREAMS & DATA SERIALIZATION
 * ============================================================================
 * Concepts Covered:
 * 1. Stream hierarchy: std::ifstream (reading), std::ofstream (writing).
 * 2. File modes: out, in, app (append), binary.
 * 3. CSV data serialization and parsing with std::stringstream.
 * 4. Binary serialization of raw memory structs.
 * 5. Stream error flags: fail(), bad(), eof().
 * ============================================================================
 */

struct ProductRecord {
    int id;
    char name[32]; // Fixed-length character array for safe binary writing
    double price;
};

void demonstrateCSVFileIO() {
    std::cout << "\n========================================\n";
    std::cout << " 1. TEXT / CSV SERIALIZATION\n";
    std::cout << "========================================\n";

    const std::string filename = "inventory_export.csv";

    // 1. Write CSV records
    {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "  Error: Could not open " << filename << " for writing!\n";
            return;
        }

        // Write CSV Header
        outFile << "id,name,price\n";
        outFile << "101,Ultra Keyboard,79.99\n";
        outFile << "102,Gaming Mouse,49.50\n";
        outFile << "103,USB Hub 4-Port,18.00\n";

        std::cout << "  Successfully exported 3 records to " << filename << "\n";
    } // File closed automatically by RAII

    // 2. Read and parse CSV records line by line
    {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "  Error: Could not open " << filename << " for reading!\n";
            return;
        }

        std::string line;
        // Skip header line
        std::getline(inFile, line);

        std::cout << "  Parsing CSV records:\n";
        std::cout << "  " << std::left << std::setw(8) << "ID" 
                  << std::setw(20) << "Product" 
                  << std::right << std::setw(10) << "Price ($)\n";
        std::cout << "  " << std::string(38, '-') << "\n";

        while (std::getline(inFile, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string idStr, name, priceStr;

            std::getline(ss, idStr, ',');
            std::getline(ss, name, ',');
            std::getline(ss, priceStr, ',');

            int id = std::stoi(idStr);
            double price = std::stod(priceStr);

            std::cout << "  " << std::left << std::setw(8) << id 
                      << std::setw(20) << name 
                      << std::right << std::setw(10) << std::fixed 
                      << std::setprecision(2) << price << "\n";
        }
    }
}

void demonstrateBinaryFileIO() {
    std::cout << "\n========================================\n";
    std::cout << " 2. HIGH-SPEED BINARY FILE I/O\n";
    std::cout << "========================================\n";

    const std::string binFilename = "products.dat";

    ProductRecord original{501, "Precision Caliper", 34.50};

    // 1. Write binary struct directly from memory
    {
        std::ofstream outBin(binFilename, std::ios::binary);
        if (outBin) {
            outBin.write(reinterpret_cast<const char*>(&original), sizeof(ProductRecord));
            std::cout << "  Binary record serialized (" << sizeof(ProductRecord) << " bytes written).\n";
        }
    }

    // 2. Read binary struct directly into memory
    {
        ProductRecord loaded{};
        std::ifstream inBin(binFilename, std::ios::binary);
        if (inBin) {
            inBin.read(reinterpret_cast<char*>(&loaded), sizeof(ProductRecord));
            std::cout << "  Binary record deserialized:\n";
            std::cout << "    ID:    " << loaded.id << "\n";
            std::cout << "    Name:  " << loaded.name << "\n";
            std::cout << "    Price: $" << std::fixed << std::setprecision(2) << loaded.price << "\n";
        }
    }
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 15: File I/O & Serialization \n";
    std::cout << "======================================================\n";

    demonstrateCSVFileIO();
    demonstrateBinaryFileIO();

    std::cout << "\n[Part 15 Lesson Completed Successfully]\n";
    return 0;
}
