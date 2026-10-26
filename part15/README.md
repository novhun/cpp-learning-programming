# Part 15: File I/O, File Streams & Data Serialization

## Overview
Persistent storage allows programs to save state to disk and reload it upon restart. In this lesson, you will master file streams (`std::ifstream`, `std::ofstream`), file access modes, delimited text parsing (CSV), and binary memory dumping/loading.

---

## 1. File Streams & RAII

File streams in C++ manage OS file descriptors using RAII. When a file stream object leaves its enclosing scope, its destructor automatically flushes buffers and closes the file descriptor.

```cpp
#include <fstream>

{
    std::ofstream file("data.txt");
    file << "Hello World!\n";
} // 'file' is automatically closed here!
```

---

## 2. Text vs Binary Files

| Feature | Text Files (ASCII / UTF-8) | Binary Files |
| :--- | :--- | :--- |
| **Human Readable?** | Yes (Openable in Notepad / VS Code) | No (Raw bytes / hex) |
| **Size Efficiency** | Larger (Numbers converted to text digits) | Compact (Exact memory footprint) |
| **Parsing Speed** | Slower (Requires string conversion) | Blazing fast (Direct DMA memory copy) |
| **Cross-Platform?** | Generally portable | Mind endianness and struct padding |

---

## 3. CSV Parsing with `std::stringstream`

To parse CSV files, read line-by-line using `std::getline(file, line)`, wrap each line in a `std::stringstream`, and split by the comma delimiter `','`:

```cpp
std::string line;
while (std::getline(inFile, line)) {
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, ',')) {
        // process individual comma-separated field
    }
}
```

---

## 4. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part15/main.cpp -o part15/main
./part15/main
```

---

## 5. Hands-On Exercises

1. **Transaction Journal Logger:** Create an append-only transaction logger using `std::ios::app` that logs timestamped sales messages into `sales.log`.
2. **Configuration File Parser:** Write a parser for key-value `config.ini` files (e.g. `port=8080`, `host=localhost`) that loads settings into a `std::unordered_map<std::string, std::string>`.
