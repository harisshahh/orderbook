#include <iostream>
#include <map>
#include <cstdint>

enum class Side {Buy, Sell};

struct Order {
    uint64_t id;
    Side side;
    double price;
    uint64_t quantity;
};

int main() {
    Order o{123, Side::Buy, 10, 20};
    std::cout << "Order: " << o.id
    << "\nSide: " << static_cast<int>(o.side)
    << "\nPrice: " << o.price
    << "\nQuantity: " << o.quantity << std::endl;
}