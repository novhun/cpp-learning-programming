#include <iostream> // Needed for console input (cin) and output (cout)
#include <string>   // Needed to use std::string for text variables

/**
 * ============================================================================
 * C++ BASICS: "HELLO WORLD" & INTRODUCTORY CONCEPTS
 * ============================================================================
 * Welcome to C++! This is the most fundamental starting point for learning C++.
 *
 * Here we break down:
 * 1. The classic "Hello, World!" program.
 * 2. Printing multiple lines and formatted text.
 * 3. Difference between '\n' and std::endl.
 * 4. Storing simple variables (numbers and words).
 * 5. Asking the user for input and saying hello.
 * ============================================================================
 */

int main() {
    // -------------------------------------------------------------
    // Step 1: The Classic "Hello, World!"
    // -------------------------------------------------------------
    std::cout << "Hello, World!\n";

    // -------------------------------------------------------------
    // Step 2: Printing Text & Basic Math Calculations
    // -------------------------------------------------------------
    std::cout << "\n========================================\n";
    std::cout << " Welcome to C++ Programming!            \n";
    std::cout << "========================================\n";

    std::cout << "C++ is powerful, fast, and fun to learn!\n";
    std::cout << "Let's do some quick math directly in cout:\n";
    std::cout << "  5 + 3 = " << (5 + 3) << "\n";
    std::cout << "  10 * 4 = " << (10 * 4) << "\n";
    std::cout << "  100 / 4 = " << (100 / 4) << "\n";

    // -------------------------------------------------------------
    // Step 3: Fundamental Variables (Data Storage)
    // -------------------------------------------------------------
    std::cout << "\n--- Basic Variables Demo ---\n";
    std::string learnerName = "Alex";
    int learningDay = 1;
    double progressPercent = 5.0;
    char gradeGoal = 'A';
    bool lovesCoding = true;

    std::cout << "Learner:  " << learnerName << "\n";
    std::cout << "Day #:    " << learningDay << "\n";
    std::cout << "Progress: " << progressPercent << "%\n";
    std::cout << "Target:   Grade " << gradeGoal << "\n";
    std::cout << "Loves C++: " << (lovesCoding ? "Yes, absolutely!" : "Not yet") << "\n";

    // -------------------------------------------------------------
    // Step 4: Simple Interactive User Input
    // -------------------------------------------------------------
    std::cout << "\n--- Interactive Input ---\n";
    std::string userName;
    int userAge = 0;

    std::cout << "Enter your first name: ";
    std::cin >> userName;

    std::cout << "Enter your age: ";
    std::cin >> userAge;

    std::cout << "\nHello, " << userName << "! Welcome to C++.\n";
    std::cout << "In 5 years, you will be " << (userAge + 5) << " years old!\n";
    std::cout << "Keep practicing every day and you will become an expert.\n";

    // 'return 0' tells the operating system that our program finished successfully
    return 0;
}
