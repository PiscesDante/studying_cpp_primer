#ifndef VEC_HPP
#define VEC_HPP

#include <memory>
#include <utility>

template <typename T>
class Vec {
public:
    Vec<T>() :
        begin_ptr(nullptr), end_ptr(nullptr), curr_ptr(nullptr) {  }
    Vec<T>(const Vec<T>& rhs);
    Vec<T>& operator = (const Vec<T>& rhs);
    ~Vec<T>();

    void push_back(const T& rhs);
    std::size_t size() const { return curr_ptr - begin_ptr; }
    std::size_t capacity() const { return end_ptr - begin_ptr; }
    T* begin() const { return begin_ptr; }
    T* end() const { return end_ptr; }
private:
    void free();
    void reallocate();

    std::allocator<T> alloc;
    T* begin_ptr;
    T* end_ptr;
    T* curr_ptr;
};

#endif