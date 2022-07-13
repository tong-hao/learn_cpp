#include <fmt/format.h>
#include <folly/Benchmark.h>
#include <folly/Conv.h>
#include <folly/container/Foreach.h>
#include <folly/hash/FarmHash.h>
#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include <glog/logging.h>

std::unordered_map<int, size_t> std_hash_part_num;
std::unordered_map<int, size_t> folly_hash_part_num;
size_t idx = 0;

BENCHMARK(std_hash, iters) {
	folly::BenchmarkSuspender braces;
	std::hash<std::string> hasher;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		auto part_id = hasher(fmt::format("biz-{}", ++idx)) % 512;
		++std_hash_part_num[part_id];
	}
}

BENCHMARK(folly_hash, iters) {
	folly::BenchmarkSuspender braces;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		auto part_id =
		    folly::hash::farmhash::Fingerprint32(fmt::format("biz-{}", ++idx)) %
		    512;
		++folly_hash_part_num[part_id];
	}
}

int main(int argc, char** argv) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);

	folly::runBenchmarks();

	auto print = [](auto& map) {
		for (auto& item : map) {
			LOG(INFO) << fmt::format("part_id:{}\tparts:{}", item.first,
			                         item.second);
		}
	};
	print(std_hash_part_num);
	LOG(INFO) << "\n\n";
	print(folly_hash_part_num);

	return 0;
}
/* clang-format off
============================================================================
hash_benchmark.cpp                              relative  time/iter  iters/s
============================================================================
std_hash                                                   385.64ns    2.59M   200w/s
folly_hash                                                 437.55ns    2.29M
============================================================================
*/

// link:-lfolly -lfmt -lglog -lgflags -lpthread -ldl -ldouble-conversion
// link:-lfollybenchmark  -lboost_regex -liberty