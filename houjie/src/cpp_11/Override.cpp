// override 的用法
struct Base {
	virtual void f();
};
struct Derived1 : Base {
	virtual void f() override;  // 避免名字写错
};
