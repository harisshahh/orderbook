#include <iostream>
#include <map>
#include <cstdint>

#include "OrderBook.h"

int main() {
    OrderBook book;

    Order firstBuy {1, Side::Buy, 100.0, 10};
    Order secondBuy{2, Side::Buy, 101.0, 5};
    Order thirdBuy{3, Side::Buy, 100.0, 20};
    Order firstSell {4, Side::Sell, 103.0, 8};

    book.addOrder(firstBuy);
    book.addOrder(secondBuy);
    book.addOrder(thirdBuy);
    book.addOrder(firstSell);


    return 0;
}