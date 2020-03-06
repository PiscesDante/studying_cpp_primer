#include <string>
#include <memory>
#include <cstdlib>
#include <initializer_list>

class StrVec {
public: // Constructors
    StrVec() :
        head(nullptr), curr(nullptr), tail(nullptr) {  }
    StrVec(const StrVec& rhs);
    StrVec(const std::initializer_list<std::string>& slis);
    StrVec& operator = (const StrVec& rhs);
    ~StrVec();
public: // Member Funtions
    void push_back(const std::string& s);
    std::size_t size() const { return curr - head; }
    std::size_t capacity() const { return tail - head; }
    std::string* begin() const { return head; }
    std::string* end() const { return tail; }
    void reserve(std::size_t new_capa);
    void resize(std::size_t new_sz);
    void show_info() const;
private: // Member Varians
    std::allocator<std::string> alloc;
    std::string* head;
    std::string* curr;
    std::string* tail;
private: // Member Fucntions
    bool is_full() const { return size() == capacity(); }
    void build(const StrVec& rhs);
    void free();
    void reallocate();
};

void StrVec::build(const StrVec& rhs)
{
    head = curr = alloc.allocate(rhs.capacity());
    tail = head + rhs.capacity();
    for (std::string* sp = rhs.head; sp != rhs.curr; ++sp, ++curr) {
        alloc.construct(curr, *sp);
    }
}

void StrVec::free()
{
    if (head != nullptr) {
        for (std::string* sp = head; sp != curr; ++sp) alloc.destroy(sp);
        alloc.deallocate(head, capacity());
        head = curr = tail = nullptr;
    }
}

StrVec::StrVec(const StrVec& rhs)
{
    build(rhs);
}

StrVec::StrVec(const std::initializer_list<std::string>& slis)
{
    std::size_t capa = slis.size() * 2;
    head = alloc.allocate(capa);
    curr = head;
    tail = head + capa;
    for (const std::string& s : slis) {
        alloc.construct(curr++, s);
    }
}

StrVec& StrVec::operator = (const StrVec& rhs)
{
    if (this != &rhs) {
        free();
        build(rhs);
    }
    return *this;
}

StrVec::~StrVec()
{
    free();
}

void StrVec::push_back(const std::string& s)
{
    if (is_full()) { reallocate(); }
    alloc.construct(curr++, s);
}

void StrVec::reallocate()
{
    std::allocator<std::string> new_alloc;
    std::size_t new_capa = capacity() ? capacity() * 2 : 1;
    std::string* new_head = new_alloc.allocate(new_capa);
    std::string* new_curr = new_head;
    std::string* new_tail = new_head + new_capa;
    for (std::string* sp = head; sp != curr; ++sp, ++new_curr) {
        new_alloc.construct(new_curr, *sp);
    }
    free();
    alloc = new_alloc;
    head = new_head;
    curr = new_curr;
    tail = new_tail;
}

void StrVec::reserve(std::size_t new_capa)
{
    if (new_capa != 0) {
        free();
        head = curr = alloc.allocate(new_capa);
        tail = head + new_capa;
    }
}

void StrVec::resize(std::size_t new_sz)
{
    if (new_sz == 0) {
        free();
    } else {
        std::allocator<std::string> new_alloc;
        std::string* new_head = new_alloc.allocate(new_sz);
        std::string* new_curr = new_head;
        std::string* new_tail = new_head + new_sz;
        for (std::string* sp = head; sp != curr && new_curr != new_tail; ++sp, ++new_curr) {
            new_alloc.construct(new_curr, *sp);
        }
        free();
        alloc = new_alloc;
        head = new_head;
        curr = new_curr;
        tail = new_tail;
    }
}

void StrVec::show_info() const
{
    std::cout << "******************************" << std::endl;
    std::cout << "Capacity: " << capacity() << std::endl;
    std::cout << "Size: " << size() << std::endl;
    std::cout << "******************************" << std::endl;
    std::cout << "Elements: " << std::endl;
    for (std::string* sp = head; sp != curr; ++sp) {
        std::cout << *sp << std::endl;
    }
    std::cout << "******************************" << std::endl;
}