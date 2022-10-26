#include <folly/File.h>
#include <folly/FileUtil.h>
#include <folly/logging/FileHandlerFactory.h>
#include <folly/logging/FileWriterFactory.h>
#include <folly/logging/LogConfig.h>
#include <folly/logging/LogHandlerConfig.h>
#include <folly/logging/Logger.h>
#include <folly/logging/LoggerDB.h>
#include <folly/logging/StandardLogHandler.h>
#include <folly/logging/xlog.h>
#include <iostream>

#include <folly/logging/LogWriter.h>

int main(int argc, char const* argv[]) {
	// first step : register file factory and unregister old stream factory.
	folly::LoggerDB::get().registerHandlerFactory(
	    std::make_unique<folly::FileHandlerFactory>());
	folly::LoggerDB::get().unregisterHandlerFactory("stream");

	std::unordered_map<std::string, std::string> xlogOptions;
	xlogOptions["path"] = "./slow.log";
	xlogOptions["async"] = "false";
	// xlogOptions["max_buffer_size"] = "1";
	xlogOptions["formatter"] = "custom";
	xlogOptions["log_format"] = "";

	auto xlogHandlerConfig = folly::LogHandlerConfig("file", xlogOptions);

	folly::LogConfig xlogConfig({{"default", xlogHandlerConfig}}, {});

	// third step : update xlog.
	folly::LoggerDB::get().updateConfig(xlogConfig);

	XLOG(INFO) << "info...";
	XLOG(ERR) << "error...";

	folly::Logger eventLogger("eden.events");
	FB_LOG(eventLogger, INFO) << "something happened";

	{
		folly::FileWriterFactory fc;
		fc.processOption("async", "true");
		fc.processOption("max_buffer_size", "100");

		auto w = fc.createWriter(
		    folly::File("./output1.txt", O_WRONLY | O_APPEND | O_CREAT));
		w->writeMessage(std::string("hello output"));
	}

	{
		std::string buffer{"hello"};
		auto file_ =
		    folly::File("./output2.txt", O_WRONLY | O_APPEND | O_CREAT);
		auto ret = folly::writeFull(file_.fd(), buffer.data(), buffer.size());
		std::cout << ret << std::endl;
	}

	{
		folly::FileHandlerFactory factory;
		auto options = folly::LogHandlerFactory::Options{
		    std::make_pair("path", "./output3.txt"),
		    std::make_pair("max_buffer_size", "4096000"),
		};
		auto handler = factory.createHandler(options);

		auto stdHandler =
		    std::dynamic_pointer_cast<folly::StandardLogHandler>(handler);
		stdHandler->getWriter()->writeMessage(std::string("hello"));
	}
	return 0;
}
