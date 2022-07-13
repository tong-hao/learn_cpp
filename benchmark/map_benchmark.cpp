#include <fmt/format.h>
#include <folly/Benchmark.h>
#include <folly/Conv.h>
#include <folly/SharedMutex.h>
#include <folly/container/Foreach.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/executors/IOThreadPoolExecutor.h>
#include <folly/futures/Future.h>
#include <folly/hash/FarmHash.h>
#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include <folly/stop_watch.h>
#include <glog/logging.h>

std::unordered_map<std::pair<int, int>, std::string> map_;

BENCHMARK(map_at, iters) {
	folly::BenchmarkSuspender braces;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		map_.at(std::make_pair(1, i));
	}
}

BENCHMARK(map_find, iters) {
	folly::BenchmarkSuspender braces;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		map_.find(std::make_pair(1, i));
	}
}

BENCHMARK(map_emplace, iters) {
	folly::BenchmarkSuspender braces;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		map_.emplace(std::make_pair(1, i), fmt::format("biz-{}", i));
	}
}

BENCHMARK(vector_push_back, iters) {
	folly::BenchmarkSuspender braces;
	std::vector<std::string> vct;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		vct.push_back(fmt::format("biz-{}", i));
	}
}

BENCHMARK(vector_empty, iters) {
	folly::BenchmarkSuspender braces;
	std::vector<std::string> vct;
	for (size_t i = 0; i < iters; i++) {
		vct.emplace_back(fmt::format("{}", i));
	}

	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		vct.empty();
	}
}

BENCHMARK(vector_size, iters) {
	folly::BenchmarkSuspender braces;
	std::vector<std::string> vct;
	for (size_t i = 0; i < iters; i++) {
		vct.emplace_back(fmt::format("{}", i));
	}
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		vct.size();
	}
}

BENCHMARK(vector_swap_512, iters) {
	FOR_EACH_RANGE(i, 0, iters) {
		folly::BenchmarkSuspender braces;
		std::vector<std::string> vct;
		for (size_t idx = 0; idx < 512; idx++) {
			vct.emplace_back(fmt::format("{}", idx));
		}
		braces.dismiss();

		std::vector<std::string> new_data;
		vct.swap(new_data);
	}
}

BENCHMARK(vector_swap_1024, iters) {
	FOR_EACH_RANGE(i, 0, iters) {
		folly::BenchmarkSuspender braces;
		std::vector<std::string> vct;
		for (size_t idx = 0; idx < 1024; idx++) {
			vct.emplace_back(fmt::format("{}", idx));
		}
		braces.dismiss();

		std::vector<std::string> new_data;
		vct.swap(new_data);
	}
}

BENCHMARK(vector_reserve_1024, iters) {
	folly::BenchmarkSuspender braces;
	std::vector<std::string> vct;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		vct.reserve(1024);
	}
}

BENCHMARK(std_make_pair, iters) {
	folly::BenchmarkSuspender braces;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		std::make_pair(i, i);
	}
}

BENCHMARK(fmt_format, iters) {
	folly::BenchmarkSuspender braces;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		fmt::format("biz-{}", i);
	}
}

BENCHMARK(std_string_append) {
	folly::BenchmarkSuspender braces;
	std::string str;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, 512) {
		str.append("abcdefgh01235689t");
	}
}

BENCHMARK(folly_stop_watch_reset, iters) {
	folly::BenchmarkSuspender braces;
	folly::stop_watch<std::chrono::milliseconds> w;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		w.reset();
	}
}

BENCHMARK(folly_stop_watch_elapsed, iters) {
	folly::BenchmarkSuspender braces;
	folly::stop_watch<std::chrono::milliseconds> w;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		w.elapsed().count();
	}
}

BENCHMARK(vlog, iters) {
	FOR_EACH_RANGE(i, 0, iters) {
		VLOG(3) << fmt::format(
		    "end: IDConvertWorker::DigestInput, used_time={}", i);
	}
}

using PartIDPair = std::pair<int, int>;

template <typename T1, typename T2>
using Map = std::unordered_map<T1, T2>;

template <typename T>
T& getWithLock(folly::SharedMutex& mutex, Map<PartIDPair, T>& map,
               const int db_id, const int part_id) {
	// folly::stop_watch<std::chrono::microseconds> watch;
	auto key = std::make_pair(db_id, part_id);
	auto exist = [](Map<PartIDPair, T>& map, auto& key,
	                folly::SharedMutex& mutex) {
		folly::SharedMutex::ReadHolder l(mutex);
		return map.find(key) != map.end();  // 800w/s
	};
	if (!exist(map, key, mutex)) {
		folly::SharedMutex::WriteHolder l(mutex);
		if (map.find(key) == map.end()) {  // 800w/s
			T v;
			map.emplace(key, v);  // 100w/s
		}
	}
	auto& res = map.at(key);  // 800w/s
	return res;
}

BENCHMARK(get_with_lock, iters) {
	folly::BenchmarkSuspender braces;
	folly::SharedMutex mutex;
	std::unordered_map<PartIDPair, std::unordered_map<std::string, std::string>>
	    map;
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		getWithLock(mutex, map, 1, i);
	}
}

BENCHMARK(cpu_exec1_add, iters) {
	folly::BenchmarkSuspender braces;
	folly::CPUThreadPoolExecutor cpu_exec(1);
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		cpu_exec.add([i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		});
	}
}

BENCHMARK(cpu_exec5_add, iters) {
	folly::BenchmarkSuspender braces;
	folly::CPUThreadPoolExecutor cpu_exec(5);
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		cpu_exec.add([i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		});
	}
}

BENCHMARK(cpu_via_add, iters) {
	folly::BenchmarkSuspender braces;
	folly::CPUThreadPoolExecutor cpu_exec(1);
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		folly::via(&cpu_exec, [i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		});
	}
}

BENCHMARK(io_exec_add, iters) {
	folly::BenchmarkSuspender braces;
	folly::IOThreadPoolExecutor io_exec(1);
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		io_exec.add([i]() {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		});
	}
}

BENCHMARK(io_via_add, iters) {
	folly::BenchmarkSuspender braces;
	folly::IOThreadPoolExecutor io_exec(10);
	braces.dismiss();

	FOR_EACH_RANGE(i, 0, iters) {
		folly::via(&io_exec, [i]() {});
	}
}

int main(int argc, char** argv) {
	FLAGS_logtostderr = 1;
	folly::init(&argc, &argv);

	for (int i = 0; i < 1024; i++) {
		map_.emplace(std::make_pair(1, i), fmt::format("biz-{}", i));
	}

	folly::runBenchmarks();

	return 0;
}
/* clang-format off
============================================================================
map_benchmark.cpp                               relative  time/iter  iters/s
============================================================================
map_at                                                     136.72ns    7.31M
map_find                                                   117.92ns    8.48M  800w/s
map_emplace                                                741.41ns    1.35M  100w/s
vector_push_back                                           484.24ns    2.07M  200w/s
vector_empty                                                24.02ns   41.64M  4000w/s 忽略
vector_size                                                  6.15ns  162.52M  忽略
vector_swap_512                                              4.47us  223.62K  20w/s
vector_swap_1024                                             5.12us  195.33K  
vector_reserve_1024                                         10.66ns   93.78M  忽略
std_make_pair                                                6.83ns  146.32M  忽略
fmt_format                                                 378.53ns    2.64M  200w/s
std_string_append                                            8.70ns  114.98M  忽略
folly_stop_watch_reset                                      15.05ns   66.46M
folly_stop_watch_elapsed                                    32.51ns   30.76M
cpu_exec_add                                                50.74us   19.71K
io_exec_add                                                174.54us    5.73K
via_add                                                    270.84us    3.69K
============================================================================
8000000/s
*/

// link:-lfolly -lfmt -lglog -lgflags -lpthread -ldl -ldouble-conversion
// link:-lfollybenchmark  -lboost_regex -liberty -levent -lboost_context