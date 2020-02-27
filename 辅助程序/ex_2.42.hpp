// 加入主动防御头
#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

struct Sales_data
{
    std::string book_no { "Null" };
    int units_sold { 0 };
    double single_price { 0.0 };
};

#endif