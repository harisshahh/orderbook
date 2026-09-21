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
    void printBook() const {
        std::cout << "==========OrderBook==========" << "\n";

        std::cout << "\nBIDS: \n";
        for (const auto& level: bids) {
            std::cout << "Price: " << level.first << " | Orders: ";
            for (const auto& order: level.second) {
                std::cout << "[ID: " << order.id
                << ", Qty: " << order.quantity
                << "]";
            }
            std::cout << "\n";
        }
        std::cout << "\nASKS: \n";
        for (const auto& level: asks) {
            std::cout << "Price: " << level.first << " | Orders: ";
            for (const auto& order: level.second) {
                std::cout << "[ID: " << order.id
                << ", Qty: " << order.quantity
                << "]";
            }
            std::cout << "\n";
        }
        std::cout << "====================\n";
    }
};
