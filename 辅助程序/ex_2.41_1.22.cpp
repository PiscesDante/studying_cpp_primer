/*--------  编写程序，读取多个具有相同 `ISBN` 的销售记录，输出所有记录的和。  --------*/

#include <iostream>
#include <string>
#include <vector>

struct Sales_data
{
    std::string book_no { "Null" };
    int units_sold { -1 };
    double single_price { 0.0 };
};

int main(int argc, char** argv)
{
    Sales_data temp;
    Sales_data total;
    std::cin >> temp.book_no >> temp.units_sold >> temp.single_price;
    total = temp;
    while (std::cin >> temp.book_no >> temp.units_sold >> temp.single_price) {
        total.units_sold += temp.units_sold;
    }
    std::cout << total.book_no << " | ";
    std::cout << total.units_sold << " | ";
    std::cout << total.single_price << std::endl;
    return 0;
}