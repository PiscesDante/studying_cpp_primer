/*--------  编写程序，读取两个 `ISBN` 的相同的 `Sales_item` 对象，输出它们的和。  --------*/

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
    Sales_data data_1;
    Sales_data data_2;
    std::cin >> data_1.book_no >> data_1.units_sold >> data_1.single_price;
    std::cin >> data_2.book_no >> data_2.units_sold >> data_2.single_price;
    if (data_1.book_no == data_2.book_no) {
        std::cout << data_1.book_no << " | ";
        std::cout << data_1.units_sold + data_2.units_sold << " | ";
        std::cout << data_1.single_price << std::endl;
    }
    return 0;
}