#include <iostream>
#include <string>
#include <vector>
#include <utility>

struct Sales_data
{
    std::string book_no = "NULL";
    int units_sold = -1;
    double single_price = 0.0;
};

int main(int argc, char** argv)
{
    Sales_data current_input;
    std::vector<Sales_data> sd_set;
    bool is_found;
    while (std::cin >> current_input.book_no >> current_input.units_sold >> current_input.single_price) {
        is_found = false
        for (auto& record : sd_set) {
            if (current_input.book_no == record.book_no) {
                is_found = true;
                record.units_sold += current_input.units_sold;
                break;
            }
        }
        if (!is_found) {
            sd_set.push_back(current_input);
        }
    }
    if (!sd_set.empty()) {
        for (auto& item : sd_set) {
            std::cout << item.book_no << " | ";
            std::cout << item.units_sold << " | ";
            std::cout << item.single_price << std::endl; 
        }
    } else {
        std::cout << "Error : No Data." << std::endl;
    }
    return 0;
}