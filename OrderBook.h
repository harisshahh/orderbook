#pragma once
#include <cstdint>
#include <map>
#include <deque>
#include <functional>
#include "Order.h"

class OrderBook {
private:
    std::map<double, std::deque<Order>> asks;
    std::map<double, std::deque<Order>, std::greater<>> bids;
public:
    void addOrder(const Order& order) {
        if (order.side == Side::Buy) {
            bids[order.price].push_back(order);
        } else {
            asks[order.price].push_back(order);
        }
    }
};
