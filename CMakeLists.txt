cmake_minimum_required(VERSION 4.2)
project(orderbook)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(orderbook
        main.cpp
        OrderBook.h
        Order.h
        OrderBook.cpp
)

add_executable(orderbook_tests
        tests/OrderBookTests.cpp
        OrderBook.cpp
        OrderBook.h
        Order.h
)

target_link_libraries(orderbook_tests
        PRIVATE
        GTest::gtest_main
)