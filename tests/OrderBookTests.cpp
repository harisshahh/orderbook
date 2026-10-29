#include <gtest/gtest.h>
#include <string>
#include "../OrderBook.h"


TEST(OrderBookTest, BuyOrderRestsWhenNoAsk) {
    OrderBook book;

    book.addOrder({1, Side::Buy, 100.0, 10});

    testing::internal::CaptureStdout();
    book.printBook();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("ID: 1"), std::string::npos);
    EXPECT_NE(output.find("Qty: 10"), std::string::npos);
}

TEST(OrderBookTest, MatchingPartialFill) {

    OrderBook book;

    book.addOrder(Order{1, Side::Sell, 100.0, 10});
    book.addOrder(Order{2, Side::Buy, 100.0, 6});

    testing::internal::CaptureStdout();
    book.printBook();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("ID: 1"), std::string::npos);
    EXPECT_NE(output.find("Qty: 4"), std::string::npos);
    EXPECT_EQ(output.find("ID: 2"), std::string::npos);
}


TEST(OrderBookTest, CancelRemovesOrder) {

    OrderBook book;

    book.addOrder(Order{1, Side::Buy, 100.0, 10});

    bool cancelled = book.cancelOrder(1);

    EXPECT_TRUE(cancelled);

    testing::internal::CaptureStdout();
    book.printBook();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.find("ID: 1"), std::string::npos);
}


TEST(OrderBookTest, CancelUnknownOrderReturnsFalse) {

    OrderBook book;

    bool cancelled = book.cancelOrder(999);

    EXPECT_FALSE(cancelled);
}

 // Tests that orders at the same price are filled in FIFO order.
TEST(OrderBookTest, FIFOExecutionAtSamePrice) {
    OrderBook book;

    book.addOrder(Order{1, Side::Sell, 100.0, 5});
    book.addOrder(Order{2, Side::Sell, 100.0, 7});
    book.addOrder(Order{3, Side::Buy, 100.0, 8});

    testing::internal::CaptureStdout();
    book.printBook();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.find("ID: 1"), std::string::npos);
    EXPECT_NE(output.find("ID: 2"), std::string::npos);
    EXPECT_NE(output.find("Qty: 4"), std::string::npos);
    EXPECT_EQ(output.find("ID: 3"), std::string::npos);
}

// Tests that an incoming order consumes the best prices first.
TEST(OrderBookTest, MatchesAcrossMultiplePriceLevels) {
    OrderBook book;

    book.addOrder(Order{1, Side::Sell, 100.0, 5});
    book.addOrder(Order{2, Side::Sell, 101.0, 5});
    book.addOrder(Order{3, Side::Sell, 102.0, 5});
    book.addOrder(Order{4, Side::Buy, 101.0, 8});

    testing::internal::CaptureStdout();
    book.printBook();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output.find("ID: 1"), std::string::npos);
    EXPECT_NE(output.find("ID: 2"), std::string::npos);
    EXPECT_NE(output.find("Qty: 2"), std::string::npos);
    EXPECT_NE(output.find("ID: 3"), std::string::npos);
    EXPECT_NE(output.find("Qty: 5"), std::string::npos);
}

TEST(OrderBookTest, CancelMiddleOrderPreservesRemainingOrders) {
    OrderBook book;

    book.addOrder(Order{1, Side::Buy, 100.0, 10});
    book.addOrder(Order{2, Side::Buy, 100.0, 20});
    book.addOrder(Order{3, Side::Buy, 100.0, 30});

    EXPECT_TRUE(book.cancelOrder(2));

    testing::internal::CaptureStdout();
    book.printBook();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("ID: 1"), std::string::npos);
    EXPECT_EQ(output.find("ID: 2"), std::string::npos);
    EXPECT_NE(output.find("ID: 3"), std::string::npos);
    EXPECT_NE(output.find("Qty: 10"), std::string::npos);
    EXPECT_NE(output.find("Qty: 30"), std::string::npos);
}
