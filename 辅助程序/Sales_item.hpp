#include <string>
#include <iostream>

/*********  DECLARATIONS  **********/


class Sales_item;
std::ostream& operator << (std::ostream& os, const Sales_item& rhs);
std::istream& operator >> (std::istream& is, Sales_item& rhs);


/*********  IMPLEMENTS  **********/


class Sales_item
{
friend std::ostream& operator << (std::ostream& os, const Sales_item& rhs);
friend std::istream& operator >> (std::istream& is, Sales_item& rhs);

private:
    std::string book_no { "Null" };
    int sales_amount { 0 };
    double unit_price { 0.0 };

public:
    Sales_item(std::string book_no, int sales_amount, double unit_price);
    Sales_item(const Sales_item& rhs);
    Sales_item& operator = (Sales_item& rhs);

    std::string isbn() const { return book_no; }
    Sales_item& operator += (const Sales_item& rhs);
};

std::ostream& operator << (std::ostream& os, const Sales_item& rhs)
{
    os << "Book No: " << rhs.book_no << " | ";
    os << "Salse Amount: " << rhs.sales_amount << " | ";
    os << "Unit Price: " << rhs.unit_price;
    return os;
}

std::istream& operator >> (std::istream& is, Sales_item& rhs)
{
    is >> rhs.book_no >> rhs.sales_amount >> rhs.unit_price;
    return is;
}

Sales_item::Sales_item(std::string book_no = "null", int sales_amount = 0, double unit_price = 0.0)
{
    this->book_no = book_no;
    this->sales_amount = sales_amount;
    this->unit_price = unit_price;
}

Sales_item::Sales_item(const Sales_item& rhs)
{
    if (&rhs != nullptr) {
        this->book_no = rhs.book_no;
        this->sales_amount = rhs.sales_amount;
        this->unit_price = rhs.unit_price;
    }
}

Sales_item& Sales_item::operator = (Sales_item& rhs)
{
    if (&rhs != nullptr && &rhs != this) {
        this->book_no = rhs.book_no;
        this->sales_amount = rhs.sales_amount;
        this->unit_price = rhs.unit_price;
    }
    return *this;
}

Sales_item& Sales_item::operator += (const Sales_item& rhs)
{
    if (this->book_no == rhs.book_no) {
        this->sales_amount += rhs.sales_amount;
    }
    return *this;
}