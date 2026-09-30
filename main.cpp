#include <iostream>
#include "OrderBook.h"

int main() {

    std:: cout << "Test 1" << "\n";
    OrderBook book;
    book.addOrder({1, Side::Buy, 100.0, 10});
    book.addOrder({2, Side::Buy, 101.0, 5});
    book.printBook();
    std::cout << "cancel order 2: " << book.cancelOrder(2) << "\n";
    book.printBook();

    std::cout << "Test 2" << "\n";
    book.addOrder({3, Side::Sell, 105.0, 8});
    book.addOrder({4, Side::Sell, 104.0, 9});
    book.printBook();
    std::cout << "cancel order 3: " << book.cancelOrder(3) << "\n";
    book.printBook();

    std::cout << "Test 3" << "\n";
    OrderBook book2;
    book2.addOrder({5, Side::Buy, 100.0, 10});
    book2.addOrder({6, Side::Buy, 100.0, 20});
    book2.addOrder({7, Side::Buy, 100.0, 30});
    std::cout << "before cancellation:\n";
    book2.printBook();
    std::cout << "cancel order 6: " << book2.cancelOrder(6) << "\n";
    std::cout << "after cancellation:\n";
    book2.printBook();

    std::cout << "Test 4" << "\n";
    std::cout << "cancel order 9: " << book2.cancelOrder(9) << "\n";

    return 0;
}