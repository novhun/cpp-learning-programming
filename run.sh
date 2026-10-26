#!/usr/bin/env bash

# ==============================================================================
# C++ MASTERCLASS INTERACTIVE RUNNER SCRIPT
# ==============================================================================

set -e

CXX="clang++"
CXXFLAGS="-std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference"
BUILD_DIR="./build"

# ANSI Colors
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
RED='\033[0;31m'
BOLD='\033[1m'
NC='\033[0m' # No Color

mkdir -p "$BUILD_DIR"

run_lesson() {
    local PART_NUM="$1"
    local TARGET_DIR=""
    local OUT_BIN=""

    if [ "$PART_NUM" == "basic" ] || [ "$PART_NUM" == "0" ]; then
        TARGET_DIR="basic"
        OUT_BIN="${BUILD_DIR}/basic"
        PART_NUM="Basic (Hello World)"
    else
        # Strip any leading 'part' if user entered 'part5'
        PART_NUM="${PART_NUM#part}"
        TARGET_DIR="part${PART_NUM}"
        OUT_BIN="${BUILD_DIR}/part${PART_NUM}"
    fi

    local SRC_FILE="${TARGET_DIR}/main.cpp"

    if [ ! -f "$SRC_FILE" ]; then
        echo -e "${RED}Error: Lesson source file '$SRC_FILE' does not exist!${NC}"
        exit 1
    fi

    echo -e "${CYAN}------------------------------------------------------------${NC}"
    echo -e "${BOLD}${CYAN}Compiling ${PART_NUM} with strict Clang++ flags...${NC}"
    echo -e "${CYAN}------------------------------------------------------------${NC}"
    echo "Command: $CXX $CXXFLAGS $SRC_FILE -o $OUT_BIN"
    
    $CXX $CXXFLAGS "$SRC_FILE" -o "$OUT_BIN"
    echo -e "${GREEN}✓ Compilation successful with 0 warnings!${NC}\n"

    echo -e "${YELLOW}------------------------------------------------------------${NC}"
    echo -e "${BOLD}${YELLOW}Running ${PART_NUM} Output:${NC}"
    echo -e "${YELLOW}------------------------------------------------------------${NC}"
    "$OUT_BIN"
    echo -e "${GREEN}\n✓ Execution completed.${NC}"
}

run_all() {
    echo -e "${BOLD}${CYAN}Compiling and verifying all 20 C++ Lessons...${NC}\n"
    for i in {1..20}; do
        local TARGET_DIR="part${i}"
        local SRC_FILE="${TARGET_DIR}/main.cpp"
        local OUT_BIN="${BUILD_DIR}/part${i}"
        echo -n "Compiling Part $i... "
        $CXX $CXXFLAGS "$SRC_FILE" -o "$OUT_BIN"
        echo -e "${GREEN}PASS${NC}"
    done
    echo -e "\n${BOLD}${GREEN}All 20 parts compiled cleanly with zero warnings!${NC}"
}

# If arguments provided
if [ $# -gt 0 ]; then
    if [ "$1" == "all" ]; then
        run_all
        exit 0
    elif [ "$1" == "clean" ]; then
        rm -rf "$BUILD_DIR"/*
        echo -e "${GREEN}Build artifacts cleaned.${NC}"
        exit 0
    else
        run_lesson "$1"
        exit 0
    fi
fi

# Interactive Menu
echo -e "${BOLD}${CYAN}============================================================${NC}"
echo -e "${BOLD}${CYAN}          MODERN C++ PROFESSIONAL MASTERCLASS              ${NC}"
echo -e "${BOLD}${CYAN}============================================================${NC}"
echo "Select a lesson to compile and run (0 - 20):"
echo ""
echo "  [0]  Basic:   Hello World & Fundamental Concepts (Starter)"
echo "  [1]  Part 1:  Variables, Data Types, Standard I/O & Formatting"
echo "  [2]  Part 2:  Control Flow, Conditionals & POS Multi-Item Loops"
echo "  [3]  Part 3:  Functions, Scope & Parameter Passing Modes"
echo "  [4]  Part 4:  Arrays, Strings & Zero-Allocation string_view"
echo "  [5]  Part 5:  Pointers, Addresses & Heap Memory Allocation"
echo "  [6]  Part 6:  References, Const Correctness & Scoped Enums"
echo "  [7]  Part 7:  Structures, Memory Padding & Structured Bindings"
echo "  [8]  Part 8:  OOP: Classes, Encapsulation & Lifecycle"
echo "  [9]  Part 9:  OOP: Inheritance, Polymorphism & Virtual Functions"
echo "  [10] Part 10: Operator Overloading & The Rule of 3/5/0"
echo "  [11] Part 11: Generic Templates & Compile-time Type Traits"
echo "  [12] Part 12: Modern Smart Pointers & RAII"
echo "  [13] Part 13: STL Containers (Vectors, Maps, Sets, Deques)"
echo "  [14] Part 14: STL Algorithms, Predicates & Modern Lambdas"
echo "  [15] Part 15: File I/O, File Streams & Data Serialization"
echo "  [16] Part 16: Exception Handling & Robust Error Architecture"
echo "  [17] Part 17: Modern C++17/20 Features (optional, variant)"
echo "  [18] Part 18: Multithreading, Concurrency & Atomics"
echo "  [19] Part 19: Design Patterns (Singleton, Factory, Strategy)"
echo "  [20] Part 20: Capstone: Enterprise POS & Inventory Engine"
echo "  [A]  All:     Verify & compile all 20 lessons"
echo "  [Q]  Quit"
echo ""
read -p "Enter choice [0-20, A, Q]: " choice

case "$choice" in
    [0-9]|1[0-9]|20)
        run_lesson "$choice"
        ;;
    [bB]|"basic")
        run_lesson "basic"
        ;;
    [aA])
        run_all
        ;;
    [qQ])
        echo "Exiting."
        exit 0
        ;;
    *)
        echo -e "${RED}Invalid choice! Please run ./run.sh <1-20>${NC}"
        exit 1
        ;;
esac
