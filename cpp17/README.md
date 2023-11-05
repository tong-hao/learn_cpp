## c++17 特性
> 参考：https://en.cppreference.com/w/cpp/17

---
## 需要记住
- 对if和switch语句添加了初始化器
- namespace嵌套
---


## Obsolete
### Removed:
- std::auto_ptr,
- deprecated function objects,
- std::random_shuffle,
- std::unexpected,
- the obsolete iostreams aliases,
- trigraphs,
- the register keyword,
- bool increment,
- dynamic exception specification

### Deprecated:
- std::iterator,
- std::raw_storage_iterator,
- std::get_temporary_buffer,
- std::is_literal_type,
- std::result_of,
- all of <codecvt>


## New language features
### u8 character literal
C++17 引入了 u8 字符字面量（u8 character literal）的特性，用于表示 UTF-8 编码的字符。
```c++
const char* str = u8"你好，世界！";  // 使用 u8 字符字面量表示包含中文字符的字符串

```

### made noexcept part of type system
```c++
void f() noexcept; // the function f() does not throw
void (*fp)() noexcept(false); // fp points to a function that may throw
void g(void pfa() noexcept);  // g takes a pointer to function that doesn't throw
// typedef int (*pf)() noexcept; // error
```

### new order of evaluation rules
C++17 引入了一些新的求值顺序规则:
1. C++17 引入了一些新的顺序点: 函数调用、函数参数求值、逗号运算符、逻辑与运算符（&&）和逻辑或运算符（||）等。
2. 函数参数求值顺序：C++17 规定函数参数的求值顺序是未指定的，即编译器可以按照任意顺序对函数参数进行求值。
3. C++17 规定逗号运算符的求值顺序是从左到右的
4. C++17 规定逻辑与运算符和逻辑或运算符的求值顺序是从左到右的，并且具有短路求值的特性

### lambda capture of *this、
在C++17中，lambda函数的捕获列表支持捕获*this指针。
```c++
class MyClass {
public:
    void memberFunction() {
        int x = 10;

        // Lambda函数通过引用捕获*this指针
        auto lambda_ref = [&]() {
            std::cout << "Accessing member variable x through reference capture: " << x << std::endl;
            // 修改成员变量x
            x = 20;
        };

        // Lambda函数通过值捕获*this指针
        auto lambda_val = [=]() {
            std::cout << "Accessing member variable x through value capture: " << x << std::endl;
            // x不可修改，因为*this以值捕获，是const指针
            // this->x = 30;  // 这会导致编译错误
        };

        lambda_ref();
        lambda_val();
        std::cout << "After lambda_ref(), x = " << x << std::endl; // 输出为20
    }

private:
    int x;
};
```


### constexpr
#### compile-time if constexpr
在编译时 if constexpr 中，condition 必须是一个编译时可求值的常量表达式。
```c++
template <typename T>
void process(T value)
{
    if constexpr (std::is_integral<T>::value)
    {
        // 处理整数类型的值
        // ...
    }
    else if constexpr (std::is_floating_point<T>::value)
    {
        // 处理浮点数类型的值
        // ...
    }
    else
    {
        // 处理其他类型的值
        // ...
    }
}

```

#### constexpr lambda
C++17 引入了 constexpr lambda（常量表达式 lambda）这个特性，它允许我们在编译时求值的上下文中使用 lambda 表达式。
```c++
constexpr auto lambda = [] (parameters) constexpr -> return_type
{
    // lambda body
};

```

### Variables
#### inline variables
C++17引入了内联变量（Inline Variables）的特性。
在C++17之前，如果我们在头文件中定义了一个全局变量，当多个编译单元（cpp文件）包含该头文件时，会出现多次定义的链接错误。为了解决这个问题，我们通常需要在头文件中声明变量为extern，然后在某个cpp文件中定义它。
```c++
// example.h
#pragma once

inline int globalVar = 42;
```
在多个cpp文件中包含 "example.h"，编译器会确保只有一个 globalVar 的实例存在。

#### structured bindings
C++17 引入了结构化绑定（Structured Bindings）这个特性，它允许我们将一个复杂的数据结构解构为多个独立的变量。结构化绑定可以用于解构数组、元组、结构体等数据类型
```c++
auto [var1, var2, ...] = expression;
```


#### initializers for if and switch
在C++17中，对if和switch语句添加了初始化器（Initializer）的特性
```c++
if (bool b = someCondition(); b){}

switch (int value = 2; value) {}
```

#### guaranteed copy elision
C++17引入了“拷贝省略”（Guaranteed Copy Elision）的特性，这是一种编译器优化，用于避免不必要的拷贝构造和移动构造函数的调用。

编译器在以下情况下必须执行拷贝省略：
- 从函数返回一个临时对象时，可以避免生成临时对象，直接在函数的调用方创建该对象。
- 在初始化过程中，可以直接在目标对象的位置创建对象，而无需使用中间临时对象。
- 在将一个对象作为参数传递给函数时，可以直接在函数的调用方创建该对象，而无需生成临时对象。
```c++

```

#### temporary materialization
用于避免创建临时对象并直接在目标位置生成结果
```c++
// 函数接受int类型参数
void printNumber(int number) {
    std::cout << "Number: " << number << std::endl;
}

// 编译器直接在函数参数位置创建临时对象，而无需生成中间临时对象
printNumber(42 + 10);

```


### Templates
#### fold-expressions ( ... )
C++17中引入了fold表达式（fold-expressions）作为模板元编程（template metaprogramming）的一个重要增强特性。
```c++
#include <iostream>

template<typename... Args>
auto sum(Args... args) {
    return (args + ...);
}

int main() {
    int result = sum(1, 2, 3, 4, 5);
    std::cout << "Sum: " << result << std::endl; // Output: Sum: 15
    return 0;
}

///
// Output: 1 2 3 4 5 
// Sum: 15
template<typename... Args>
auto print_and_sum(Args... args) {
    return ((std::cout << args << ' '), ... , (std::cout << '\n'), (args + ...));
}


```

### class template argument deduction tuple t(4, 3, 2.5)
在C++17中，引入了类模板参数推导（class template argument deduction）
```c++
// 在C++17之前，要使用std::tuple，需要显式地指定类型，例如：
std::tuple<int, int, double> t(4, 3, 2.5);

// 在C++17中
auto t = std::make_tuple(4, 3, 2.5);
```

### non-type template parameters declared with auto
in C++17, you can have non-type template parameters like this:
```c++
template <int N>
class MyClass {
public:
    int value = N;
};

int main() {
    MyClass<42> obj;
    std::cout << obj.value << std::endl; // Output: 42
    return 0;
}

```

### Namespaces
simplified nested namespaces
```c++
// 之前
namespace a {
    namespace b{
    }
}

// c++17
namespace a::b{}

```

using-declaration declaring multiple names
```c++
// 支持多个
using std::cout, std::endl;
```

attribute namespaces don't have to repeat
```c++
[[gnu::deprecated]] namespace attributes {}
void foo() {
}
namespace ns1 {
// 在 C++17 中，可以使用新的语法，只需在一个命名空间中声明属性命名空间，然后在其他命名空间中直接使用该属性命名空间。
    using namespace attributes;
    void bar() {
    }
}


```

### new attributes:
`[[fallthrough]]`
在 C++17 中，引入了 [[fallthrough]] 属性，用于在 switch 语句中显式地标记出意图穿透（fallthrough）到下一个 case 的行为。
```c++
switch (value) {
    case 1:
        std::cout << "Value is 1." << std::endl;
        [[fallthrough]];
    case 2:
        std::cout << "Value is 2." << std::endl;
        break;
    case 3:
        std::cout << "Value is 3." << std::endl;
        [[fallthrough]];
    default:
        std::cout << "Default case." << std::endl;
        break;
}

```

`[[maybe_unused]]`
在 C++17 中，引入了 [[maybe_unused]] 属性，用于标记变量或函数可能未被使用的情况，以抑制编译器产生的未使用变量或函数的警告。
```c++
[[maybe_unused]] int unusedVariable;
[[maybe_unused]] void unusedFunction() {
    // do something
}
```

`[[nodiscard]]`
当我们在C++17中使用[[nodiscard]]属性时，它用于指示函数的返回值不应该被忽略。
```c++
[[nodiscard]] int addNumbers(int a, int b) {
    return a + b;
}

int main() {
    addNumbers(3, 5); // 如果返回值没有被使用，编译器可能会发出警告。
    return 0;
}

```

### __has_include
__has_include 是C++17标准引入的预处理器宏（preprocessor macro）。它用于在编译时检查是否存在某个头文件，这样在编写跨平台的代码时可以进行条件编译。
```c++
#if __has_include(<header>)
    // Code to be included if the header is found
#else
    // Code to be included if the header is not found
#endif

```


## New headers
- <any>
- <charconv>
- <execution>
- <filesystem>
- <memory_resource>
- <optional>
- <string_view>
- <variant>

## Utility types
### std::tuple:
std::apply
```c++
// std::apply 是C++17新增的标准函数，它允许我们将一个可调用对象（函数、函数指针、成员函数指针或者函数对象）和一个 std::tuple 中的元素进行绑定

int add(int a, int b) {
    return a + b;
}
std::tuple<int, int> values = std::make_tuple(3, 5);
int result = std::apply(add, values);
```

std::make_from_tuple
允许我们使用元组中的元素来构造一个对象，而无需手动拆解元组。
```
std::tuple<std::string, int> values = std::make_tuple("John", 30);
Person person = std::make_from_tuple<Person>(values);
```

deduction guides
C++17还引入了 deduction guides（推导指南），这是一种帮助编译器在特定情况下自动推导模板参数的机制。
```c++
// 对于 std::tuple，推导指南允许我们在创建元组时省略模板参数。
auto values = std::make_tuple("Alice", 25);
```

### std::any
在C++17中，std::any 是一个新的标准库类，它允许存储任意类型的值，并提供了一种类型安全的方式来操作这些值。
```c++
#include <any>
std::any val1 = 42;
std::any val2 = "Hello, C++17!";
std::any val3 = std::string("std::any");

int i = std::any_cast<int>(val1);
const char* str = std::any_cast<const char*>(val2);
std::string str2 = std::any_cast<std::string>(val3);

```

### std::optional
在C++17中，std::optional 是一个新的标准库类，用于表示一个可能包含值的可选对象。它提供了一种类型安全的方式来处理可能缺失的值，避免了使用特殊值（如-1、NULL或nullptr）来表示缺失的情况。
```c++
#include <optional>

// 定义
std::optional<int> divide(int a, int b) {
    if (b != 0) {
        return a / b;
    } else {
        return std::nullopt; // 表示没有值
    }
}

// 调用
std::optional<int> result = divide(10, 2);
if (result) {
    std::cout << "Result: " << *result << std::endl;
} else {
    std::cout << "Division by zero." << std::endl;
}
```

### std::variant
用于表示可以包含多种不同类型值的联合体。类似于C语言中的联合体（union），但 std::variant 提供了更多的类型安全性和功能。
```c++
#include <variant>

std::variant<int, double, std::string> var;
var = 42; // 包含一个int类型的值
std::cout << "Type: int, Value: " << std::get<int>(var) << std::endl;

```

### searchers
用于搜索子序列的新的标准库组件。它提供了一种高效的方式来在序列（例如字符串、数组等）中查找子序列的位置。

std::searchers 定义了以下几种搜索器：
1）std::default_searcher: 默认搜索器，使用 std::boyer_moore_searcher 或 std::boyer_moore_horspool_searcher 作为底层搜索算法。这个搜索器适用于大多数情况，并且通常是最快的。
2）std::boyer_moore_searcher: 使用Boyer-Moore算法实现的搜索器。Boyer-Moore算法是一种高效的字符串搜索算法，特别适用于长模式的情况。
3）std::boyer_moore_horspool_searcher: 使用Boyer-Moore-Horspool算法实现的搜索器。这是Boyer-Moore算法的一种简化版本，在某些情况下可能比std::boyer_moore_searcher更快。
4）std::boyer_moore_searcher_utf8: 针对UTF-8编码的字符串的Boyer-Moore搜索器。对于使用UTF-8编码的字符串，这个搜索器提供了更高效的搜索。

```c++
#include <iostream>
#include <string>
#include <algorithm>
#include <searchers>

int main() {
    std::string text = "This is a sample text for searching.";
    std::string pattern = "sample";

    auto searcher = std::default_searcher(pattern.begin(), pattern.end());
    auto result = std::search(text.begin(), text.end(), searcher);

    if (result != text.end()) {
        std::cout << "Pattern found at position: " << std::distance(text.begin(), result) << std::endl;
    } else {
        std::cout << "Pattern not found." << std::endl;
    }

    return 0;
}

```

### std::as_const
std::as_const 是一个新的标准库函数，用于将对象转换为其对应的常量引用。
```c++
#include <iostream>
#include <utility>

void printValue(const int& value) {
    std::cout << "Value: " << value << std::endl;
}

int main() {
    int x = 42;

    printValue(x); // 调用函数并输出：Value: 42

    std::as_const(x) = 100; // 使用 std::as_const 将 x 转换为常量引用
    printValue(x); // 再次调用函数并输出：Value: 42（x的值未被修改）

    return 0;
}

```

### std::not_fn
std::not_fn 函数模板，用于创建一个函数对象，该函数对象的行为与给定的谓词相反。
```c++
#include <iostream>
#include <functional>
bool isEven(int num) {
    return num % 2 == 0;
}
int main() {
    std::function<bool(int)> isOdd = std::not_fn(isEven);
    std::cout << isOdd(3) << std::endl;  // 输出 1，表示 3 是奇数
    std::cout << isOdd(4) << std::endl;  // 输出 0，表示 4 不是奇数
    return 0;
}


```

## Memory management
### uninitialized memory algorithms
std::destroy_at
std::destroy_at 是C++17中引入的一个标准库函数，用于显式地调用对象的析构函数。
需要注意的是，std::destroy_at 会调用对象的析构函数，但不会释放内存。如果需要同时释放内存，必须在调用 std::destroy_at 之后使用 delete 或其他释放内存的方法。
```c++
#include <memory>

int main() {
    int* ptr = new int(42);
    std::destroy_at(ptr); // 调用指针指向对象的析构函数
    delete ptr; // 删除指针指向的对象
    return 0;
}

```

std::destroy
```c++
#include <iostream>
#include <memory>
#include <algorithm>
struct MyClass {
    int value;
    ~MyClass() {
        std::cout << "Destructor called for MyClass with value: " << value << std::endl;
    }
};
int main() {
    MyClass* arr = new MyClass[3]{{1}, {2}, {3}};
    std::destroy(arr, arr + 3); //这会对数组中的每个对象调用 MyClass 的析构函数
    delete[] arr;
    return 0;
}

```

std::destroy_n
```c++
#include <iostream>
#include <memory>

int main() {
    // Allocate memory for three objects of int type
    int* buffer = static_cast<int*>(std::malloc(sizeof(int) * 3));

    // Construct three int objects in the memory
    for (size_t i = 0; i < 3; ++i) {
        new (buffer + i) int(i + 1);
    }

    // Destruct the objects before freeing the memory
    std::destroy_n(buffer, 3);

    // Free the memory
    std::free(buffer);

    return 0;
}

```

std::uninitialized_move
```c++

```

std::uninitialized_value_construct
std::uninitialized_value_construct 是一个标准库函数，用于在未初始化的内存区域上执行值初始化
```c++
#include <iostream>
#include <memory>

struct MyClass {
    int value;
    MyClass() : value(42) {} // 默认构造函数
};

int main() {
    const size_t numElements = 5;
    MyClass* buffer = static_cast<MyClass*>(std::malloc(sizeof(MyClass) * numElements));

    // 初始化内存中的对象
    std::uninitialized_value_construct(buffer, buffer + numElements);

    // 输出初始化后的对象的值
    for (size_t i = 0; i < numElements; ++i) {
        std::cout << "Value at index " << i << ": " << buffer[i].value << std::endl;
    }

    // 析构对象并释放内存
    for (size_t i = 0; i < numElements; ++i) {
        buffer[i].~MyClass();
    }
    std::free(buffer);

    return 0;
}

```

### weak_from_this
std::weak_from_this 是一个用于解决循环引用问题的特性。
```c++
#include <memory>

class MyClass : public std::enable_shared_from_this<MyClass> {
public:
    std::weak_ptr<MyClass> getWeak() {
        return weak_from_this();
    }
};

int main() {
    std::shared_ptr<MyClass> obj = std::make_shared<MyClass>();
    std::weak_ptr<MyClass> weakObj = obj->getWeak();

    if (auto sharedObj = weakObj.lock()) {
        // 使用 sharedObj 指向的对象
    } else {
        // 对象已经被释放
    }

    return 0;
}

```

### std::pmr::memory_resource and std::polymorphic_allocator 【有疑问】
std::pmr::memory_resource 是一个抽象基类，用于为 C++ 内存分配器提供接口。它使得我们可以自定义内存管理器，然后将其用于标准容器和其他使用内存分配器的操作。

std::polymorphic_allocator 是一个包装器类模板，它在标准容器上提供对 std::pmr::memory_resource 的透明访问。通过使用 std::polymorphic_allocator，标准容器可以在其内部使用自定义的 std::pmr::memory_resource 实现内存分配和释放，从而实现内存的灵活管理。
```c++
#include <iostream>
#include <vector>
#include <memory_resource>

int main() {
    // 使用自定义的内存资源
    std::pmr::monotonic_buffer_resource pool;
    std::pmr::vector<int> vec(&pool);

    for (int i = 1; i <= 5; ++i) {
        vec.push_back(i);
    }

    for (const auto& value : vec) {
        std::cout << value << " ";
    }

    return 0;
}

```

### std::aligned_alloc
we use std::aligned_alloc to allocate 64 bytes of memory with an alignment of 32 bytes. It ensures that the returned memory block is aligned to a 32-byte boundary. 
```c++
#include <iostream>
#include <cstdlib>

int main() {
    size_t alignment = 32;
    size_t size = 64;

    void* ptr = std::aligned_alloc(alignment, size);

    if (ptr) {
        std::cout << "Memory allocation successful." << std::endl;
        // Use the allocated memory here.
    } else {
        std::cout << "Memory allocation failed." << std::endl;
    }

    // Don't forget to free the memory after use.
    std::free(ptr);

    return 0;
}

```

### transparent std::owner_less
它是一个用于透明地比较智能指针的比较函数对象。
std::owner_less，我们可以直接进行比较，它能够理解并透明地处理不同智能指针的所有权关系。
```c++
#include <iostream>
#include <memory>
#include <set>

int main() {
    std::shared_ptr<int> sp1 = std::make_shared<int>(42);
    std::shared_ptr<int> sp2 = std::make_shared<int>(42);

    std::set<std::shared_ptr<int>, std::owner_less<std::shared_ptr<int>>> mySet;
    mySet.insert(sp1);
    mySet.insert(sp2);

    // 注意：由于std::set是有序容器，会判断两个shared_ptr是否相等
    // 所以即使sp1和sp2指向的对象相同，但它们在set中仍然会被认为是不同的元素
    std::cout << "Size of set: " << mySet.size() << std::endl; // 输出：2

    return 0;
}

```

### array support for std::shared_ptr
C++17引入了对std::shared_ptr的数组支持。在C++17之前，std::shared_ptr只能用于管理单个对象的动态内存，无法直接管理动态数组的内存。
```c++
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int[]> arr = std::make_shared<int[]>(5);

    for (int i = 0; i < 5; ++i) {
        arr[i] = i + 1;
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << arr[i] << " ";
    }

    return 0;
}

```

### allocation functions with explicit alignment
在C++17中，引入了一项新特性，即为内存分配函数提供显式对齐（explicit alignment）的支持。这个特性允许我们在使用operator new和operator new[]进行内存分配时，指定所需的对齐方式。
```c++
// 这个函数用于分配指定大小和对齐方式的内存块。
void* operator new(std::size_t size, std::align_val_t alignment);

// 这个函数用于分配指定大小和对齐方式的数组内存块。
void* operator new[](std::size_t size, std::align_val_t alignment);


```


## Compile-time programming
### std::byte
std::byte 类型，它是一个无符号整数类型，用于表示字节（8位数据）的数据
```c++
#include <iostream>
#include <cstddef> // For std::byte

int main() {
    std::byte b = std::byte{0x2A}; // 使用十六进制字面值初始化 std::byte 对象
    std::cout << "Value of b: " << std::to_integer<int>(b) << std::endl;

    // 使用位运算对字节数据进行操作
    std::byte mask = std::byte{0xF0};
    std::byte result = b & mask;
    std::cout << "Result: " << std::to_integer<int>(result) << std::endl;

    return 0;
}

```
### std::conjunction/std::disjunction/std::negation
std::conjunction 是一个类型特性模板，用于实现逻辑与运算。
std::disjunction 是一个类型特性模板，用于实现逻辑或运算。
std::negation 是一个类型特性模板，用于实现逻辑非运算。

```c++
#include <iostream>
#include <type_traits>

template <typename T>
struct IsIntegral : std::is_integral<T> {};

template <typename T>
struct IsPointer : std::is_pointer<T> {};

// 检查所有类型是否为整数类型
std::cout << std::conjunction<IsIntegral<int>, IsIntegral<char>>::value << std::endl; // 输出：true



```
### type trait variable templates (xxx_+v)
在C++17中，引入了一组 type trait 的变量模板（Variable Templates），它们是在类型特性（type traits）基础上的进一步增强，提供了更便捷和直观的方式来获取类型特性的信息。这些变量模板以 _v 结尾，可以直接通过类型名称来获取对应的值，而不需要通过 .value 成员。

以下是一些常用的 type trait 变量模板：
```c++
#include <type_traits>

std::cout << std::is_same_v<int, int> << std::endl; // 输出：true
std::cout << std::is_integral_v<int> << std::endl; // 输出：true
std::cout << std::is_pointer_v<int*> << std::endl; // 输出：true
std::cout << std::is_array_v<int[]> << std::endl; // 输出：true
std::cout << std::is_enum_v<MyEnum> << std::endl; // 输出：true
std::cout << std::is_reference_v<int&> << std::endl; // 输出：true

```
### std::is_swappable
用于检查给定类型是否可交换（swappable）
```c++
#include <iostream>
#include <type_traits>
struct MyType {
    // 自定义的交换函数
    friend void swap(MyType& lhs, MyType& rhs) {
        std::cout << "Custom swap function" << std::endl;
        // 交换操作的具体实现
    }
};
int main() {
    std::cout << std::boolalpha;
    std::cout << "Is int swappable? " << std::is_swappable<int>::value << std::endl;
    std::cout << "Is MyType swappable? " << std::is_swappable<MyType>::value << std::endl;
    return 0;
}

```
### is_invocable
用于检查是否可以调用一个函数或者函数对象（callable），以及调用时的参数是否合法。
```c++
#include <iostream>
#include <type_traits>

void foo(int a, double b) {
    std::cout << "foo(" << a << ", " << b << ")" << std::endl;
}

struct Bar {
    void operator()(int a, double b) const {
        std::cout << "Bar::operator()(" << a << ", " << b << ")" << std::endl;
    }
};

int main() {
    std::cout << std::boolalpha;

    // 检查函数是否可调用
    std::cout << std::is_invocable<decltype(foo), int, double>::value << std::endl; // 输出：true

    // 检查函数对象是否可调用
    std::cout << std::is_invocable<Bar, int, double>::value << std::endl; // 输出：true

    // 检查参数类型不匹配的情况
    std::cout << std::is_invocable<Bar, int, int>::value << std::endl; // 输出：false

    return 0;
}

```
### is_aggregate
```c++

```
### std::has_unique_object_representations
引入了 std::has_unique_object_representations 类型特性，它用于检查一个类型是否具有唯一的对象表示（Unique Object Representations）。

唯一的对象表示意味着类型的所有对象都有相同的二进制表示形式，没有任何额外的位模式或填充字节。这意味着这些对象可以在内存中被完全按照其二进制位进行拷贝和复制。
```c++
#include <iostream>
#include <type_traits>

struct Point {
    int x;
    int y;
};

int main() {
    std::cout << std::boolalpha;

    std::cout << std::has_unique_object_representations<Point>::value << std::endl; // 输出：true
    std::cout << std::has_unique_object_representations<int>::value << std::endl; // 输出：true

    // 类型包含虚函数，因此不具有唯一的对象表示
    struct Base {
        virtual ~Base() {}
    };
    std::cout << std::has_unique_object_representations<Base>::value << std::endl; // 输出：false

    return 0;
}

```

## Algorithms
### std::clamp
 std::clamp 算法，它用于将一个值限制在指定的范围内。
 std::clamp 接受三个参数：
要限制的值。
最小边界值。
最大边界值。

```c++
#include <iostream>
#include <algorithm>

int main() {
    int value = 15;
    int minValue = 5;
    int maxValue = 10;

    // 将 value 限制在 minValue 和 maxValue 之间
    int result = std::clamp(value, minValue, maxValue);

    std::cout << "Original value: " << value << std::endl;
    std::cout << "Clamped value: " << result << std::endl;

    return 0;
}
```

### parallel algorithms and execution policies
C++17引入了并行算法（Parallel Algorithms）和执行策略（Execution Policies），以提高STL标准库算法的性能和并行处理能力。

C++17引入了三种执行策略：
- std::execution::sequenced_policy：该策略表示算法以串行方式执行，不进行并行处理。
- std::execution::parallel_policy：该策略表示算法将在多个线程上并行执行。标准库会自动决定使用多少线程，具体取决于硬件支持和算法的复杂性。
- std::execution::parallel_unsequenced_policy：该策略表示算法可以以并行和无序的方式执行。这意味着算法可以在多个线程上同时执行，而且不保证执行的顺序。
```c++
#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>

int main() {
    std::vector<int> data = {5, 2, 8, 3, 1, 7, 6, 4};

    // 使用并行算法对数据进行排序
    std::sort(std::execution::par, data.begin(), data.end());

    std::cout << "Sorted data: ";
    for (int num : data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

```
### std::reduce
用于在给定范围内对元素进行归约操作。
归约操作是指对一组值进行累积、组合或聚合。

std::reduce 接受四个参数：
1） 要进行归约的元素的起始迭代器。
2） 要进行归约的元素的结束迭代器。
3） 初始值（可选参数）：归约操作的初始值，默认为 T()，即 T 类型的默认构造函数产生的值。
4） 二元操作函数（可选参数）：用于对两个元素进行归约操作的函数，默认为 std::plus<T>()，即加法运算。

```c++
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 使用 std::reduce 对 numbers 中的元素进行累加
    int sum = std::reduce(numbers.begin(), numbers.end());

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}

```
### std::inclusive_scan
C++17 introduced the std::inclusive_scan algorithm in the <numeric> header. This algorithm performs an inclusive prefix sum operation on a range of elements.
```c++
#include <iostream>
#include <numeric>
#include <vector>
int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());
    std::inclusive_scan(numbers.begin(), numbers.end(), result.begin());
    for (const auto& num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}

```
### std::exclusive_scan
std::exclusive_scan 接受五个参数：
- 要进行独占性扫描的元素的起始迭代器。
- 要进行独占性扫描的元素的结束迭代器。
- 输出结果的目标迭代器。
- 初始值：独占性扫描操作的初始值。
- 二元操作函数（可选参数）：用于对两个元素进行独占性扫描操作的函数，默认为 std::plus<T>()，即加法运算。


```c++
#include <iostream>
#include <vector>
#include <numeric>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::vector<int> result(numbers.size());

    // 使用 std::exclusive_scan 对 numbers 中的元素进行独占性扫描，初始值为0
    std::exclusive_scan(numbers.begin(), numbers.end(), result.begin(), 0);

    std::cout << "Exclusive scan result: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

```
### std::gcd
用于计算两个整数的最大公约数（Greatest Common Divisor，简称为 GCD）
```c++
#include <iostream>
#include <numeric>

int main() {
    int a = 12;
    int b = 18;

    int result = std::gcd(a, b);

    std::cout << "GCD of " << a << " and " << b << " is: " << result << std::endl;

    return 0;
}

```
### std::lcm
用于计算两个整数的最小公倍数（Least Common Multiple，简称为 LCM）
```c++
#include <iostream>
#include <numeric>

int main() {
    int a = 6;
    int b = 8;

    int result = std::lcm(a, b);

    std::cout << "LCM of " << a << " and " << b << " is: " << result << std::endl;

    return 0;
}

```


## Iterators and containers
### map/set extract and map/set merge
extract 用于在关联容器 std::map 和 std::set 中执行元素的提取和合并操作。
merge 用于将一个关联容器中的元素合并到另一个关联容器中。

```c++
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}, {3, "three"}};

    // 提取键为 2 的元素
    auto extractedElement = myMap.extract(2);

    if (extractedElement.empty()) {
        std::cout << "Element not found in the map." << std::endl;
    } else {
        std::cout << "Extracted element: " << extractedElement.key() << " => " << extractedElement.mapped() << std::endl;
    }

//===

    std::map<int, std::string> sourceMap = {{1, "one"}, {2, "two"}};
    std::map<int, std::string> targetMap = {{3, "three"}, {4, "four"}};

    // 将 sourceMap 中的元素合并到 targetMap 中
    targetMap.merge(sourceMap);


    return 0;
}


```
### map/unordered_map try_emplace and insert_or_assign
try_emplace 用于在关联容器 std::map 和 std::unordered_map 中插入元素

insert_or_assign 用于插入或修改容器中的元素。如果容器中已经存在具有相同键的元素，则 insert_or_assign 会用新值覆盖旧值，即修改元素的值。

```c++
#include <iostream>
#include <map>

int main() {
    std::map<int, std::string> myMap = {{1, "one"}, {2, "two"}};

    // 尝试插入新元素，键为 3，值为 "three"，但因为键已经存在，插入操作失败
    auto result = myMap.try_emplace(3, "three");

    if (result.second) {
        std::cout << "Element inserted successfully." << std::endl;
    } else {
        std::cout << "Element insertion failed. Key already exists." << std::endl;
    }

    // 插入或修改元素，键为 2，新值为 "new two"，容器中已存在具有相同键的元素，因此会修改其值
    myMap.insert_or_assign(2, "new two");
    // 插入或修改元素，键为 3，值为 "three"，容器中不存在具有相同键的元素，因此会插入新元素
    myMap.insert_or_assign(3, "three");

    return 0;
}

```
### contiguous iterators (LegacyContiguousIterator)
在 C++17 中，引入了“连续迭代器”（Contiguous Iterators）的概念。

连续迭代器是一种特殊类型的迭代器，它们指向的元素在内存中是连续存储的。具有连续迭代器的容器可以保证它们的元素在内存中是紧密排列的，因此支持更高效的内存访问和处理。

std::vector 和 std::array 是连续容器，它们的迭代器是连续迭代器；而 std::list 和 std::map 是非连续容器，它们的迭代器不是连续迭代器。
```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用指针算法访问连续范围
    int* ptr = vec.data();
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << *ptr++ << " ";
    }

    // 使用算法处理连续范围
    int sum = std::accumulate(vec.begin(), vec.end(), 0);
    std::cout << "\nSum: " << sum << std::endl;

    return 0;
}

```
### non-member std::size/std::empty/std::data
在 C++17 中，引入了三个非成员函数 std::size、std::empty 和 std::data，用于方便地获取容器的大小、判空状态以及底层数据的指针。
```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    std::cout << "Size of the vector: " << std::size(numbers) << std::endl;

    if (std::empty(numbers)) {
        std::cout << "The vector is empty." << std::endl;
    } else {
        std::cout << "The vector is not empty." << std::endl;
    }

    int* dataPtr = std::data(numbers);
    for (size_t i = 0; i < std::size(numbers); ++i) {
        std::cout << dataPtr[i] << " ";
    }

    return 0;
}

```

## Numerics
### mathematical special functions 【查询不出来】
```c++

```
### 3D std::hypot【再查】
C++标准库的std::hypot函数用于计算两个参数的平方和的平方根（欧几里德范数）
```c++

```

## Other
### cache line interface
```c++

```
### std::launder
std::launder是一个非常有用的工具，用于处理指针的优化问题。它用于指示编译器避免对指针的优化，以确保指针在适当的时间访问正确的内存。
```c++
#include <iostream>

struct S {
    int value;
};

int main() {
    alignas(16) char buffer[sizeof(S)]; // Aligned buffer.
    S* ptr = new (buffer) S{42}; // Placement new to construct an object in the buffer.

    // Compiler optimizations might assume ptr->value is always 42,
    // even after the object has been modified.
    ptr->value = 99;

    // Incorrect access due to potential optimizations.
    // This might print 42 instead of 99.
    std::cout << ptr->value << std::endl;

    // Using std::launder to get the correct value.
    S* launderedPtr = std::launder(ptr);
    std::cout << launderedPtr->value << std::endl; // This will correctly print 99.

    return 0;
}

```
### std::uncaught_exceptions
用于获取当前未捕获异常的数量。
```c++
#include <iostream>
#include <exception>

int main() {
    try {
        throw std::runtime_error("Error!");
    }
    catch (...) {
        int uncaughtCount = std::uncaught_exceptions();
        std::cout << "Uncaught exceptions: " << uncaughtCount << std::endl;
    }

    return 0;
}

```
### std::to_chars/std::from_chars
用于将数字转换为字符串（字符序列）和将字符串（字符序列）解析为数字的函数。
```c++
#include <iostream>
#include <charconv>

int main() {
    char buffer[20];
    int value = 42;

    auto result = std::to_chars(buffer, buffer + 20, value);
    *result.ptr = '\0'; // Null-terminate the string.

    std::cout << "Result: " << buffer << std::endl;

////

const char* str = "12345";
    int value;

    auto result = std::from_chars(str, str + 5, value);

    if (result.ec == std::errc()) {
        std::cout << "Parsed value: " << value << std::endl;
    } else {
        std::cout << "Parsing failed." << std::endl;
    }
    return 0;
}



```
### std::atomic<T>::is_always_lock_free
std::atomic<T>::is_always_lock_free是std::atomic模板类的一个静态成员函数，用于查询给定类型T的std::atomic对象是否始终是无锁（lock-free）的。无锁意味着在多线程环境中，对std::atomic对象的操作不需要使用互斥锁，因此可以高效地执行。
```c++
#include <iostream>
#include <atomic>

int main() {
    std::atomic<int> atomicInt;

    // Check if the std::atomic<int> is always lock-free.
    bool isLockFree = std::atomic<int>::is_always_lock_free;

    std::cout << "std::atomic<int> is always lock-free: " << std::boolalpha << isLockFree << std::endl;

    return 0;
}
请注意，返回值为true并不意味着所有的操作都是无锁的，而只是表明对于给定类型T的std::atomic<T>对象，编译器保证其操作可以无锁执行。如果返回值为false，则表示编译器不保证其操作是无锁的，可能会使用锁机制来实现原子性。


```
### std::scoped_lock
用于简化对多个互斥量（std::mutex）进行锁定的操作。它可以一次性锁定多个互斥量，并在作用域结束时自动解锁，从而避免了手动管理锁的问题，更好地实现了多个互斥量的安全操作。
```c++
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mutex1;
std::mutex mutex2;

void function1() {
    std::scoped_lock lock(mutex1, mutex2); // Lock mutex1 and mutex2 together

    std::cout << "Function 1 is working..." << std::endl;
    // Do some work that requires both mutex1 and mutex2 locked.
}

void function2() {
    std::scoped_lock lock(mutex1, mutex2); // Lock mutex1 and mutex2 together

    std::cout << "Function 2 is working..." << std::endl;
    // Do some work that requires both mutex1 and mutex2 locked.
}

int main() {
    std::thread t1(function1);
    std::thread t2(function2);

    t1.join();
    t2.join();

    return 0;
}

```
### std::timespec_get
用于获取当前时间的高精度时间戳。它定义在头文件<ctime>中。
```c++
#include <iostream>
#include <ctime>

int main() {
    struct timespec ts;
    int result = std::timespec_get(&ts, TIME_UTC);

    if (result == TIME_UTC) {
        std::cout << "Current time: " << ts.tv_sec << " seconds and " << ts.tv_nsec << " nanoseconds" << std::endl;
    } else {
        std::cout << "Failed to get the current time." << std::endl;
    }

    return 0;
}

```
### rounding functions for std::chrono::duration and std::chrono::time_point
在C++11标准中，std::chrono库没有直接提供用于舍入（rounding）std::chrono::duration和std::chrono::time_point的函数。

```c++
#include <iostream>
#include <chrono>

template<typename Duration>
Duration round_duration(const Duration& duration, const typename Duration::rep& rounding_value) {
    return std::chrono::duration_cast<Duration>(
        (duration.count() >= 0) ? 
            (duration + Duration(rounding_value / 2)) / rounding_value * rounding_value :
            (duration - Duration(rounding_value / 2)) / rounding_value * rounding_value
    );
}

int main() {
    // Example: Round a duration to the nearest 100 milliseconds
    std::chrono::milliseconds duration(247);
    std::chrono::milliseconds rounded_duration = round_duration(duration, 100);
    std::cout << "Original duration: " << duration.count() << " ms\n";
    std::cout << "Rounded duration: " << rounded_duration.count() << " ms\n";

    return 0;
}
```

```c++
#include <iostream>
#include <chrono>

template<typename Clock, typename Duration>
std::chrono::time_point<Clock, Duration> round_time_point(const std::chrono::time_point<Clock, Duration>& time_point, const typename Duration::rep& rounding_value) {
    auto duration_since_epoch = time_point.time_since_epoch();
    auto rounded_duration = round_duration(duration_since_epoch, rounding_value);
    return std::chrono::time_point<Clock, Duration>(rounded_duration);
}

int main() {
    // Example: Round a time_point to the nearest 5 minutes
    std::chrono::system_clock::time_point time_point = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point rounded_time_point = round_time_point(time_point, std::chrono::minutes(5).count());
    
    std::cout << "Original time_point: " << std::chrono::system_clock::to_time_t(time_point) << "\n";
    std::cout << "Rounded time_point: " << std::chrono::system_clock::to_time_t(rounded_time_point) << "\n";

    return 0;
}

```
