# c++20

## New language features

### Feature test macros
C++20 中引入的功能测试宏：
__cpp_modules：检查是否支持 C++20 的模块（Modules）特性。模块是一种新的代码组织方式，可以提高编译速度并减少头文件相关的问题。

__cpp_concepts：检查是否支持概念（Concepts）特性。概念允许你对模板参数设置约束，改善模板错误信息，并支持更精确的模板特化。

__cpp_coroutines：检查是否支持 C++20 协程（Coroutines）。协程引入了一种更可读且结构化的编写异步代码的方式。

__cpp_ranges：这个宏表示是否支持 C++20 范围（Ranges）特性，它提供了一种更直观和可组合的方式来处理值的序列。

__cpp_three_way_comparison：检查是否支持 C++20 的三路比较运算符（operator<=>），它简化了对象之间的比较操作。

__cpp_constexpr_dynamic_alloc：判断是否支持在 constexpr 上下文中进行动态内存分配（constexpr dynamic memory allocation），即在 new 和 delete 中使用 constexpr。

__cpp_aggregate_paren_init：检查是否支持使用圆括号进行聚合初始化。这允许你使用圆括号而不是大括号来初始化聚合类型。

__cpp_designated_initializers：判断是否支持 C++20 的指定初始化器（designated initializers），允许你使用指定的语法初始化结构体或类的特定成员。

__cpp_impl_three_way_comparison：类似于 __cpp_three_way_comparison，但检查的是三路比较的实现状态，而不是语言本身是否支持。

__cpp_using_enum：检查是否支持使用 using 声明将枚举引入到较小的作用域中的特性。

__cpp_char8_t：判断是否支持 char8_t 类型，该类型用于表示 UTF-8 字符字面量。
```c++
#if __cpp_modules
    // 依赖 Modules 特性的代码
#endif

#if __cpp_concepts
    // 依赖 Concepts 特性的代码
#endif

```

### Three-way comparison operator <=> and operator==() = default
```c++
// 1)
std::strong_ordering result = value1 <=> value2;
if (result == std::strong_ordering::less) {
    // value1 < value2
} else if (result == std::strong_ordering::equal) {
    // value1 == value2
} else {
    // value1 > value2
}

// 2)
// 在 C++20 中，对于类类型，默认情况下会自动生成 operator==() 操作符，这个操作符用于比较两个对象是否相等
class Person {
public:
    // 类的成员定义...

    // 在 C++20 中不需要显式定义 operator==()

    // 其他成员函数...
};

```

### Designated initializers
C++20 引入了指定初始化器（Designated Initializers）的特性，这使得在初始化结构体或类的成员时更加灵活和可读。指定初始化器允许你在初始化表达式中使用成员的名字来指定特定的成员进行初始化，而不必按照成员的顺序进行初始化。
```c++
struct Point {
    int x;
    int y;
    int z;
};

int main() {
    Point p = {.x = 10, .z = 20}; // 使用指定初始化器
    // p.x = 10, p.y = 0, p.z = 20

    return 0;
}

```

### Init-statements and initializers in range-for
使用 C++20 提供的新特性，你可以在范围 for 循环中使用逗号分隔的初始化语句，这些语句会在循环开始之前执行。同时，你还可以在范围 for 循环中的循环体内使用初始化器，以便在每次迭代时执行。
```c++
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    for (int i = 0; i < numbers.size(); ++i) {
        int num = numbers[i];
        std::cout << "Current number: " << num << std::endl;
    }

   
    // C++20
    for (int i = 0, num; i < numbers.size() && (num = numbers[i]); ++i) {
        std::cout << "Current number: " << num << std::endl;
    }

    return 0;
}

```

### char8_t
C++20 引入了 char8_t 类型, 用于表示 UTF-8 编码的字符.
```c++
#include <iostream>

int main() {
    const char8_t* utf8String = u8"Hello, 你好, こんにちは";
    std::cout << utf8String << std::endl;

    for (char8_t c : u8"🌍🌎🌏") {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0;
}

```

### New attributes: `[[no_unique_address]], [[likely]], [[unlikely]]`
`[[no_unique_address]]` 属性用于告诉编译器，如果一个成员变量在其所在的类中没有独立的地址（即对齐和布局的限制导致这个成员变量与前一个成员重叠），则可以将其合并到其他成员中，从而减小这个类的大小。
[[likely]] 和 [[unlikely]] 属性用于向编译器提供分支预测的提示。你可以在条件语句上使用这些属性，指示该条件在运行时的可能性。[[likely]] 表示条件的结果很可能为真，而 [[unlikely]] 表示条件的结果很可能为假。

编译器可以利用这些提示来优化代码，例如进行指令重排、分支预测等操作，以提高代码的性能。

```c++
#include <iostream>

[[no_unique_address]]
struct Empty {};

int main() {
    Empty e;

    if constexpr(sizeof(Empty) == 1) {
        std::cout << "sizeof(Empty) == 1" << std::endl;
    }

    if [[likely]] (true) {
        std::cout << "This is likely to be true" << std::endl;
    }

    if [[unlikely]] (false) {
        std::cout << "This is unlikely to be true" << std::endl;
    }

    return 0;
}

```

### Pack-expansions in lambda init-captures
允许在 lambda 表达式的初始化捕获（init-captures）中使用参数包展开（pack-expansions）。
```c++
#include <iostream>

int main() {
    int x = 10;
    int y = 20;
    int z = 30;

    auto lambda = [x, y, ...args = z]() {
        std::cout << "x: " << x << std::endl;
        std::cout << "y: " << y << std::endl;

        std::cout << "Other arguments:" << std::endl;
        ((std::cout << args << std::endl), ...); // 参数包展开

        std::cout << "Sum: " << (x + y + ... + args) << std::endl; // 参数包展开
    };

    lambda();

    return 0;
}

```

### Removed the requirement to use typename to disambiguate types in many contexts
```c++
// Before C++20
template <typename T>
struct Example {
    typename T::value_type member; // typename was required

    void foo(typename T::iterator it) { /* ... */ }
};

// In C++20
template <typename T>
struct Example {
    T::value_type member; // No need for typename

    void foo(T::iterator it) { /* ... */ }
};

```

### consteval, constinit
consteval 关键字用于在编译时执行函数的计算，确保函数的调用仅在编译期间进行。
constinit 关键字用于确保变量在静态存储持续期间。
```c++
consteval int Square(int x) {
    return x * x;
}

int main() {
    constexpr int result = Square(5); // 编译时计算，结果是 25
    return 0;
}
//----
constinit int globalValue = 10; // 在静态存储期间进行初始化

```

### Further relaxed constexpr
C++20 进一步放宽了 constexpr 的使用。在之前的 C++版本中，constexpr 被要求只能用于一些简单的表达式、函数和构造函数。
放宽：更大的函数体、循环、分支、异常
```c++

```

### Signed integers are 2's complement
从 C++20 开始，C++ 标准现在要求使用 2 的补码表示来表示有符号整数。这个变化为不同平台上有符号整数的行为带来了更一致和可预测的性质。
2 的补码表示是一种广泛使用的在二进制形式中表示负整数的方式。在这种表示中：
- 最高有效位（MSB）是符号位。如果为 0，则表示数是正数；如果为 1，则表示数是负数。
- 剩余位表示数的大小。
2 的补码的关键属性是，将一个负数的二进制表示与它的正数对应部分的二进制表示相加会得到零。这个属性简化了硬件中的加法和减法操作。
C++20 中的这个变化使得有符号整数的行为与现代硬件架构保持一致，因为大多数现代处理器中都广泛使用 2 的补码表示。


### Bitwise shift operators unified behavior
在 C++20 中，位移操作符的行为得到了统一。在以前的标准中，左移位超出了可表示范围的行为是未定义的，但在 C++20 中，这个行为已经定义为执行逻辑位移，丢弃超出位的值。右移位的行为也得到了统一，当操作数为有符号类型且负数时，右移将执行算术位移，补充符号位。
```c++
#include <iostream>

int main() {
    unsigned int value = 0x80000000; // Binary: 10000000...0000

    value = value << 1; // Left shift
    std::cout << std::hex << value << std::endl; // Output: 0x00000000

    int negativeValue = -1;
    negativeValue = negativeValue >> 1; // Right shift
    std::cout << negativeValue << std::endl; // Output: -1

    return 0;
}


```

### aggregate initialization using parentheses
C++20 允许使用圆括号来进行聚合初始化。之前，只能使用大括号进行聚合初始化，但现在可以使用圆括号，使代码更加灵活。
```c++
struct Point {
    int x;
    int y;
};

int main() {
    Point p = (Point{1, 2}); // 使用圆括号进行聚合初始化
    return 0;
}

```

### coroutines
C++20 引入了协程（Coroutines）的支持，允许以更清晰和结构化的方式编写异步代码。协程允许函数在中途挂起并在稍后恢复执行，从而简化异步操作的编写。
```c++
#include <iostream>
#include <coroutine>

struct MyCoroutine {
    struct promise_type {
        MyCoroutine get_return_object() {
            return MyCoroutine{std::coroutine_handle<promise_type>::from_promise(*this)};
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> handle;

    MyCoroutine(std::coroutine_handle<promise_type> h) : handle(h) {}

    ~MyCoroutine() {
        if (handle) handle.destroy();
    }

    void resume() {
        if (handle) handle.resume();
    }
};

MyCoroutine myAsyncTask() {
    std::cout << "Start of coroutine" << std::endl;
    co_await std::suspend_always{};
    std::cout << "End of coroutine" << std::endl;
}

int main() {
    MyCoroutine coroutine = myAsyncTask();
    coroutine.resume();
    return 0;
}

```

### modules
C++20 引入了模块（Modules）的支持，用于改善头文件管理和加速编译过程。模块允许将代码划分为逻辑模块，以便更有效地组织代码并减少头文件的依赖问题。

```c++
// math.h
export module math;

export int add(int a, int b) {
    return a + b;
}

// main.cpp
import math;

int main() {
    int result = add(3, 4);
    return 0;
}

```

### Constraints and concepts
C++20 引入了约束（Constraints）和概念（Concepts），允许你对模板参数设置约束条件，以提高模板错误信息和支持更精确的模板特化。
```c++
template <typename T>
concept Integral = std::is_integral_v<T>;

template <Integral T>
T square(T x) {
    return x * x;
}

int main() {
    int result = square(5);
    return 0;
}

```

### Abbreviated function template
缩写函数模板（Abbreviated Function Template）是 C++20 中引入的一个特性，允许在函数声明或函数模板声明的参数列表中使用占位类型（placeholder types，例如 auto 或 Concept auto）。当在参数列表中使用占位类型时，编译器会为每个占位类型添加一个虚拟的模板参数，从而形成一个函数模板。
```c++
#include <iostream>
#include <concepts>

// 使用占位类型 auto，编译器会根据参数类型自动推导模板参数
void f1(auto x) {
    std::cout << x << std::endl;
}

// 使用占位类型 Concept auto，需要一个相关的概念（concept）来约束类型
template <typename T>
concept MyConcept = std::is_integral_v<T>;

void f2(MyConcept auto x) {
    std::cout << x << std::endl;
}

// 使用占位类型 Concept auto...，允许多个参数
template <typename T>
concept AnotherConcept = std::is_floating_point_v<T>;

void f3(AnotherConcept auto... args) {
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

// 使用占位类型 const Concept auto* 和 Concept auto&
template <typename T>
concept ConstConcept = std::is_const_v<T>;

template <typename T>
concept ReferenceConcept = std::is_reference_v<T>;

void f4(const ConstConcept auto* ptr, ReferenceConcept auto& ref) {
    std::cout << *ptr << " " << ref << std::endl;
}

int main() {
    f1(42);        // 调用 f1<int>(42)
    f2(5);         // 调用 f2<int>(5)
    f3(1.1, 2.2);  // 调用 f3<double, double>(1.1, 2.2)
    int x = 10;
    f4(&x, x);     // 调用 f4<const int>(&x, x)

    return 0;
}


```

### DR11: array new can deduce array size 【可能不对】
C++20 中引入了 DR11 提案，允许在使用 new 运算符创建数组时，自动推断数组的大小。
```c++
#include <iostream>

int main() {
    int size = 5;
    int* arr = new int[size]; // C++20 允许自动推断数组大小
    delete[] arr;
    return 0;
}

```

## New library features
### New headers
```
<bit>
<compare>
<concepts>
<coroutine>
<format>
<numbers>
<ranges>
<source_location>
<span>
<syncstream>
<version>

<barrier>
<latch>
<semaphore>
<stop_token>

```


## Library features


### Library feature-test macros
```c++
#include <iostream>

int main() {
    // 检查是否支持 C++20 的某个特性
    #ifdef __cpp_consteval
        std::cout << "C++20 consteval is supported." << std::endl;
    #else
        std::cout << "C++20 consteval is not supported." << std::endl;
    #endif

    return 0;
}

```

### Formatting library
```c++
#include <iostream>
#include <format>

int main() {
    std::string name = "Alice";
    int age = 30;

    std::string formatted = std::format("My name is {} and I am {} years old.", name, age);
    std::cout << formatted << std::endl;

    return 0;
}

```

### Concepts library
```c++
#include <iostream>
#include <concepts>

template <typename T>
concept Integral = std::is_integral_v<T>;

template <Integral T>
T square(T x) {
    return x * x;
}

int main() {
    int result = square(5); // 编译时检查类型是否符合约束
    std::cout << "Square: " << result << std::endl;

    return 0;
}

```

### Calendar and Time zone library in <chrono>
C++20 在 <chrono> 标准库中引入了日历和时区库，使处理日期、时间和时区变得更加便捷。
```c++
#include <iostream>
#include <chrono>

int main() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);

    std::cout << "Current time: " << std::ctime(&now_t);

    return 0;
}

```

### std::source_location
C++20 引入了 std::source_location 类，用于获取代码的源代码位置信息，例如文件名、行号、函数名等。这对于编写日志和调试信息非常有用。
```c++
#include <iostream>
#include <source_location>

void log(const std::string& message, const std::source_location& loc = std::source_location::current()) {
    std::cout << "File: " << loc.file_name() << ", Line: " << loc.line() << ": " << message << std::endl;
}

int main() {
    log("Hello, world!");
    return 0;
}

```

### std::span
C++20 引入了 std::span 类，用于表示一段连续的内存区域，类似于指针和长度的组合。这对于传递数组信息或进行内存操作非常有用，同时避免了指针和长度分离导致的错误。
```c++
#include <iostream>
#include <span>

void print_numbers(std::span<int> numbers) {
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::span<int> span_arr(arr, 5);

    print_numbers(span_arr);

    return 0;
}

```

### std::endian: big / little / native
std::endian 是一个枚举类型，用于表示机器的字节序。它定义了三个值：std::endian::big、std::endian::little 和 std::endian::native，分别表示大端字节序、小端字节序和本机字节序。
```c++
#include <iostream>
#include <bit>

int main() {
    if (std::endian::native == std::endian::little) {
        std::cout << "This machine uses little-endian byte order." << std::endl;
    } else if (std::endian::native == std::endian::big) {
        std::cout << "This machine uses big-endian byte order." << std::endl;
    } else {
        std::cout << "Byte order of this machine is unknown." << std::endl;
    }

    return 0;
}

```

### Integral power-of-2 operations and std::bit_cast in <bit>
C++20 引入了 <bit> 头文件，提供了一组处理整数的 2 的幂次方运算的函数，以及一个用于进行位级别转换的 std::bit_cast 函数。
```c++
#include <iostream>
#include <bit>

int main() {
    // 检查是否是 2 的幂次方
    if (std::has_single_bit(16)) {
        std::cout << "16 is a power of 2." << std::endl;
    }

    // 计算下一个 2 的幂次方
    int next_power_of_2 = std::next_power_of_2(10);
    std::cout << "Next power of 2 after 10: " << next_power_of_2 << std::endl;

    // 使用 std::bit_cast 进行位级别转换
    float f = 3.14f;
    unsigned int bits = std::bit_cast<unsigned int>(f);
    std::cout << "Float to bits: " << bits << std::endl;

    return 0;
}

```

### Array support for std::make_shared
C++20 为 std::make_shared 引入了对动态数组的支持。
```c++
#include <iostream>
#include <memory>

int main() {
    auto arr = std::make_shared<int[]>(5); // 创建包含 5 个元素的动态数组
    arr[0] = 1;
    arr[1] = 2;

    std::cout << "Array element 0: " << arr[0] << std::endl;
    std::cout << "Array element 1: " << arr[1] << std::endl;

    return 0;
}

```

### std::remove_cvref
std::remove_cvref 是一个类型转换工具，用于移除类型的 const、volatile 和引用修饰，得到原始类型。
```c++
#include <iostream>
#include <type_traits>

int main() {
    using T = const volatile int&;
    using U = std::remove_cvref_t<T>;

    std::cout << std::is_same_v<T, U> << std::endl; // 输出 0（不同的类型）
    std::cout << std::is_same_v<int, U> << std::endl; // 输出 1（相同的类型）

    return 0;
}

```

### std::to_address
std::to_address 是一个指针工具函数，用于从智能指针、迭代器或原始指针中获取底层指针。
```c++
#include <iostream>
#include <memory>

int main() {
    std::shared_ptr<int> ptr = std::make_shared<int>(42);

    int* raw_ptr = std::to_address(ptr); // 获取底层指针
    std::cout << *raw_ptr << std::endl;

    return 0;
}

```

### Floating-point atomics, std::atomic atomics
C++20 引入了浮点数原子操作
```c++
#include <iostream>
#include <atomic>
#include <thread>

int main() {
    std::atomic<int> counter = 0;

    std::thread t1([&]() {
        for (int i = 0; i < 100000; ++i) {
            counter.fetch_add(1, std::memory_order_relaxed);
        }
    });

    std::thread t2([&]() {
        for (int i = 0; i < 100000; ++i) {
            counter.fetch_sub(1, std::memory_order_relaxed);
        }
    });

    t1.join();
    t2.join();

    std::cout << "Counter value: " << counter.load() << std::endl;

    return 0;
}

```

### Thread-coordination classes: std::barrier, std::latch, and std::counting_semaphore
C++20 引入了一些线程协调类，如 std::barrier、std::latch 和 std::counting_semaphore，用于实现更高级的线程同步。
```c++
#include <iostream>
#include <thread>
#include <barrier>

int main() {
    constexpr int num_threads = 4;
    std::barrier<num_threads> barrier;

    std::thread threads[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread([&](int id) {
            std::cout << "Thread " << id << " before barrier" << std::endl;
            barrier.arrive_and_wait();
            std::cout << "Thread " << id << " after barrier" << std::endl;
        }, i);
    }

    for (int i = 0; i < num_threads; ++i) {
        threads[i].join();
    }

    return 0;
}


```

### std::jthread and thread cancellation classes: std::stop_token, std::stop_source, and std::stop_callback
C++20 引入了 std::jthread 类，用于更安全地管理线程的生命周期。同时，还引入了线程取消相关的类，如 std::stop_token、std::stop_source 和 std::stop_callback，用于实现线程的安全取消。
```c++
#include <iostream>
#include <thread>

int main() {
    std::stop_source stopSrc;
    std::stop_token stopToken = stopSrc.get_token();

    std::jthread thread([&](std::stop_token stoken) {
        while (!stoken.stop_requested()) {
            std::cout << "Thread running..." << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        std::cout << "Thread canceled." << std::endl;
    }, stopToken);

    std::this_thread::sleep_for(std::chrono::seconds(3));
    stopSrc.request_stop();

    thread.join();

    return 0;
}

```

### std::basic_osyncstream
C++20 引入了 std::basic_osyncstream 类,用于实现线程安全的输出流，可以在多线程环境下进行输出，避免了输出混乱的问题。

```c++
#include <iostream>
#include <ostream>
#include <thread>

int main() {
    std::ostream sync_out(nullptr);
    std::basic_osyncstream sync_stream(sync_out);

    std::thread t1([&]() {
        sync_stream << "Hello from thread 1!" << std::endl;
    });

    std::thread t2([&]() {
        sync_stream << "Hello from thread 2!" << std::endl;
    });

    t1.join();
    t2.join();

    return 0;
}

```

### std::basic_string and other char8_t uses
C++20 引入了对 char8_t 类型的支持
```c++
#include <iostream>
#include <string>

int main() {
    std::basic_string<char8_t> utf8_string = u8"Hello, 世界!";
    std::cout << "UTF-8 String: " << utf8_string << std::endl;

    return 0;
}

```

### constexpr for <algorithm>, <utility>, <complex>
C++20 扩展了一些标准库算法、实用函数和复数类型的 constexpr 支持，允许在编译时计算和操作这些函数。
```c++
#include <iostream>
#include <algorithm>
#include <utility>
#include <complex>

constexpr int factorial(int n) {
    return n == 0 ? 1 : n * factorial(n - 1);
}

int main() {
    constexpr int result = std::clamp(5, 0, 10); // 编译时计算
    std::cout << "Clamped value: " << result << std::endl;

    constexpr int gcd_result = std::gcd(24, 36); // 编译时计算
    std::cout << "GCD: " << gcd_result << std::endl;

    constexpr std::complex<double> complex_number = std::polar(1.0, 3.14159); // 编译时计算
    std::cout << "Complex number: " << complex_number.real() << " + " << complex_number.imag() << "i" << std::endl;

    constexpr int fact_result = factorial(5); // 编译时计算
    std::cout << "Factorial: " << fact_result << std::endl;

    return 0;
}


```

### string::starts_with / ends_with and string_view::starts_with / ends_with
```c++
#include <iostream>
#include <string>

int main() {
    std::string str = "Hello, world!";
    std::string_view str_view = "Hello";

    if (str.starts_with("Hello")) {
        std::cout << "String starts with 'Hello'" << std::endl;
    }

    if (str.ends_with("world!")) {
        std::cout << "String ends with 'world!'" << std::endl;
    }

    if (str_view.starts_with("Hello")) {
        std::cout << "String view starts with 'Hello'" << std::endl;
    }

    if (str_view.ends_with("ello")) {
        std::cout << "String view ends with 'ello'" << std::endl;
    }

    return 0;
}

```

### std::assume_aligned
std::assume_aligned 是一个编译器提示函数，用于告知编译器某个指针的对齐情况，以便优化代码。这对于在需要手动管理内存对齐的情况下非常有用。
```c++
#include <iostream>
#include <cstdint>

int main() {
    alignas(16) int data[4] = {1, 2, 3, 4};
    int* ptr = std::assume_aligned<16>(data);

    std::cout << "Is ptr aligned to 16 bytes? " << (reinterpret_cast<std::uintptr_t>(ptr) % 16 == 0) << std::endl;

    return 0;
}

```

### std::bind_front
std::bind_front 是一个函数对象生成器，用于创建一个新的函数对象，该函数对象是通过绑定一个参数到现有函数对象的前面实现的。
```c++
#include <iostream>
#include <functional>

void print_sum(int a, int b, int c) {
    std::cout << a + b + c << std::endl;
}

int main() {
    auto print_sum_10 = std::bind_front(print_sum, 10);
    print_sum_10(20, 30); // 输出 60

    return 0;
}

```

### std::c8rtomb / std::mbrtoc8
std::c8rtomb 是一个函数，用于将 Unicode 码位转换为 UTF-8 编码
```c++
#include <iostream>
#include <cuchar>

int main() {
    char utf8_bytes[4];
    std::size_t bytes_written = std::c8rtomb(utf8_bytes, U'世', nullptr);

    for (std::size_t i = 0; i < bytes_written; ++i) {
        std::cout << "Byte " << i << ": " << static_cast<int>(utf8_bytes[i]) << std::endl;
    }

    const char* utf8_sequence = "\xE4\xB8\x96"; // UTF-8 编码的 "世"
    char32_t code_point;
    std::mbstate_t state = std::mbstate_t();
    std::size_t chars_read = std::mbrtoc8(reinterpret_cast<char8_t*>(&code_point), utf8_sequence, 4, &state);

    std::cout << "Code point: " << code_point << std::endl;

    return 0;
}

```

### std::make_obj_using_allocator etc
std::make_obj_using_allocator 是一个函数模板，用于创建对象并使用分配器分配内存。
这在需要自定义内存分配的情况下非常有用。
```c++
#include <iostream>
#include <memory>

class MyClass {
public:
    MyClass(int val) : value(val) {}

    int getValue() const {
        return value;
    }

private:
    int value;
};

int main() {
    std::allocator<MyClass> allocator;
    MyClass* obj = std::make_obj_using_allocator<MyClass>(allocator, 42);

    std::cout << "Value: " << obj->getValue() << std::endl;

    allocator.destroy(obj);
    allocator.deallocate(obj, 1);

    return 0;
}

```

### std::make_shared / std::make_unique
C++20 引入了对 std::make_shared 和 std::make_unique 的优化,使得这两个函数更加高效，减少了动态内存分配次数。
```c++
#include <iostream>
#include <memory>

int main() {
    auto shared_ptr = std::make_shared<int>(42);
    auto unique_ptr = std::make_unique<int>(42);

    std::cout << "Shared pointer value: " << *shared_ptr << std::endl;
    std::cout << "Unique pointer value: " << *unique_ptr << std::endl;

    return 0;
}

```

### Heterogeneous lookup in unordered associative containers
C++20 引入了对无序关联容器的异构查找支持，允许使用不同类型的键进行查找。
```c++
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
    std::unordered_map<std::string, int> map = {{"one", 1}, {"two", 2}, {"three", 3}};

    const char* key = "two";
    auto it = map.find(key); // 可以使用 const char* 进行查找

    if (it != map.end()) {
        std::cout << "Value for key '" << key << "': " << it->second << std::endl;
    }

    return 0;
}

```

### std::pmr::polymorphic_allocator with additional member functions and std::byte as its default template argument
std::pmr::polymorphic_allocator 是一个多态分配器，支持动态内存分配策略的切换。C++20 扩展了其成员函数，并引入了 std::byte 作为默认的模板参数。
```c++
#include <iostream>
#include <memory_resource>
#include <vector>

int main() {
    std::pmr::polymorphic_allocator<int> alloc;
    std::vector<int> vec{1, 2, 3, 4, 5};

    for (int num : vec) {
        alloc.construct(&num, num); // 使用多态分配器构造对象
    }

    for (int num : vec) {
        std::cout << num << " ";
    }

    return 0;
}

```

### execution::unseq
C++20 引入了 execution::unseq 执行策略，用于指示编译器在算法中进行并行优化，而不考虑顺序。
```c++
#include <iostream>
#include <algorithm>
#include <execution>
#include <vector>

int main() {
    std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3};

    std::sort(std::execution::unseq, nums.begin(), nums.end());

    for (int num : nums) {
        std::cout << num << " ";
    }

    return 0;
}

```

### std::midpoint and std::lerp
C++20 引入了 std::midpoint 函数，用于计算两个数的中点。同时，还引入了 std::lerp 函数，用于执行线性插值。
```c++
#include <iostream>
#include <numeric>
#include <cmath>

int main() {
    int a = 10;
    int b = 20;

    int mid = std::midpoint(a, b); // 计算中点
    std::cout << "Midpoint: " << mid << std::endl;

    double result = std::lerp(1.0, 2.0, 0.5); // 线性插值
    std::cout << "Lerp result: " << result << std::endl;

    return 0;
}

```

### std::size
std::size 是一个函数模板，用于获取数组或容器的元素数量。它的使用方式类似于 C++17 引入的 std::size.
```c++
#include <iostream>
#include <vector>

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec = {6, 7, 8, 9, 10};

    std::cout << "Array size: " << std::size(arr) << std::endl;
    std::cout << "Vector size: " << std::size(vec) << std::endl;

    return 0;
}

```

### std::is_bounded_array, std::is_unbounded_array
std::is_bounded_array 和 std::is_unbounded_array 是类型特征 trait，用于判断一个类型是否是有界数组或无界数组。
```c++
#include <iostream>
#include <type_traits>

int main() {
    int arr1[5];
    int* arr2 = new int[10];

    std::cout << std::boolalpha;
    std::cout << "Is arr1 bounded array? " << std::is_bounded_array_v<decltype(arr1)> << std::endl;
    std::cout << "Is arr2 bounded array? " << std::is_bounded_array_v<decltype(arr2)> << std::endl;
    std::cout << "Is arr1 unbounded array? " << std::is_unbounded_array_v<decltype(arr1)> << std::endl;
    std::cout << "Is arr2 unbounded array? " << std::is_unbounded_array_v<decltype(arr2)> << std::endl;

    delete[] arr2;

    return 0;
}

```

### Ranges
C++20 引入了 <ranges> 头文件，提供了新的标准库范围（ranges）概念，以及一系列用于操作范围的函数和算法，简化了代码并提高了可读性。
```c++
#include <iostream>
#include <ranges>
#include <vector>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};

    auto even_nums = nums | std::views::filter([](int num) { return num % 2 == 0; });
    for (int num : even_nums) {
        std::cout << num << " ";
    }

    return 0;
}

```

### Uniform container erasure: std::erase / std::erase_if, e.g. std::erase(std::list) or erase_if(std::map) etc
C++20 引入了 std::erase 和 std::erase_if 函数，用于在容器中删除指定的元素。
```c++
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5, 3};

    std::erase(nums, 3); // 删除所有值为 3 的元素

    for (int num : nums) {
        std::cout << num << " ";
    }

    return 0;
}

```

### Mathematical constants in <numbers>
<numbers> 头文件引入了一些数学常量，如圆周率和自然对数基数。
```c++
#include <iostream>
#include <numbers>

int main() {
    std::cout << "Pi: " << std::numbers::pi << std::endl;
    std::cout << "E: " << std::numbers::e << std::endl;

    return 0;
}

```
