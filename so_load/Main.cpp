

#include <dlfcn.h>
#include <iostream>
#include "AppBase.h"

int main() {
	// 加载动态库
	void* handle = dlopen(
	    "/home/caton.hao/build_code/others/cpp_learning/so_load/app_a/build/"
	    "lib/libapp1.so",
	    RTLD_LAZY);
	if (!handle) {
		std::cerr << "Failed to load dynamic library: " << dlerror()
		          << std::endl;
		return 1;
	}

	// 获取动态库中的类构造函数
	typedef AppBase* (*CreateAppFunc)();
	CreateAppFunc createApp =
	    reinterpret_cast<CreateAppFunc>(dlsym(handle, "createApp"));
	if (!createApp) {
		std::cerr << "Failed to find symbol createApp: " << dlerror()
		          << std::endl;
		dlclose(handle);
		return 1;
	}

	// 创建 App 对象
	AppBase* app1 = createApp();

	// // 调用 name() 方法
	// typedef std::string (AppBase::*NameFunc)();
	// NameFunc nameFunc = &AppBase::name;
	// std::string name = (app1->*nameFunc)();
	// std::cout << "App name: " << name << std::endl;

	std::cout << "App name: " << app1->name() << std::endl;

	// 释放资源
	dlclose(handle);
	delete app1;
	return 0;
}
