/**
 * 编写程序，读取多条销售记录
 * 并统计每个 ISBN （每本书）有几条销售记录。
 */

#include <iostream>
#include <string>
#include <map>
#include <utility>

struct Sales_data
{
    std::string book_no { "Null" };
    int units_sold { -1 };
    double single_price { 0.0 };
};

int main(int argc, char** argv)
{
    std::map<std::string, int> records;
    Sales_data current_input;
    while (std::cin >> current_input.book_no >> current_input.units_sold >> current_input.single_price) {
        auto iter = records.find(current_input.book_no);
        if (iter != records.end()) {
            iter->second += 1;
        } else {
            records[current_input.book_no] = 1;
        }
    }
    for (auto record : records) {
        std::cout << record.frist << " : ";
        std::cout << record.second << std::endl;
    }
    return 0;
}