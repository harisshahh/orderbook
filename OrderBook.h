#pragma once
#include <algorithm>
#include <map>
#include <deque>
#include <functional>
#include <iostream>
#include "Order.h"

class OrderBook {
private:
    std::map<double, std::deque<Order>> asks;
    std::map<double, std::deque<Order>, std::greater<>> bids;

    void matchOrder(Order &incoming) {
        if (incoming.side == Side::Buy) {
            while (incoming.quantity > 0 && !asks.empty()) {
                auto bestAsk = asks.begin();
                if (incoming.price < bestAsk->first) {
                    break;
                }
                Order &resting = bestAsk->second.front();
                uint64_t traded = std::min(incoming.quantity, resting.quantity);
                std::cout << "Trade: " << traded
                << " @ " << resting.price
                << " (buy order " << incoming.id
                << ", sell order " << resting.id
                << ")\n";

                incoming.quantity -= traded;
                resting.quantity -= traded;

                if (resting.quantity == 0) {
                    bestAsk->second.pop_front();
                }
                if (bestAsk->second.empty()) {
                    asks.erase(bestAsk);
                }
            }
        } else {
            while (incoming.quantity > 0 && !bids.empty()) {
                auto bestBid = bids.begin();
                if (incoming.price > bestBid->first) {
                    break;
                }
                Order &resting = bestBid->second.front();
                uint64_t traded = std::min(incoming.quantity, resting.quantity);
                std:: cout << "Trade: " << traded
                << " @ " << resting.price
                << " (buy order " << incoming.id
                << ", sell order " << resting.id
                << ")\n";

                incoming.quantity -= traded;
                resting.quantity -= traded;

                if (resting.quantity == 0) {
                    bestBid->second.pop_front();
                }
                if (bestBid->second.empty()) {
                    bids.erase(bestBid);
                }
            }
        }
    }

public:
    void addOrder(const Order& order) {
        Order incoming = order;
        matchOrder(incoming);
        if (incoming.quantity == 0) {
            return;
        }

        if (incoming.side == Side::Buy) {
            bids[incoming.price].push_back(incoming);
        } else if (incoming.side == Side::Sell) {
            asks[incoming.price].push_back(incoming);
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
