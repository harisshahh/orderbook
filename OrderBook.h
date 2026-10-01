#pragma once

#include <map>
#include <deque>
#include <functional>
#include "Order.h"

class OrderBook {

private:
    std::map<double, std::deque<Order>> asks;
    std::map<double, std::deque<Order>, std::greater<>> bids;
    void matchOrder(Order &incoming);

public:
    void addOrder(const Order& order);
    bool cancelOrder(uint64_t orderId);
    void printBook() const;
};
