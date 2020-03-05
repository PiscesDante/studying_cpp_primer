class StrVec {
public:
    StrVec() :
        head(nullptr), curr(nullptr), tail(nullptr),
        sz(0), capa(0) {  }
    StrVec(const StrVec& rhs);
    StrVec& operator = (const StrVec& rhs);
private:
    std::allocator<std::string> alloc;
    std::string* head;
    std::string* curr;
    std::string* tail;
    std::size_t sz;
    std::size_t capa;
private:
    void build(const StrVec& rhs);
};

void StrVec::build(const StrVec& rhs)
{
    sz = rhs.sz;
    capa = rhs.capa;
    curr = head = alloc.allocate(capa);
    tail = head + capa - 1;
    auto temp = rhs.head;
    for (std::size_t i = 0; i <= sz; ++i, ++curr) {
        alloc.construct(curr, *(rhs.head));
    }
}

StrVec::StrVec(const StrVec& rhs)
{
    build(rhs);
}

StrVec& StrVec::operator = (const StrVec& rhs)
{
    if (this != &rhs) {
        free();
        build(rhs);
    }
    return *this;
}