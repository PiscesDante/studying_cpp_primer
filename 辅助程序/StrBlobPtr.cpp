#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"

StrBlobPtr::StrBlobPtr(StrBlob& strBlob, std::size_t pos) :
    wp_svec(strBlob.sp_svec), curr_pos(pos) {  }

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t pos) const
{
    std::shared_ptr<std::vector<std::string>> sp_temp = wp_svec.lock();
    if (!sp_temp) throw std::runtime_error("Error: Data does not exist.");
    if (pos >= sp_temp->size()) throw std::out_of_range("Error: Index out of range.");
    return sp_temp;
}

std::string& StrBlobPtr::curr_elem() const
{
    auto sp = check(curr_pos);
    return (*sp)[curr_pos];
}

StrBlobPtr& StrBlobPtr::pos_increase()
{
    auto sp = check(curr_pos);
    ++curr_pos;
    return *this;
}