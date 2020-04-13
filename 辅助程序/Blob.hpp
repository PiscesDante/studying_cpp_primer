#ifndef BLOB_HPP
#define BLOB_HPP

#include <iostream>
#include <memory>
#include <vector>

template <typename T>
class Blob {
public:
    Blob() : data_ptr(std::make_shared<std::vector<T>>()) {  }
    Blob(const std::initializer_list<T>& il);
    Blob& operator = (const Blob<T>& rhs);
    std::size_t size() const { return data_ptr->size(); }
    bool empty() const { return data_ptr->empty(); }
    void push_back(const T& elem) { data_ptr->push_back(elem); }
    void push_back(T&& elem) { data_ptr->push_back(std::move(elem)); }
    void pop_back();
    T& back();
    T& front();
    T& operator [] (const std::size_t pos);
private:
    std::shared_ptr<std::vector<T>> data_ptr;
    void check(std::size_t pos, const std::string& msg);
};

template <typename T>
Blob<T>::Blob(const std::initializer_list<T>& il)
    { data_ptr = std::make_shared<std::vector<T>>(il); }

template <typename T>
Blob<T>& Blob<T>::operator = (const Blob<T>& rhs)
    { data_ptr = rhs.data_ptr; }

template <typename T>
void Blob<T>::pop_back()
{
    check(0, "Error: pop_back on empty Blob.");
    data_ptr->pop_back();
}

template <typename T>
T& Blob<T>::back()
{
    check(0, "Error: back on empty Blob.");
    return data_ptr->back();
}

template <typename T>
T& Blob<T>::front()
{
    check(0, "Error: front on empty Blob.");
    return data_ptr->front();
}

template <typename T>
T& Blob<T>::operator [] (const std::size_t pos)
{
    check(pos, "Error: input pos is out of range.");
    return (*data_ptr)[pos];
}

template <typename T>
void Blob<T>::check(std::size_t pos, const std::string& msg)
{
    if (pos >= data_ptr->size()) {
        throw std::out_of_range(msg);
    }
}

#endif