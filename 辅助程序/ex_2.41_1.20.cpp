/*--------  编写程序读取一组销售记录，将每条记录打印到标准输出上。  --------*/

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
    Sales_data single_data;
    std::vector<Sales_data> data_vector;
    while (std::cin >> single_data.book_no >> single_data.units_sold >> single_data.single_price)
        data_vector.push_back(single_data);
    for (auto& data : data_vector) {
        std::cout << data.book_no << " | ";
        std::cout << data.units_sold << " | ";
        std::cout << data.single_price << std::endl;
    }
    return 0;
}