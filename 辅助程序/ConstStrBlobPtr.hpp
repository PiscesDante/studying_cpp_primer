#ifndef CONSTSTRBLOBPTR_HPP
#define CONSTSTRBLOBPTR_HPP

#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <exception>

class StrBlob;

class ConstStrBlobPtr {
friend class StrBlob;
public:
    StrBlobPtr() :
        curr_pos(0) {  }
    StrBlobPtr(const StrBlob& strBlob, std::size_t pos);
    const std::string& curr_elem() const;
    std::size_t get_curr_pos() const { return curr_pos; }
    ConstStrBlobPtr& pos_increase(); // 递增前缀
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t pos) const;
    std::weak_ptr<std::vector<std::string>> wp_svec;
    std::size_t curr_pos; // 当前指向的内容
};

#endif