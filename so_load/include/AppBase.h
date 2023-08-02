#pragma once

#include <string>

class AppBase {
public:
	virtual std::string name() = 0;
};

extern "C" AppBase* createApp();
