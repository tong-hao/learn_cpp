#include <glog/logging.h>
#include <memory>

int main(int argc, char const* argv[]) {
	google::SetLogDestination(100, "./applog.log");

	LOG(100) << "hello";

	return 0;
}
