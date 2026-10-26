#include <iostream>
#include <cstring>
#include <utility>
#include <cstddef>

/**
 * ============================================================================
 * PART 10: OPERATOR OVERLOADING & THE RULE OF 3 / 5 / 0
 * ============================================================================
 * Concepts Covered:
 * 1. Operator overloading: operator<<, operator+, operator==.
 * 2. Deep copying vs Shallow copying.
 * 3. The Rule of Three (C++98): Destructor, Copy Constructor, Copy Assignment.
 * 4. Move Semantics (C++11): Rvalue references (&&) and std::move.
 * 5. The Rule of Five (Modern C++): Adding Move Constructor & Move Assignment.
 * 6. The Rule of Zero: Leveraging RAII containers.
 * ============================================================================
 */

// Custom dynamic buffer class demonstrating the complete Rule of Five
class DynamicBuffer {
private:
    char* data_;
    std::size_t size_;

public:
    // 1. Parameterized Constructor
    explicit DynamicBuffer(const char* str = "") {
        size_ = std::strlen(str);
        data_ = new char[size_ + 1];
        std::memcpy(data_, str, size_ + 1);
        std::cout << "  [Constructed] DynamicBuffer(\"" << data_ << "\")\n";
    }

    // 2. Destructor (Rule of 5 #1)
    ~DynamicBuffer() {
        if (data_ != nullptr) {
            std::cout << "  [Destroyed] DynamicBuffer(\"" << data_ << "\")\n";
            delete[] data_;
            data_ = nullptr;
        } else {
            std::cout << "  [Destroyed] DynamicBuffer(nullptr/Moved-from)\n";
        }
    }

    // 3. Copy Constructor (Deep Copy) (Rule of 5 #2)
    DynamicBuffer(const DynamicBuffer& other)
        : size_(other.size_) {
        data_ = new char[size_ + 1];
        std::memcpy(data_, other.data_, size_ + 1);
        std::cout << "  [Deep Copy Constructor] Copied \"" << data_ << "\"\n";
    }

    // 4. Copy Assignment Operator (Rule of 5 #3)
    DynamicBuffer& operator=(const DynamicBuffer& other) {
        if (this == &other) {
            return *this; // Protect against self-assignment
        }
        delete[] data_; // Free existing resource

        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::memcpy(data_, other.data_, size_ + 1);
        std::cout << "  [Copy Assignment Operator] Copied \"" << data_ << "\"\n";
        return *this;
    }

    // 5. Move Constructor (Rule of 5 #4 - Steals ownership, zero memory allocation!)
    DynamicBuffer(DynamicBuffer&& other) noexcept
        : data_(other.data_), size_(other.size_) {
        // Pilfer the other object's pointer, leaving it in a valid null state
        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "  [Move Constructor] Efficiently pilfered buffer memory!\n";
    }

    // 6. Move Assignment Operator (Rule of 5 #5)
    DynamicBuffer& operator=(DynamicBuffer&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        delete[] data_; // Free existing resource

        // Transfer ownership
        data_ = other.data_;
        size_ = other.size_;

        other.data_ = nullptr;
        other.size_ = 0;
        std::cout << "  [Move Assignment Operator] Transferred ownership!\n";
        return *this;
    }

    // Stream Insertion Operator
    friend std::ostream& operator<<(std::ostream& os, const DynamicBuffer& buf) {
        if (buf.data_ != nullptr) {
            os << buf.data_;
        } else {
            os << "(empty/moved-from)";
        }
        return os;
    }

    // Equality operator
    bool operator==(const DynamicBuffer& other) const {
        if (size_ != other.size_) return false;
        return std::strcmp(data_, other.data_) == 0;
    }
};

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 10: Rule of 5 & Operators    \n";
    std::cout << "======================================================\n";

    std::cout << "\n1. Demonstrating Deep Copying:\n";
    DynamicBuffer buf1("Original String Data");
    DynamicBuffer buf2 = buf1; // Invokes Copy Constructor
    std::cout << "  buf1: " << buf1 << "\n";
    std::cout << "  buf2: " << buf2 << "\n";
    std::cout << "  Are they equal? " << (buf1 == buf2 ? "YES" : "NO") << "\n";

    std::cout << "\n2. Demonstrating Move Semantics (std::move):\n";
    DynamicBuffer buf3("Data to be moved");
    std::cout << "  buf3 before move: " << buf3 << "\n";

    DynamicBuffer buf4 = std::move(buf3); // Invokes Move Constructor
    std::cout << "  buf4 after move:  " << buf4 << "\n";
    std::cout << "  buf3 after move:  " << buf3 << " (State safely pilfered)\n";

    std::cout << "\n3. Scope End Cleanup (Watch destructors):\n";
    return 0;
}
