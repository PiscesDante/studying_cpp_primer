# 8.1.2 节练习

## 练习 8.1

> 编写函数，接受一个 `std::istream&` 参数，返回值类型也是 `std::istream&` 。此函数须从给定流中读取数据，直至遇到文件结束标识时停止。它将读取的数据打印在标准输出上。完成这些操作后，在返回流之前，对流进行复位，使其处于有效的状态。

解答：

```C++
std::istream& func(std::istream& is) {
    char ch;
    while (is >> ch) std::cout << ch;
    is.clear();
    return is;
}
```

## 练习 8.2

> 测试函数，调用参数为 `std::cin` 。

解答：

```C++
#include <iostream>

std::istream& func(std::istream& is)
{
    char ch;
    while (is >> ch) std::cout << ch;
    is.clear();
    return is;
}

int main(int argc, char const *argv[])
{
    func(std::cin);
    return 0;
}
```

## 练习 8.3

> 什么情况下，下面的 `while` 循环会终止？

```C++
while (cin >> i) { ... }
```

解答：

当 `std::cin` 处于不可用状态下就会停止，比如说  `eofbit` ，`failbit` 或者 `badbit` 。

# 8.2.1 节练习

## 练习 8.4

> 编写函数，以读模式打开一个文件，将其内容读入到一个 `std::string` 的 `std::vector` 中，将每一行作为一个独立的元素存在 `vector` 中。

解答：

```C++
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
    std::vector<std::string> article;
    std::string filename { "any_text_file.txt" };
    std::ifstream in_stream(filename);
    while (in_stream) {
        std::string line;
        getline(in_stream, line);
        article.push_back(line);
    }
    return 0;
}
```

## 练习 8.5

> 重写上面的程序，将每个单词作为一个独立的元素进行存储。

解答：

```C++
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
    std::vector<std::string> article;
    std::string filename { "any_text_file.txt" };
    std::ifstream in_stream(filename);
    std::string word;
    while (in_stream >> word) article.push_back(word);
    return 0;
}
```

## 练习 8.6

> 重写 7.1.1 节的书店程序（第 229 页），从一个文件中读取交易记录。将文件名作为一个参数传递给 `main` （参见 6.2.5 节，第 196 页）。

解答：

```C++
Sales_data total;
std::ifstream input_file(argv[1]);
if (read(input_file, total)) {
    Sales_data trans;
    while (read(input_file, trans)) {
        if (total.isbn() == trans.isbn()) {
            total.combine(trans);
        } else {
            print(std::cout, total) << std::endl;
            total = trans;
        }
    }
    print(std::cout, total) << std::endl;
} else {
    std::cerr << "No Data" << std::endl;
}
input_file.close();
```

# 8.2.2 节练习

## 练习 8.7

> 修改上一节的书店程序，将结果保存到一个文件中。将输出文件名作为第二个参数传递给 `main` 函数。

解答：

```C++
Sales_data total;
std::ifstream input_file(argv[1]);
std::ofstream output_file(argv[2]);
if (read(input_file, total)) {
    Sales_data trans;
    while (read(input_file, trans)) {
        if (total.isbn() == trans.isbn()) {
            total.combine(trans);
        } else {
            print(output_file, total) << std::endl;
            total = trans;
        }
    }
    print(output_file, total) << std::endl;
} else {
    std::cerr << "No Data" << std::endl;
}
input_file.close();
output_file.close();
```

## 练习 8.8

> 修改上一题的程序，将结果追加到给定的文件末尾。对同一个输出文件，运行程序至少两次，检验数据是否得以保存。

解答：

```C++
Sales_data total;
std::ifstream input_file(argv[1]);
std::ofstream output_file;
output_file.open(argv[2], std::ofstream::out | std::ofstream::app);
if (read(input_file, total)) {
    Sales_data trans;
    while (read(input_file, trans)) {
        if (total.isbn() == trans.isbn()) {
            total.combine(trans);
        } else {
            print(output_file, total) << std::endl;
            total = trans;
        }
    }
    print(output_file, total) << std::endl;
} else {
    std::cerr << "No Data" << std::endl;
}
input_file.close();
output_file.close();
```

# 8.3.1 节练习

## 练习 8.9

> 使用你为 8.1.2 节（第 281 页）第一个练习所编写的函数打印一个 `istringstream` 对象的内容。

解答：

```C++
#include <iostream>
#include <sstream>
#include <string>

std::istream& func(std::istream& is)
{
    std::string s;
    while (is >> s) std::cout << s << std::endl;
    is.clear();
    return is;
}

int main(int argc, char* argv[])
{
    std::istringstream iss { "Here is the thing" };
    func(iss);
    return 0;
}
```

## 练习 8.10

> 编写程序，将来自一个文件中的行保存在一个 `std::vector<std::string>` 中。然后使用一个 `istringstream` 从 `vector` 读取元素，每次读取一个单词。

解答：

```C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
    std::vector<std::string> text;
    std::ifstream ifs("GettysburgAddress.txt");
    std::string line;
    while (getline(ifs, line)) {
        text.push_back(line);
    }
    for (const std::string& line : text) {
        std::istringstream ls(line);
        std::string word;
        while (ls >> word) {
            std::cout << word << std::endl;
        }
    }
    ifs.close();
    return 0;
}
```

## 练习 8.11

> 本节的程序在外层 `while` 循环中定义了 `istringstream` 对象。如果 `record` 对象定义在循环之外，你需要对程序进行怎样的修改？重写程序，将 `record` 的定义移到 `while` 循环之外，验证你的想法是否正确。

解答：

```C++
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

int main(int argc, char* argv[])
{
    std::string line;
    std::string phone_number;
    std::vector<PersonInfo> people;
    std::istringstream record;
    std::ifstream read_stream("Records.txt");
    while (getline(read_stream, line)) {
        PersonInfo info;
        record.str(line);
        record >> info.name;
        while (record >> phone_number) {
            info.phones.push_back(phone_number);
        }
        people.push_back(info);
        record.clear(); // 这里一定要重置
    }
    for (const auto& person : people) {
        std::cout << person.name;
        std::cout << " : ";
        for (const auto& phone_number : person.phones) {
            std::cout << phone_number << " | ";
        }
        std::cout << std::endl;
    }
    return 0;
}
```

## 练习 8.12

> 我们为什么没有在 `PersonInfo` 中使用内类初始化？

解答：

如果不使用类内初始值，`PersonInfo` 就可以被当作聚合类来使用。

# 8.3.2 节练习

## 练习 8.13

> 重写本节的电话号码程序，从一个命名文件而非 `std::cin` 读取数据。

解答：

```C++
// struct PersonInfo {
//     std::string name;
//     std::vector<std::string> phones;
// };

std::vector<PersonInfo> people;
std::ifstream read_file_stream("Records.txt");
std::string record;
while (getline(read_file_stream, record)) {
    PersonInfo info;
    std::istringstream iss(record);
    iss >> info.name;
    std::string phone_number;
    while (iss >> phone_number) {
        info.phones.push_back(phone_number);
    }
}

for (const auto& entry : people) {
    std::ostringstream formatted, badNums;
    for (const auto& nums : entry.phones) {
        if (!valid(nums)) {
            badNums << " " << nums;
        } else {
            formatted << " " << format(nums);
        }
    }
    if (badNums.str().empty()) {
        os << entry.name << " " << formatted.str() << std::endl;
    } else {
        cerr << "input error: " << entry.name
            << "invalid number(s)" << badNums.str() << std::endl;
    }
}
```

## 练习 8.14

> 我们为什么将 `entry` 和 `nums` 定义为 `const auto&` ？

解答：

* 为了防止内容在程序中被修改。
* 对于标准库类型来说，运行更加高效。
* 当容器中存储的是常量对象时，程序也能正常的工作。