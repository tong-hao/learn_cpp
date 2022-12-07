
// final的用法:

// 1)
struct Base1 final {};  // 没有人继承了

// 2)
struct Base2 {
	virtual void f() final;  // 不允许覆写
};
