/*************************************************************************
 * 我们将为 StrBlob 类定义一个伴随指针类。我们的指针类将命名为 StrblobPtr
 * 这个类里面会保存一个 weak_ptr ，不会影响一个给定的 StrBlob 所指向的 vector
 * 的生存期。但是，可以阻止用户访问一个不再存在的 vector 的企图。
 * 两个数据成员：wp_svec 和 curr_pos 。分别指向容器和当前对象所在的下标。
**************************************************************************/

#ifndef STRBLOBPTR_HPP
#define STRBLOBPTR_HPP

#include <memory>
#include <string>
#include <vector>
#include <cstdlib>
#include <exception>

class StrBlob;

class StrBlobPtr {
friend class StrBlob;
public:
    StrBlobPtr() :
        curr_pos(0) {  }
    StrBlobPtr(StrBlob& strBlob, std::size_t pos);
    std::string& curr_elem() const;
    std::size_t get_curr_pos() const { return curr_pos; }
    StrBlobPtr& pos_increase(); // 递增前缀
private:
    std::shared_ptr<std::vector<std::string>> check(std::size_t pos) const;
    std::weak_ptr<std::vector<std::string>> wp_svec;
    std::size_t curr_pos; // 当前指向的内容
};

#endif