/***********************************************************************
 * 定义 StrBlob 类
 * 最终这个类将会变成一个模板。但是，现在我们先定义一个管理 std::string 的类
 * 首先使用 std::vector<std::string> 作为容器来保存 std::string
 * 但是不能让 StrBlob 对象直接管理 std::vector<std::string> 
 * 要使用 std::shared_ptr<std::vector<std::string>> 来间接的管理容器
 * 修改访问元素的操作 front() back()
 * 访问不存在的元素会抛出一个异常
 * 一个默认构造函数 和 一个接受 std::initializer_list<std::string> 构造函数
************************************************************************/

#ifndef STRBLOB_HPP
#define STRBLOB_HPP

#include <memory>
#include <vector>
#include <string>
#include <cstdlib>
#include <initializer_list>

class StrBlobPtr;

class StrBlob {
friend class StrBlobPtr;
public:
    StrBlob() : // 默认构造函数
        sp_svec(std::make_shared<std::vector<std::string>>()) {  }
    StrBlob(std::initializer_list<std::string> sl) : // 接受初始化列表的构造函数
        sp_svec(std::make_shared<std::vector<std::string>>(sl)) {  }
    bool empty() const { return sp_svec->empty(); } // 判断是否为空
    std::size_t size() const { return sp_svec->size(); } // 返回数组大小
    void push_back(const std::string& s) { sp_svec->push_back(s); }
    std::string& front(); // 返回首元素的引用「可修改」
    std::string& back(); // 返回尾元素的引用「可修改」
    const std::string& front() const;
    const std::string& back() const;

    StrBlobPtr begin();
    StrBlobPtr end();
private:
    std::shared_ptr<std::vector<std::string>> sp_svec;
    void bound_check(std::size_t index, const std::string& error_msg) const;
};

#endif