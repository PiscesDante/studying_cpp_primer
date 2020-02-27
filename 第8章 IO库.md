# 第8章 `IO`库

## 8.1 `IO`类

目前为止，使用过的 `IO` 类型和对象都是操纵 `char` 数据的。这些对象默认都是关联到 **控制台窗口** 的。接下来我们需要从文件中进行读写。使用 `IO` 操作处理 `string` 中的字符会很方便。

* `iostream` ：定义了用于读写 **流** 的基本类型。
* `fstream` ：定义了读写命名文件的类型。
* `sstream` ：定义了读写内存 `string` 对象的类型。

#### `IO` 类型间的关系

简而言之，继承关系。我们之前是如何使用 `std::cout` 对象的，也可以同样使用接下来的 `IO` 对象。

### 8.1.1 `IO` 对象无拷贝或赋值

禁止拷贝 `IO` 对象或者对其赋值：

```C++
std::ofstream out1, out2;
out1 = out2; // 错误：不能对流对象赋值
ofstream print(ofstream); // 错误：不能初始化 ofstream 参数
out2 = print(out2); // 错误：不能拷贝流对象
```

**进行 `IO` 操作的函数只能以引用方式传递和返回流** 。

### 8.1.2 条件状态

一个流一旦发生错误，对其的后续的 `IO` 操作都会失败。只有当一个流处于正常状态时，我们才可以读写数据。因为在使用一个 `IO` 对象之前，应当先检查其状态是否正常：

```C++
while (std::cin >> word)
    // ok: reading...
```

#### 查询流的状态

#### 管理条件状态

`clear` 不接受参数的版本清除所有的错误标志。执行 `clear()` 之后，调用 `good` 会返回 `true` 。我们可以这样使用这些成员：

```C++
// 记住 std::cin 的当前状态
auto old_state = std::cin.rdstate();
std::cin.clear(); // clear all error states
process_input(std::cin); // use std::cin
std::cin.setstate(old_state); // set std::cin to the old state
```

### 8.1.3 管理输出缓冲

每个输出流都管理一个缓冲区，用来保存程序读写的数据。

```C++
os << "please enter a value: ";
```

文本串可能立即打印出来，但也有可能被操作系统保存在缓冲区中，随后再打印。

导致缓冲区被刷新的原因：

* 程序正常结束，作为 `main` 函数的 `return` 操作的一部分，缓冲刷新被执行。
* 缓冲区满，需要刷新后才能继续写入。
* 使用 `std::endl` 等操作符进行刷新。

#### 刷新输出缓冲区

`IO` 库中还有两个类似的操纵符：
* `std::flush` ：刷新缓冲区，但是不输出任何额外的字符。
* `std::ends` ：向缓冲区插入一个空字符，然后刷新缓冲区。

#### `unitbuf` 操纵符

如果想在每次输出操作后都刷新缓冲区，我们可以使用 `unitbuf` 操纵符。该操纵符告诉流在接下来的每次写操作之后都进行一次 `flush` 操作。而 `nounitbuf` 操纵符则重置流，使其恢复使用正常的系统管理的缓冲区刷新机制：

```C++
std::cout << std::unitbuf; // 所有输出操作后立即刷新缓冲区
// 任何输出都会立即刷新，无缓冲
std::cout << std::nounitbuf; // 回到正常的缓冲方式
```

> **如果程序崩溃，输出缓冲区不会被刷新** 。

#### 关联输入和输出流

**<u>当一个输入流被关联到一个输出流时，任何试图从输入流读取数据的操作都会先刷新关联的输出流</u>** 。

> 交互式系统通常应当关联输入流和输出流。这意味着 **所有输出，包括用户提示信息，都会在读操作之前被打印出来** 。

`tie` 函数有两个重载的版本：
* 不带参数，返回指向输出流的指针（可能是空指针）。
* 接受一个指向 `std::ostream` 的指针，将自己关联到这个 `std::ostream` 上。即， `strm.tie(&o)` 表示将流 `strm` 关联到输出流 `o` 。这个 `strm` 既可以是输入流，也可以是输出流。

```C++
std::cin.tie(&std::cout);
std::ostream* old_tie = std::cin.tie(nullptr);
std::cin.tie(&std::cerr);
std::cin.tie(old_tie); 
```

## 8.2 文件输入输出

头文件 `<fstream>` 定义了三个类型来支持文件 `IO` ：
* `ifstream` ：从给定的文件读取数据。
* `ofstream` ：向给定的文件写入数据。
* `fstream` ：读写指定的文件。

### 8.2.1 使用文件流对象

```C++
// 创建文件流对象时，我们可以直接提供文件名（可选）
// 如果提供了一个文件名，那么 open 函数会被自动调用
std::ifstream read_in(filename);
// 这里已经自动调用 open 函数打开了文件 filename
std::ofstream write_out; // 输出文件流未关联到任何文件
```

在 C++ 新标准中，**文件名既可以是 `std::string` ，也可以是 C 风格的字符串** 。

#### 用 `std::fstream` 代替 `std::iostream&`

在要求使用基类型的地方，我们也可以使用其派生类型的对象来代替。也就是说，接受一个 `std::iostream&` 的函数，也可以传递 `std::fstream&` 类型来调用。

```C++
std::ifstream input(argv[1]); // 打开销售记录文件
std::ofstream output(argv[2]); // 打开输出文件
Sales_data total;
if (read(input, total)) {
    Sales_data trans;
    while (read(input, trans)) {
        if (total.isbn() == trans.isbn()) {
            total.combine(trans);
        } else {
            print(output, total) << std::endl;
            total = trans;
        }
    }
    print(output, total) << std::endl;
} else {
    std::cerr << "No Data." << std::endl;
}
```

#### 成员函数 `open` 和 `close`

如果我们定义了一个空文件流对象，可以调用 `open` 将它与文件关联起来：

```C++
std::ifstream read_in(filename);
std::ofstream write_out;
write_out.open(filename); // 关联到 filename
```

如果 `open` 失败，可以检查流对象的状态来确定：

```C++
if (write_out) // 测试文件是否成功打开
```

#### 自动构造和析构

> 当一个 `fstream` 对象被销毁时， `close` 会自动被调用。

### 8.2.2 文件模式

每一个流都有一个关联的 **文件模式** ，用来指出如何使用文件。调用 `open` 时以及初始化时指定都可以。

#### 以 `out` 模式打开文件会丢弃已有数据

默认情况下，当我们打开一个 `ofstream` 时，文件的内容会被丢弃。阻止一个 `ofstream` 清空给定文件内容的方法是 **同时指定 `app` 模式** ：

```C++
// 在这几条语句中，file 都被截断
std::ofstream out("file"); // 隐含以输出模式打开文件并截断文件
std::ofstream out("file", std::ofstream::out); // 隐含的截断文件
std::ofstream out("file", std::ofstream::out | std::ofstream::trunc);
// 为了保留文件内容，我们必须显式指定 app 模式
std::ofstream out("file", std::ofstream::app); // 隐含为输出模式
std::ofstream out("file", std::ofstream::out | std::ofstream::app);
```

> 保留被 `std::ofstream` 打开的文件中已有数据的唯一方法时显式指定 `app` 或者 `in` 模式。

#### 每次调用 `open` 时都会确定文件模式

```C++
std::ofstream out; // 写文件流对象，未关联
out.open("scratchpad"); // 模式隐含设置为 输出 和 截断
out.close();
out.open("precious", std::ofstream::app); // 模式为输出和追加
out.close();
```

> 每次打开文件时，都要设置文件模式，可能是显式的设置，也可能是隐式的设置。当程序未指定模式时，就使用默认值。

## 8.3 `string` 流

`<sstream>` 头文件定义了三个类型来支持内存 `IO` ，这些类型可以向 `std::string` 写入数据，从 `std::string` 读取数据，就像 `std::string` 是一个 `IO` 流一样。

### 8.3.1 使用 `istringstream`

当我们的某些工作是对整行的文本进行处理，而其他一些工作是处理行内的单词时。

例如，文件中的每条记录都以一个人名开始，后面跟随一个或者多个电话号码。我们首先定义一个简单地类来描述输入数据：

```C++
struct PersonInfo {
    std::string name;
    std::vector<std::string> phones;
};

std::string line, word;
std::vector<PersonInfo> people;
// 逐行从输入读取数据，直到文件末尾或错误
while (getline(std::cin, line)) {
    PersonInfo info;
    std::istringstream record(line);
    record >> info.name;
    while (record >> word) info.phones.push_back(word);
    people.push_back(info);
}
```

### 8.3.2 使用 `ostringstream`

逐步构造输出，最后一起打印。

还是一样的流程，使用一个 `string` 对象来初始化这个流，然后逐步输出。

```C++
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