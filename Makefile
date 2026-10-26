CXX = clang++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference
BUILD_DIR = ./build

PART ?= 1

.PHONY: all run clean

all:
	@mkdir -p $(BUILD_DIR)
	@./run.sh all

run:
	@mkdir -p $(BUILD_DIR)
	@./run.sh $(PART)

clean:
	rm -rf $(BUILD_DIR)/*
