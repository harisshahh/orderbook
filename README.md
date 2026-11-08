# Limit Order Book

A limit order book built in C++20 that simulates basic order matching using price-time priority.

## Features

- Buy and sell limit orders
- Price-time priority matching
- Partial order fills
- Matching across multiple price levels
- Order cancellation
- FIFO ordering at the same price
- Automated tests with GoogleTest

## Implementation

The order book uses `std::map` to organize price levels and `std::deque` to maintain order arrival order at each price.

Buy orders are matched against the lowest available sell price, while sell orders are matched against the highest available buy price.

Partially filled orders remain in the book with their remaining quantity.

## Technologies

- C++20
- CMake
- GoogleTest

## Build

```bash
cmake -S . -B build
cmake --build build
```

## Run Tests

```bash
ctest --test-dir build --output-on-failure
```

## Future Work

- Improve order lookup and cancellation performance
- Add input validation
- Benchmark matching and cancellation
- Explore memory and performance optimizations