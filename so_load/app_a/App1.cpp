#include "AppBase.h"

class App1 : public AppBase {
public:
	std::string name() {
		return "app1";
	}
};

extern "C" AppBase* createApp() {
	AppBase* app = new App1();
	return app;
}
