## c++14 特性
> 参考：https://en.cppreference.com/w/cpp/14


## New language features
### variable templates
```c++
#include <iostream>
template <typename T>
constexpr T pi = T(3.1415926535897932385);

double radius = 5.0;
double area = pi<double> * radius * radius;
```
### generic lambdas
泛型lambda允许我们在lambda表达式中使用自动推导的参数类型
```c++
int multiplier = 2;
auto multiply = [multiplier](auto num) { return num * multiplier; };

multiply(123);
```
### lambda init-capture
初始化捕获允许我们在lambda表达式中使用初始化语句来捕获外部变量，从而使得捕获更加灵活和方便。
```c++
int x = 5;
int y = 10;
auto sum = [z = x + y]() { return z; };
```

### new/delete elision
C++14中的new/delete elision通过优化这些开销来提高性能。具体来说，它允许编译器在某些情况下省略对new和delete运算符的调用，从而避免了不必要的开销
```c++
// 1) 在C++14中，编译器可以通过省略对new和delete运算符的调用来优化这个过程，直接将局部对象的值复制到函数调用的结果中。
std::string createString() {
    std::string str = "Hello, World!";
    return str;
}
// 2) 编译器可以通过省略对new和delete运算符的调用来优化这个过程，直接将临时对象的值复制到变量str中。
// 需要注意的是，new/delete elision是一种编译器优化技术，具体是否发生取决于编译器的实现。
std::string str = std::string("Hello, World!");

```

### relaxed restrictions on constexpr functions
在C++14中，对constexpr函数的限制进行了放宽，使得我们可以在更多的情况下使用constexpr函数。

在C++11中，constexpr函数有一些限制，例如：
- 入参：函数参数必须是字面值类型。
- 函数体：函数体中不能包含任何的局部变量定义。
- 返回：函数体必须只包含一条返回语句。

而在C++14中，对这些限制进行了放宽，具体变化如下：
- 函数体可以包含多条语句，而不仅限于一条返回语句。
- 函数体中可以包含局部变量定义，但这些变量必须是constexpr类型，并且必须在编译时就能够确定其值。
- 函数参数可以是任意类型，而不仅限于字面值类型。


### binary literals
在C++14中，引入了二进制字面值（binary literals）的特性，使得我们可以直接在代码中使用二进制表示数字。
```
int decimal = 10;       // 十进制表示，值为10
int octal = 012;        // 八进制表示，值为10
int hexadecimal = 0xA;  // 十六进制表示，值为10

int binary = 0b1010;    // 二进制表示，值为10
```
### digit separators
在C++14中，引入了数字分隔符（digit separators）的特性，使得我们可以在数字中插入下划线来提高数字的可读性。
```
int million = 1'000'000;  // 一百万

```
### return type deduction for functions
在C++14中，引入了函数返回类型推导（return type deduction）的特性，使得我们可以在函数定义时省略返回类型，并让编译器根据函数体中的返回语句推导出返回类型。
```
auto add(int a, int b) {
    return a + b;
}

```
### aggregate classes with default non-static member initializers.
在C++14中，引入了聚合类（aggregate class）的概念，并允许在聚合类中使用默认的非静态成员初始化器（default non-static member initializers）。

聚合类是指满足以下条件的类：
- 所有非静态成员都是公有的。
- 没有用户提供的构造函数。
- 没有基类或虚函数。
- 没有默认成员初始化器（default member initializers）。

```c++
// 之前
class Point {
public:
    int x;
    int y;
    
    Point() : x(0), y(0) {}
};

// c++14 
class Point {
public:
    int x = 0;
    int y = 0;
};

```

## New library features
### std::make_unique
在C++14中，标准库引入了一个新的函数模板 std::make_unique，用于创建动态分配的对象，并返回一个 std::unique_ptr 智能指针来管理该对象的生命周期。
```c++

std::unique_ptr<MyClass> ptr = std::make_unique<MyClass>(42);
ptr->print();
```

### std::shared_timed_mutex and std::shared_lock
在C++14中，标准库引入了两个与多线程相关的类：std::shared_timed_mutex 和 std::shared_lock。

std::shared_timed_mutex 是一个互斥量，用于实现共享所有权的读写锁。它允许多个线程同时读取共享数据，但只允许一个线程写入共享数据。与 std::mutex 不同，std::shared_timed_mutex 允许多个线程同时获取共享锁，而不会阻塞彼此。只有当一个线程持有独占锁时，其他线程才会被阻塞。

std::shared_lock 是一个轻量级的共享锁，用于在读取共享数据时获取共享锁。它允许多个线程同时获取共享锁，并且不会阻塞彼此。与 std::unique_lock 不同，std::shared_lock 不拥有互斥量的所有权，因此它只能用于读取共享数据，而不能用于写入共享数据。

```c++
#include <iostream>
#include <thread>
#include <shared_mutex>

std::shared_timed_mutex mutex;
int sharedData = 0;

void reader() {
    std::shared_lock<std::shared_timed_mutex> lock(mutex);
    std::cout << "Reader: " << sharedData << std::endl;
}

void writer() {
    std::unique_lock<std::shared_timed_mutex> lock(mutex);
    sharedData++;
    std::cout << "Writer: " << sharedData << std::endl;
}

int main() {
    std::thread t1(reader);
    std::thread t2(reader);
    std::thread t3(writer);
    std::thread t4(reader);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    return 0;
}
```

### std::integer_sequence
std::integer_sequence 是在 C++14 中引入的一个模板类，用于表示整数序列。它主要与可变参数模板一起使用，用于在编译时进行计算。
```c++
template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
    std::cout << "The sequence of size " << int_seq.size() << ": ";
    ((std::cout << ints << ' '), ...);
    std::cout << '\n';
}

print_sequence(std::integer_sequence<unsigned, 9, 2, 5, 1, 9, 1, 6>{});
```

### std::exchange
用于交换一个对象的值，并返回原始值。
```c++
#include <utility>

int x = 10;
int y = std::exchange(x, 20);
```

### std::quoted
使用 std::quoted 可以方便地将字符串包装在引号中，这在某些情况下非常有用
```c++

#include <iostream>
#include <iomanip>
int main() {
    std::string str = "Hello, World!";
    
    std::cout << std::quoted(str) << std::endl; // 输出: "Hello, World!"
    
    return 0;
}

```

### and many small improvements to existing library facilities, such as
two-range overloads for some algorithms
type alias versions of type traits
user-defined literals for basic_string, duration and complex



