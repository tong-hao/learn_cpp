#include <fmt/format.h>
#include <folly/Benchmark.h>
#include <folly/Conv.h>
#include <folly/container/Foreach.h>
#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include <glog/logging.h>
#include <regex>

std::map<std::string, std::regex> regex_map{
    {"^(/gflags)(/[^/]*/?)?$", std::regex("^(/gflags)(/[^/]*/?)?$")}};

bool matchWithStatic(const std::string& s, const std::string& regex_str) {
	std::smatch m;
	auto iter = regex_map.find(regex_str);
	CHECK(iter != regex_map.end());
	return std::regex_search(s, m, iter->second);
}

bool match(const std::string& s, const std::string& regex_str) {
	std::smatch m;
	std::regex e(regex_str);
	return std::regex_search(s, m, e);
}

BENCHMARK(matchWithStatic, iters) {
	folly::BenchmarkSuspender braces;
	std::string regex_str = "^(/gflags)(/[^/]*/?)?$";
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		matchWithStatic(fmt::format("/gflags/benchmark{}", i), regex_str);
	}
}

BENCHMARK(match, iters) {
	folly::BenchmarkSuspender braces;
	std::string regex_str = "^(/gflags)(/[^/]*/?)?$";
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		match(fmt::format("/gflags/benchmark{}", i), regex_str);
	}
}

int main(int argc, char** argv) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);

	folly::runBenchmarks();
	return 0;
}
/* clang-format off
============================================================================
HdfsFileParserBenchmark.cpp                               time/iter  iters/s
============================================================================
hdfs_write                                                   2.62us  381.75K
hdfs_read                                                    1.73us  578.27K
============================================================================
*/

// link:-lfolly -lfmt -lglog -lgflags -lpthread -ldl -ldouble-conversion
// link:-lfollybenchmark  -lboost_regex -liberty