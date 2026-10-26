# Part 20: Capstone Project: Enterprise Terminal POS & Inventory System

## Overview
This final capstone project consolidates every concept learned across the entire 20-part masterclass into an enterprise-grade Point-of-Sale (POS) and inventory management engine. It demonstrates clean architecture, RAII, smart pointer ownership, STL containers, custom exceptions, design patterns (Strategy), file I/O persistence, and strict warning-free modern C++.

---

## 1. System Architecture

```
                  ┌────────────────────────┐
                  │    InventoryManager    │
                  │ (unordered_map<SKU,   │
                  │   shared_ptr<Product>) │
                  └───────────┬────────────┘
                              │ references
                              ▼
┌──────────────────┐    ┌───────────┐    ┌─────────────────────┐
│   ShoppingCart   │───►│  Product  │    │   IDiscountPolicy   │
│ (vector<CartItem>│    │ (Entity)  │    │     (Strategy)      │
└────────┬─────────┘    └───────────┘    └──────────┬──────────┘
         │                                          ▲
         ▼ checkout                                 │ uses
┌──────────────────┐               ┌────────────────┴──────────────┐
│  ASCII Receipt   │               │ VIPMember / TieredBulkPolicy  │
│  & Disk Export   │               └───────────────────────────────┘
└──────────────────┘
```

---

## 2. Key Engineering Highlights

1. **Memory Safety & Ownership:**
   - Products are shared across catalog and carts via `std::shared_ptr<Product>`.
   - Discount strategies are owned exclusively by `std::unique_ptr<IDiscountPolicy>` and swapped at runtime with `std::move`.
2. **Custom Domain Exceptions:**
   - `ProductNotFoundException` and `InsufficientStockException` enforce transactional integrity before deducting any warehouse stock.
3. **Data Persistence:**
   - Completed orders are simultaneously printed to the console with professional formatting and written to disk as official receipts using `std::ofstream`.
4. **Zero-Warning Strict Quality:**
   - Fully compliant with `-Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference`.

---

## 3. How to Compile & Run

```bash
clang++ -std=c++17 -Wall -Wextra -Wpedantic part20/main.cpp -o part20/main
./part20/main
```

---

## 4. Extended Capstone Exercises

1. **Barcode / SKU Scanner:** Add an interactive terminal loop allowing cashiers to enter SKUs and quantities via `std::cin` until entering `DONE`.
2. **Sales Journal CSV Exporter:** Append a transaction log entry into `daily_sales.csv` every time a receipt is successfully checked out.
3. **Multithreaded Stock Replenisher:** Use `std::thread` to simulate a background warehouse restocking routine updating product stock quantities while sales occur.
