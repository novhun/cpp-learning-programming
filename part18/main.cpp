#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <future>
#include <chrono>

/**
 * ============================================================================
 * PART 18: CONCURRENCY & MULTITHREADING
 * ============================================================================
 * Concepts Covered:
 * 1. Spawning and joining threads (std::thread).
 * 2. Data races and thread synchronization.
 * 3. RAII mutex locking with std::lock_guard.
 * 4. Lock-free atomic operations with std::atomic<T>.
 * 5. Asynchronous computation with std::async and std::future.
 * ============================================================================
 */

std::mutex g_coutMutex;
std::mutex g_accountMutex;
double g_bankBalance = 1000.0;

// Atomic counter: lock-free, thread-safe counter
std::atomic<int> g_processedOrders{0};

void synchronizedPrint(const std::string& message) {
    std::lock_guard<std::mutex> lock(g_coutMutex);
    std::cout << message << "\n";
}

void performDeposit(int threadId, double amount, int count) {
    for (int i = 0; i < count; ++i) {
        {
            // Protect shared resource with RAII lock
            std::lock_guard<std::mutex> lock(g_accountMutex);
            g_bankBalance += amount;
        }
        // Atomic fetch-and-add (no mutex needed)
        ++g_processedOrders;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    synchronizedPrint("  [Worker " + std::to_string(threadId) + "] Completed deposits.");
}

// Function executed asynchronously
int computeComplexAnalytics(int datasetId) {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    return datasetId * 42;
}

int main() {
    std::cout << "======================================================\n";
    std::cout << "  C++ Masterclass - Part 18: Multithreading           \n";
    std::cout << "======================================================\n";

    std::cout << "\n1. Spawning Concurrent Worker Threads:\n";
    std::vector<std::thread> workers;

    // Launch 4 concurrent threads depositing funds simultaneously
    for (int i = 1; i <= 4; ++i) {
        workers.emplace_back(performDeposit, i, 25.0, 10);
    }

    // Wait for all worker threads to complete
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }

    std::cout << "  All threads finished execution.\n";
    std::cout << "  Final protected Bank Balance: $" << g_bankBalance << "\n";
    std::cout << "  Total atomic transactions processed: " << g_processedOrders.load() << "\n";

    std::cout << "\n2. Asynchronous Tasks with std::async & std::future:\n";
    // Launch async task in background
    std::future<int> analyticsResult = std::async(std::launch::async, computeComplexAnalytics, 10);

    std::cout << "  Main thread is free to do other work while async task runs...\n";

    // Block and retrieve calculated result from future
    int finalValue = analyticsResult.get();
    std::cout << "  Retrieved asynchronous computation result: " << finalValue << "\n";

    std::cout << "\n[Part 18 Lesson Completed Successfully]\n";
    return 0;
}
