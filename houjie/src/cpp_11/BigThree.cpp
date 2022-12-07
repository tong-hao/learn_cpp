
// =default
// =delete

// Big-three(拷贝构造、拷贝赋值、析构函数)
// 注意1: class Empty{}; 空类编译器会默认生成big-three
// 注意2: 当类成员中有指针时候，就不能使用编译器合成的big-three

// 5个特殊函数
class Zoo {
public:
	Zoo() = default;                       // 构造器
	Zoo(const Zoo&) = default;             // 拷贝构造
	Zoo& operator=(const Zoo&) = default;  // 拷贝赋值

	Zoo(Zoo&&) = delete;             // 移动构造
	Zoo& operator=(Zoo&&) = delete;  // 移动赋值

	~Zoo() = default;  // 析构
};
