#include <iostream>
#include <memory>
#include <string>
#include <vector>

/**
 * ============================================================================
 * PART 12: MODERN SMART POINTERS & RAII
 * ============================================================================
 * Concepts Covered:
 * 1. RAII (Resource Acquisition Is Initialization) paradigm.
 * 2. std::unique_ptr & std::make_unique (exclusive zero-overhead ownership).
 * 3. Moving unique_ptr ownership.
 * 4. std::shared_ptr & std::make_shared (reference-counted shared ownership).
 * 5. std::weak_ptr: Breaking cyclic dependencies.
 * 6. Custom Deleters for native C resource wrappers.
 * ============================================================================
 */

class DeviceSession {
private:
    std::string deviceId_;

public:
    explicit DeviceSession(std::string id) : deviceId_(std::move(id)) {
        std::cout << "  [Connect] DeviceSession opened: " << deviceId_ << "\n";
    }

    ~DeviceSession() {
        std::cout << "  [Disconnect] DeviceSession closed: " << deviceId_ << "\n";
    }

    void ping() const {
        std::cout << "  Device " << deviceId_ << " is online and responding.\n";
    }
};

void demonstrateUniquePtr() {
    std::cout << "\n========================================\n";
    std::cout << " 1. STD::UNIQUE_PTR (EXCLUSIVE OWNERSHIP)\n";
    std::cout << "========================================\n";

    // Allocate managed object on heap with make_unique
    auto dev1 = std::make_unique<DeviceSession>("ROUTER-01");
    dev1->ping();

    // Cannot copy unique_ptr (copy constructor is deleted):
    // auto dev2 = dev1; // COMPILE ERROR!

    // Must move ownership:
    std::cout << "  Transferring ownership of ROUTER-01 to dev2 via std::move...\n";
    std::unique_ptr<DeviceSession> dev2 = std::move(dev1);

    if (!dev1) {
        std::cout << "  dev1 is now nullptr (ownership successfully transferred).\n";
    }
    dev2->ping();

    std::cout << "  Exiting unique_ptr scope (auto-cleanup will trigger):\n";
}

void demonstrateSharedAndWeakPtr() {
    std::cout << "\n========================================\n";
    std::cout << " 2. STD::SHARED_PTR & STD::WEAK_PTR\n";
    std::cout << "========================================\n";

    // Shared pointer with reference counting
    std::shared_ptr<DeviceSession> sharedOwner1 = std::make_shared<DeviceSession>("SERVER-NODE");
    std::cout << "  Reference count after creation: " << sharedOwner1.use_count() << "\n";

    {
        std::shared_ptr<DeviceSession> sharedOwner2 = sharedOwner1; // Copies shared ownership
        std::cout << "  Reference count inside inner scope: " << sharedOwner1.use_count() << "\n";
        sharedOwner2->ping();

        // Weak pointer: non-owning observer that does not increment reference count
        std::weak_ptr<DeviceSession> weakObserver = sharedOwner2;
        std::cout << "  Ref count with weak_ptr active: " << sharedOwner1.use_count() << "\n";

        // Locking weak pointer to access object safely
        if (auto lockedPtr = weakObserver.lock()) {
            std::cout << "  Weak pointer successfully locked object:\n  ";
            lockedPtr->ping();
        }
        std::cout << "  Exiting inner scope (sharedOwner2 destroyed)...\n";
    }

    std::cout << "  Reference count back in outer scope: " << sharedOwner1.use_count() << "\n";
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 12: Smart Pointers & RAII    \n";
    std::cout << "======================================================\n";

    demonstrateUniquePtr();
    demonstrateSharedAndWeakPtr();

    std::cout << "\n[Part 12 Lesson Completed Successfully]\n";
    return 0;
}
