#include "StrBlob.hpp"
#include "StrBlobPtr.hpp"

std::string& StrBlob::front()
{
    if (empty()) {
        throw std::runtime_error("Error: front on empty StrBlob.");
    } else {
        return sp_svec->front();
    }
}

std::string& StrBlob::back()
{
    if (empty()) {
        throw std::runtime_error("Error: back on empty StrBlob.");
    } else {
        return sp_svec->back();
    }
}

const std::string& StrBlob::front() const
{
    if (empty()) {
        throw std::runtime_error("Error: front on empty StrBlob.");
    } else {
        return sp_svec->front();
    }
}

const std::string& StrBlob::back() const
{
    if (empty()) {
        throw std::runtime_error("Error: back on empty StrBlob.");
    } else {
        return sp_svec->back();
    }
}

void StrBlob::bound_check(std::size_t index, const std::string& error_msg) const
{
    if (index < 0 || index >= size()) {
        throw std::out_of_range("Error: unbound index.");
    }
}

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this, 0); }

StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, sp_svec->size()); }