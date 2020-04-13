#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <utility>
#include <iostream>

// 非类型参数 HEIGHT & WIDTH
template <std::size_t WIDTH, std::size_t HEIGHT>
class Screen {
template <std::size_t W, std::size_t H>
friend std::ostream& operator << (std::ostream& os, const Screen<W, H>& rhs);
public:
    Screen();
    // Screen(const Screen& rhs);
    std::size_t get_width() const { return WIDTH; }
    std::size_t get_height() const { return HEIGHT; }
    void set_char(std::size_t row, std::size_t col, char ch);
private:
    std::size_t width;
    std::size_t height;
    char screen[HEIGHT][WIDTH];
};

// 模板友元：同样需要非类型模板参数
template <std::size_t W, std::size_t H>
std::ostream& operator << (std::ostream& os, const Screen<W, H>& rhs)
{
    for (std::size_t row = 0; row < H; ++row) {
        for (std::size_t col = 0; col < W; ++col) {
            os << rhs.screen[row][col];
        }
        os << std::endl;
    }
    return os;
}

template <std::size_t HEIGHT, std::size_t WIDTH>
Screen<HEIGHT, WIDTH>::Screen() : width(WIDTH), height(HEIGHT)
{
    for (std::size_t i = 0; i < WIDTH; ++i) {
        for (std::size_t j = 0; j < HEIGHT; ++j) { screen[i][j] = '#'; }
    }
}

#endif