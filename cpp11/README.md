## c++11 特性
> 参考：https://en.cppreference.com/w/cpp/11


## 1.语言层面
### 1.1 新增的类型
#### nullptr
```c++
int *p = nullptr;
```
#### long long
```c++
long long ll = 1;
```
#### char16_t and char32_t
```c++

```

#### Unicode string literals
Unicode string literals是指在C++中使用Unicode字符的字符串字面量。在C++11之前，C++中的字符串字面量只支持ASCII字符集，无法直接表示Unicode字符。然而，C++11引入了一种新的字符串字面量前缀u8、u、U和L，用于支持不同的Unicode编码方式。
u8前缀用于表示UTF-8编码的字符串字面量。例如：u8"Hello, 世界"。
u前缀用于表示UTF-16编码的字符串字面量。例如：u"Hello, 世界"。
U前缀用于表示UTF-32编码的字符串字面量。例如：U"Hello, 世界"。
L前缀用于表示宽字符编码的字符串字面量。例如：L"Hello, 世界"。

#### user-defined literals
User-defined literals（用户自定义字面量）是C++11引入的一项功能，允许程序员自定义字面量的解释和使用方式。通过定义自己的字面量后缀
```c++

#include <iostream>
// 自定义字面量后缀 "_m" 表示米
constexpr long double operator"" _m(long double meters) {
    return meters;
}

int main() {
    // 使用自定义字面量
    long double distance = 10.5_m;
    std::cout << "Distance: " << distance << " meters" << std::endl;
    return 0;
}
```


### 1.2 新增的修饰符
#### constexpr
```c++
//constexpr 说明符声明编译时可以对函数或变量求值。
constexpr int factorial(int n)
{
    return n <= 1 ? 1 : (n * factorial(n #### 1));
}
```

#### default
```c++
class A {
    A() = default;
};
```

#### delete
```c++
class A {
    A() = delete;
};
```

#### final
```c++
struct Base
{
    virtual void foo();
};
// 1）修饰类
struct B final : A{};

// 2) 修饰函数
struct A : Base
{
    void foo() final; // Base::foo 被覆盖而 A::foo 是最终覆盖函数
    void bar() final; // 错误：bar 非虚，因此它不能是 final 的
};
```

#### override
```c++
struct A
{
    virtual void foo();
    void bar();
};
 
struct B : A
{
    void foo() const override; // 错误：B::foo 不覆盖 A::foo （签名不匹配）【注意！！！】
    void foo() override; // OK：B::foo 覆盖 A::foo
    void bar() override; // 错误：A::bar 非虚
};

```

#### noexcept
函数声明或定义中的noexcept关键字用于指示函数不会抛出异常。
如果函数在运行时抛出了异常，std::terminate()函数会被调用来终止程序。
```
void func() noexcept; // 声明一个不会抛出异常的函数

void func() noexcept { // 定义一个不会抛出异常的函数
    // 函数体
}

// noexcept运算符用于在编译时检查表达式是否可能抛出异常。
void func() {
    int a = 10;
    int b = 0;
    int c = noexcept(a / b); // c的值为false，因为除以0会抛出异常
}

```

#### alignof and alignas
alignof和alignas是C++11引入的关键字，用于控制和查询对象的对齐方式。
alignof关键字用于查询类型或表达式的对齐要求。
```c++
alignas(8) struct MyStruct {
    int a;
    char b;
};

size_t alignment = alignof(MyStruct); // 查询MyStruct的对齐要求，alignment的值为8

```


#### attributes
C++11引入了一项新的特性——属性（Attributes），它允许程序员向代码中的声明添加额外的信息，以改变其行为或提供其他指示。属性可以用于函数、变量、类型、命名空间等各种声明。
C++11中的属性使用方括号 `[[ ]]` 来表示，放置在声明的名称之前。以下是一些常用的C++11属性：

1) `[[maybe_unused]]`：用于标记未使用的函数、变量或参数。编译器会在未使用的声明时发出警告。
```c++
[[maybe_unused]] void unusedFunc();
```

2) `[[deprecated]]`：用于标记已过时的函数、变量或类型。编译器会在使用过时的声明时发出警告。
```c++
[[deprecated]] void oldFunc();
```

3) `[[noreturn]]`：用于函数声明，表示函数不会返回。
```c++
[[noreturn]] void func();
```

4) `[[nodiscard]]`：用于函数或类型声明，表示函数返回值或类型的对象不应该被忽略。编译器会在忽略返回值或对象时发出警告。
```
[[nodiscard]] int getValue();
```

5) `[[fallthrough]]`：用于在switch语句中标记意图的穿透（fallthrough）。编译器会在没有显式的break语句时发出警告。
```c++
switch (value) {
    case 1:
        doSomething();
        [[fallthrough]];
    case 2:
        doSomethingElse();
        break;
}
```



### 1.3 变量或函数的定义
#### rvalue references
```c++
    std::string&& r3 = s1 + s1;      // okay: rvalue reference extends lifetime
    r3 += "Test";                    // okay: can modify through reference to non-const
    std::cout << r3 << '\n';
```

#### auto 
```c++
// 1) 变量
auto a = 1 + 2;          // a 的类型是 int
auto b = add(1, 1.2);    // b 的类型是 double
decltype(auto) c1 = a;   // [c++14]

// 2）lambda
auto lambda = [](int x) { return x + 3; };

// 3）模版
template<class T, class U>
auto add(T t, U u) { return t + u; } // 返回类型是 operator+(T, U) 的类型
```
#### decltype
```c++
// 1）变量
int i = 33;
decltype(i) j = i * 2;

// 2）函数或表达式
auto f = [i](int a, int b) -> int { return a * b + i; };
decltype(f) g = f;
```

#### list initialization
```c++
std::vector<int> mem = {1, 2, 3}; // list-initialization of a non-static member
```

#### brace-or-equal initializers
C++11引入了一种新的初始化语法，称为"brace-or-equal initializers"（花括号或等号初始化器）。这个特性允许在类的成员变量声明中使用花括号或等号来进行初始化。
```c++
class MyClass {
public:
    int x = 0;  // 使用等号初始化器进行初始化
    int y{5};  // 使用花括号初始化器进行初始化
};

```

#### type aliases
```c++
using MyInt = int;  // 定义一个类型别名MyInt，表示int类型
typedef double Distance;  // 传统的typedef方式定义一个类型别名Distance，表示double类型
```

#### trailing return type
```c++
// function returning a pointer to f0, with C++11 trailing return type
auto fp11() -> void(*)(const std::string&)
{
    return f0;
}
 
```

#### lambda expressions
```c++
auto f = [r1&, c_i](int i){return 0};

f(1);
```

#### static_assert
C++11引入了static_assert关键字，它用于在编译时进行静态断言（static assertion）。静态断言是一种在编译时检查条件是否满足的机制，如果条件不满足，则会导致编译错误。

```c++
#include <iostream>
template <typename T>
void process(T value) {
    // 静态断言：检查类型T是否为整数类型
    static_assert(std::is_integral<T>::value, "T must be an integral type");
    // 处理逻辑...
    std::cout << "Processing value: " << value << std::endl;
}

int main() {
    process(10);  // 正常调用，T为整数类型
    process(3.14);  // 编译错误，T不是整数类型
    return 0;
}

```


### 1.4 class相关
#### move constructors and move assignment operators
```c++
// 语法
class-name (class-name && ); //(since C++11)

class-name && class-name::operator=(class-name &&);	//(1)	(since C++11)
```

#### scoped enums
```c++

 enum class E1 : int {A=1, B=2};

int i = static_cast<int>(E1::A);
```

#### delegating and inherited constructors
C++11引入了两个与构造函数相关的新特性：委托构造函数（Delegating Constructors）和继承构造函数（Inherited Constructors）。
```c++
// 委托构造函数（Delegating Constructors）
class MyClass {
public:
    MyClass(int x, int y) {
        // 构造函数的具体实现
    }
    
    MyClass(int x) : MyClass(x, 0) {
        // 委托给另一个构造函数来完成初始化
    }
};


// 继承构造函数（Inherited Constructors）
class Base {
public:
    Base(int x) {
        // 构造函数的具体实现
    }
};

class Derived : public Base {
public:
    using Base::Base;  // 继承Base类的构造函数
};
```


#### generalized (non-trivial) unions
C++11引入了一种新的特性，称为"generalized (non-trivial) unions"（广义（非平凡）联合体）。在C++11之前，联合体（union）只能包含一种数据类型的成员变量，而且这些成员变量不能有非平凡的构造函数、析构函数和拷贝赋值运算符。然而，C++11通过引入广义联合体的概念，允许联合体包含具有非平凡特性的成员变量。
```c++
union MyUnion {
    int i;
    double d;

    MyUnion() {}
    ~MyUnion() {}
};

```

#### generalized PODs (trivial types and standard-layout types)
C++11引入了一种新的概念，称为"generalized PODs"（广义POD）。POD（Plain Old Data）是指在C++中可以以C语言方式进行内存布局和操作的数据类型。在C++11之前，POD类型包括标量类型（如整型、浮点型）、POD类和数组。然而，C++11通过引入广义POD的概念，扩展了POD类型的范围，包括了"trivial types"（平凡类型）和"standard-layout types"（标准布局类型）。

平凡类型（trivial types）是指具有以下特性的类型：
- 没有非平凡的默认构造函数、拷贝构造函数、移动构造函数、拷贝赋值运算符和移动赋值运算符；
- 没有虚函数；
- 没有虚基类；
- 没有虚析构函数。
- 标准布局类型（standard-layout types）是指具有以下特性的类型：
- 所有非静态成员都具有相同的访问权限（public、protected或private）；
- 所有非静态成员都具有相同的访问权限，并且在类中以相同的顺序声明；
- 类中没有虚函数、虚基类或虚析构函数；
- 类中没有非静态成员对象或非静态成员引用。

广义POD类型可以用于各种场景，如内存映射、网络通信和序列化等。在C++11中，可以使用std::is_pod类型特性来检查一个类型是否是广义POD类型。
下面是一个使用广义POD类型的示例：
```c++
#include <iostream>
#include <type_traits>
struct Point {
    int x;
    int y;
};

int main() {
    std::cout << std::boolalpha;
    std::cout << "Is Point a POD type? " << std::is_pod<Point>::value << std::endl;
    return 0;
}

```

### 1.5 模版
#### variadic templates
C++11引入了一种新的特性，称为"variadic templates"（可变参数模板）。可变参数模板允许定义接受任意数量参数的模板函数或类模板。
```c++
#include <iostream>
// 递归终止条件
void print() {
    std::cout << std::endl;
}
// 可变参数模板
template<typename T, typename... Args>
void print(T value, Args... args) {
    std::cout << value << " ";
    print(args...);  // 递归调用print函数
}
int main() {
    print(1, 2, 3, "hello", 4.5);
    return 0;
}

```


### 1.6 线程

#### multithreaded memory model
C++11的多线程内存模型主要包括以下几个方面：

1) 原子操作（Atomic Operations）：
C++11引入了原子类型（std::atomic），用于实现原子操作。
原子类型提供了一组原子操作，如加载（load）、存储（store）、交换（exchange）、比较交换（compare-and-swap）等。
原子操作可以保证在多线程环境下的原子性，避免竞态条件和数据竞争。

2) 内存顺序（Memory Ordering）：
C++11引入了内存顺序的概念，用于定义多线程程序中的内存访问顺序。
内存顺序规定了对共享变量的读写操作在多线程环境下的可见性和顺序。
C++11提供了一组内存顺序修饰符（memory order modifiers），如std::memory_order_relaxed、std::memory_order_acquire、std::memory_order_release等，用于指定不同的内存访问顺序。

3) 互斥量（Mutex）：
C++11引入了互斥量（std::mutex）和锁（std::lock_guard、std::unique_lock等）。
互斥量用于实现临界区的互斥访问，保证多线程环境下的数据同步和互斥操作。
锁用于在临界区中对互斥量进行加锁和解锁操作，确保只有一个线程可以进入临界区。

4) 条件变量（Condition Variable）：
C++11引入了条件变量（std::condition_variable）和条件变量锁（std::unique_lock）。
条件变量用于实现线程之间的同步和通信。
条件变量锁用于在等待条件变量时对互斥量进行加锁和解锁操作。

#### thread-local storage
```c++
#include <iostream>
#include <thread>
thread_local int tls_variable = 0;
void thread_function() {
    // 修改线程本地存储的变量
    tls_variable += 1;
    std::cout << "Thread local variable: " << tls_variable << std::endl;
}
int main() {
    // 创建多个线程
    std::thread t1(thread_function);
    std::thread t2(thread_function);
    std::thread t3(thread_function);
    // 等待线程结束
    t1.join();
    t2.join();
    t3.join();
    return 0;
}

```

#### GC interface (removed in C++23)
```c++

```

#### range-for (based on a Boost library)
```c++
std::vector<int> vct{1,2,3};
for(const auto& i : vct) {
}
```

## 2. Library features
### 2.1 Headers
```
<array>
<atomic>
<cfenv>
<chrono>
<cinttypes>
<condition_variable>
<cstdint>
<cuchar>
<forward_list>
<future>
<initializer_list>
<mutex>
<random>
<ratio>
<regex>
<scoped_allocator>
<system_error>
<thread>
<tuple>
<typeindex>
<type_traits>
<unordered_map>
<unordered_set>
```

### 2.2 Library features
#### concurrency support library

#### emplace() and other use of rvalue references throughout all parts of the existing library
```c++
std::vector<int> vct;
vct.emplace_back(1);

std::map<int,char> m;
m.emplace(1, 'a');
```

#### std::unique_ptr
```c++
std::unique_ptr<int> p_i = std::make_unique<int>(1);
p_i.get();

```

#### std::move_iterator
std::move_iterator是C++标准库中的一个迭代器适配器，定义在头文件<iterator>中。它用于将普通迭代器转换为移动迭代器，从而实现对容器中元素的移动语义操作。

移动迭代器是一种特殊的迭代器，它通过移动语义来避免不必要的拷贝操作，提高程序的性能。

```c++
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination;
    // 使用移动迭代器将source中的元素移动到destination中
    std::move_iterator<std::vector<int>::iterator> begin(std::begin(source));
    std::move_iterator<std::vector<int>::iterator> end(std::end(source));
    std::move(begin, end, std::back_inserter(destination));
    // 输出destination中的元素
    for (const auto& num : destination) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}

```

#### std::initializer_list
std::initializer_list是C++11引入的一种特殊类型，用于方便地初始化容器、数组和其他类型的对象。
std::initializer_list是一个模板类，定义在头文件<initializer_list>中。它表示一个不可修改的元素列表，类似于数组或容器，但没有提供修改元素的方法。它的主要作用是用于初始化对象。

```c++
#include <iostream>
#include <vector>
#include <initializer_list>

void printList(std::initializer_list<int> list) {
    for (auto it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    // 使用std::initializer_list初始化vector
    std::vector<int> vec = {1, 2, 3, 4, 5};
    for (const auto& num : vec) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 使用std::initializer_list初始化数组
    int arr[] = {6, 7, 8, 9, 10};
    for (const auto& num : arr) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    // 将多个元素作为std::initializer_list参数传递给函数
    printList({11, 12, 13, 14, 15});
    return 0;
}

```

#### stateful and scoped allocators
C++11引入了状态化分配器（stateful allocators）和作用域分配器（scoped allocators）的概念，用于更灵活地管理内存分配和释放。

1) 状态化分配器（Stateful Allocators）：
状态化分配器是一种分配器，它在分配和释放内存时需要维护一些状态信息。在C++11之前，分配器是无状态的，即它们不需要维护任何状态信息。但是，有些分配器可能需要在分配和释放内存时使用一些额外的信息，例如内存池的地址或其他配置参数。C++11引入了状态化分配器的概念，允许分配器在分配和释放内存时使用额外的状态信息。

2) 作用域分配器（Scoped Allocators）：
作用域分配器是一种分配器，它可以在特定的作用域内进行内存分配和释放。作用域分配器可以用于在特定的代码块或函数中管理内存，以便在离开该作用域时自动释放内存。作用域分配器可以避免手动管理内存的麻烦，并提供更安全和更高效的内存管理方式。

C++11中引入了std::allocator_traits模板类，它提供了一种通用的方式来处理状态化分配器和作用域分配器。std::allocator_traits提供了一组模板函数，用于在分配器上执行内存分配和释放操作。
使用状态化分配器和作用域分配器可以提供更灵活和高效的内存管理方式，特别是在需要自定义内存分配策略或在多线程环境中使用时。但是，使用这些特性需要对C++的内存管理机制有一定的了解，并且需要谨慎处理内存分配和释放的逻辑，以避免内存泄漏和其他内存相关的问题。

```c++

#include <iostream>
#include <memory>

// 自定义状态化分配器
template <typename T>
class MyAllocator {
public:
    using value_type = T;
    
    MyAllocator(int id) : id_(id) {}
    
    template <typename U>
    MyAllocator(const MyAllocator<U>& other) : id_(other.id_) {}

    T* allocate(std::size_t n) {
        std::cout << "Allocating " << n << " objects with allocator " << id_ << std::endl;
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating " << n << " objects with allocator " << id_ << std::endl;
        ::operator delete(p);
    }
private:
    int id_;
};

// 自定义作用域分配器
template <typename T>
class MyScopedAllocator {
public:
    using value_type = T;
    MyScopedAllocator() : buffer_(nullptr), size_(0), used_(0) {}
    template <typename U>
    MyScopedAllocator(const MyScopedAllocator<U>& other) : buffer_(other.buffer_), size_(other.size_), used_(other.used_) {}

    T* allocate(std::size_t n) {
        if (used_ + n > size_) {
            throw std::bad_alloc();
        }
        T* p = reinterpret_cast<T*>(buffer_ + used_);
        used_ += n;
        return p;
    }

    void deallocate(T* p, std::size_t n) {}
private:
    char* buffer_;
    std::size_t size_;
    std::size_t used_;
};

int main() {
    // 使用状态化分配器
    MyAllocator<int> allocator1(1);
    std::vector<int, MyAllocator<int>> vec1(allocator1);
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);
    
    MyAllocator<int> allocator2(2);
    std::vector<int, MyAllocator<int>> vec2(allocator2);
    vec2.push_back(4);
    vec2.push_back(5);
    vec2.push_back(6);

    // 使用作用域分配器
    {
        MyScopedAllocator<int> allocator;
        std::vector<int, MyScopedAllocator<int>> vec(allocator);
        vec.push_back(1);
        vec.push_back(2);
        vec.push_back(3);
    }
    return 0;
}

```

#### std::forward_list
```c++
#include <iostream>
#include <forward_list>
int main() {
    std::forward_list<int> myList;
    myList.push_front(1);
    myList.push_front(2);
    myList.push_front(3);
    for (const auto& element : myList) {
        std::cout << element << " ";
    }
    return 0;
}

```

#### chrono library

C++11中的`<chrono>`库提供了一组用于处理时间间隔和时间点的类和函数。它是标准库的一部分，旨在成为旧版`<ctime>`库的现代化和灵活的替代品。

以下是C++11中`<chrono>`库的一些关键特性：
- 时间间隔：该库提供了一个std::chrono::duration类模板，用于表示时间间隔。时间间隔可以以不同的单位（例如秒、毫秒、微秒）指定，并可用于测量时间的持续。
- 时间点：库中的std::chrono::time_point类模板表示特定的时间点。它可以与时间间隔一起使用，用于计算时间的差异或执行时间的加减运算。
- 时钟：库中定义了几种不同的时钟类型，例如std::chrono::system_clock、std::chrono::steady_clock和std::chrono::high_resolution_clock。这些时钟提供了不同的精度和用途，可以用于获取当前时间、计算时间间隔等操作。
- 时间转换：库中提供了函数和方法，用于在不同的时间单位之间进行转换，例如将秒转换为毫秒或微秒，或将时间点转换为字符串表示形式。
- 定时器：库中还提供了定时器功能，可以使用std::chrono::duration和std::chrono::steady_clock来实现定时执行任务的功能。

#### ratio library
```c++
#include <ratio>

// 定义一个比率，其分母为 2 ，分子为 3
std::ratio<2, 3> r;

// 计算两个比率的乘积
std::ratio<2, 3> s = r * r;

// 比较两个比率
if (r < s) {
  // r 小于 s
}
```

#### new algorithms:
    * std::all_of
    * std::any_of
    * std::none_of
    * std::find_if_not
    * std::copy_if
    * std::copy_n
    * std::move
    * std::move_backward
    * std::random_shuffle
    * std::shuffle
    * std::is_partitioned
    * std::partition_copy 
    * std::partition_point
    * std::is_sorted
    * std::is_sorted_until
    * std::is_heap
    * std::is_heap_until
    * std::minmax
    * std::minmax_element

```c++
#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  // 定义一个向量
  std::vector<int> v = {1, 2, 3, 4, 5};

  // 使用 std::all_of 检查所有元素是否满足某个条件
  bool all_even = std::all_of(v.begin(), v.end(), [](int i) { return i % 2 == 0; });

  // 使用 std::any_of 检查是否至少有一个元素满足某个条件
  bool any_odd = std::any_of(v.begin(), v.end(), [](int i) { return i % 2 != 0; });

  // 使用 std::none_of 检查是否没有元素满足某个条件
  bool none_negative = std::none_of(v.begin(), v.end(), [](int i) { return i < 0; });

  // 使用 std::find_if_not 找到第一个不满足某个条件的元素
  auto not_even = std::find_if_not(v.begin(), v.end(), [](int i) { return i % 2 == 0; });

  // 使用 std::copy_if 复制满足某个条件的元素到另一个容器
  std::vector<int> v2;
  std::copy_if(v.begin(), v.end(), std::back_inserter(v2), [](int i) { return i % 2 == 0; });

  // 使用 std::copy_n 复制指定数量的元素到另一个容器
  std::vector<int> v3(3);
  std::copy_n(v.begin(), 3, v3.begin());

  // 使用 std::move 将元素移动到另一个容器
  std::vector<int> v4;
  std::move(v.begin(), v.end(), std::back_inserter(v4));

  // 使用 std::move_backward 将元素在向量中反向移动
  std::move_backward(v.begin(), v.end(), v.end());

  // 使用 std::random_shuffle 随机打乱向量中的元素
  std::random_shuffle(v.begin(), v.end());

  // 使用 std::shuffle 使用用户提供的函数随机打乱向量中的元素
  std::shuffle(v.begin(), v.end(), [](int i) { return rand() % 5; });

  // 使用 std::is_partitioned 检查向量是否已分区
  bool is_partitioned = std::is_partitioned(v.begin(), v.end(), [](int i) { return i < 3; });

  // 使用 std::partition_copy 将向量分区并复制到另一个向量
  std::vector<int> v2;
  std::partition_copy(v.begin(), v.end(), v2.begin(), [](int i) { return i < 3; });

  // 使用 std::partition_point 找到向量中的分区点
  auto partition_point = std::partition_point(v.begin(), v.end(), [](int i) { return i < 3; });

  // 使用 std::is_sorted 检查向量是否已排序
  bool is_sorted = std::is_sorted(v.begin(), v.end());

  // 使用 std::is_sorted_until 找到向量中第一个未排序的元素
  auto is_sorted_until = std::is_sorted_until(v.begin(), v.end());

  // 使用 std::is_heap 检查向量是否为堆
  bool is_heap = std::is_heap(v.begin(), v.end());

  // 使用 std::is_heap_until 找到向量中第一个不为堆的元素
  auto is_heap_until = std::is_heap_until(v.begin(), v.end());

  // 使用 std::minmax 获取向量的最小和最大元素
  auto minmax = std::minmax(v.begin(), v.end());

  // 使用 std::minmax_element 获取向量的最小和最大元素的迭代器
  auto minmax_element = std::minmax_element(v.begin(), v.end());
```

#### std::is_permutation
C++标准库中的 `st::is_permutation` 函数用于确定一个序列是否是另一个序列的排列。排列是元素序列，其中元素是唯一的，但元素的顺序可以不同。

```c++
#include <algorithm>
#include <iostream>

int main() {
  int a[] = {1, 2, 3};
  int b[] = {3, 1, 2};

  bool is_permutation = std::is_permutation(a, a + 3, b);

  std::cout << is_permutation << std::endl;

  return 0;
}
```

#### std::iota,
```c++
int arr[10];

// generate a sequence of consecutive integers
std::iota(arr, arr + 10, 1);
```

#### std::uninitialized_copy_n
用于将一个序列的元素复制到另一个序列中。
std::uninitialized_copy_n 函数不会为 destination 分配内存。它会假设 destination 已经分配了足够的空间，如果 destination 没有足够的空间，则函数会抛出一个异常。

```c++
#include <algorithm>
#include <iostream>

int main() {
  int source[] = {1, 2, 3, 4, 5};
  int destination[5];

  std::uninitialized_copy_n(source, 5, destination);

  for (int i = 0; i < 5; i++) {
    std::cout << destination[i] << std::endl;
  }

  return 0;
}

```


#### std::function

std::function 是一个模板类，它可以存储和调用任何可调用对象，包括函数指针、函数对象和 lambda 表达式。std::function 类提供了一种安全、通用的方法来存储和调用可调用对象，而不必担心可调用对象的具体类型。
```c++
#include <functional>

int main() {
  // 定义一个函数指针
  int (*func)(int) = [](int x) { return x * x; };

  // 定义一个函数对象
  struct MyFunc {
    int operator()(int x) { return x * x; }
  };

  // 定义一个 lambda 表达式
  auto lambda = [](int x) { return x * x; };

  // 创建一个 std::function 对象，并将函数指针、函数对象和 lambda 表达式存储其中
  std::function<int(int)> f1(func);
  std::function<int(int)> f2(MyFunc());
  std::function<int(int)> f3(lambda);

  // 调用 std::function 对象
  std::cout << f1(5) << std::endl; // 25
  std::cout << f2(5) << std::endl; // 25
  std::cout << f3(5) << std::endl; // 25

  return 0;
}
```


#### std::exception_ptr
```c++
include <exception>
#include <iostream>

int main() {
  try {
    // 抛出一个异常
    throw std::runtime_error("This is an exception");
  } catch (std::exception_ptr e) {
    // 捕获异常
    std::cout << "捕获到异常" << std::endl;

    // 重抛异常
    std::rethrow_exception(e);
  }

  return 0;
}
```

#### std::error_code and std::error_condition
```c++
#include <iostream>
#include <system_error>

int main() {
  // 创建一个 std::error_code 对象
  std::error_code ec(1, std::system_category());

  // 获取错误的描述
  std::string description = ec.message();

  // 获取错误的类别
  std::error_category const *category = ec.category();

  // 比较错误
  if (ec == std::errc::invalid_argument) {
    // 错误是无效参数错误
  }

  // 打印错误
  std::cout << description << std::endl;

  return 0;
}
```

#### iterator improvements:
    * std::begin
    * std::end
    * std::next
    * std::prev

#### Unicode conversion facets

#### Unicode conversion functions
