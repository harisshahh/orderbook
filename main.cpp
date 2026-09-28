#include <iostream>

#include "OrderBook.h"

int main() {
    OrderBook book;

    book.addOrder({1, Side::Sell, 100.0, 10});
    book.addOrder({2, Side::Sell, 101.0, 20});

    std::cout << "Book before the incoming buy:\n";
    book.printBook();

    book.addOrder({3, Side::Buy, 101.0, 15});
    std::cout << "Book after the incoming buy:\n";
    book.printBook();


    return 0;
}