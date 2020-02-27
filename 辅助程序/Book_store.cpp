#include <iostream>
#include "Sales_item.hpp"

int main(int argc, char** argv)
{
    Sales_item total;
    if (std::cin >> total) {
        Sales_item trans;
        while (std::cin >> trans) {
            if (total.isbn() == trans.isbn()) {
                total += trans;
            } else {
                std::cout << total << std::endl;
                total = trans;
            }
        }
        std::cout << total << std::endl;
    } else {
        std::cerr << "Error: No Data Input." << std::endl;
        return -1;
    }
    return 0;
}