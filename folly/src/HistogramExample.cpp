#include <folly/stats/Histogram.h>
#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
	// 0-100, 每个bucket10个
	folly::Histogram<int64_t> latencies(10, 0, 100);

	for (int i = 1; i < 100; i++) {
		latencies.addValue(i);
	}
	latencies.addValue(1);
	latencies.addValue(2);

	auto numBuckets = latencies.getNumBuckets();
	std::cout << "numBuckets = " << numBuckets << std::endl;
	std::cout << "Below min: " << latencies.getBucketByIndex(0).count << "\n";
	for (unsigned int n = 0; n < numBuckets; n++) {
		std::cout << latencies.getBucketMin(n) << "-"
		          << latencies.getBucketMax(n) << ": "
		          << latencies.getBucketByIndex(n).count << "\n";
	}
	std::cout << "Above max: "
	          << latencies.getBucketByIndex(numBuckets - 1).count << "\n";

	int64_t p50 = latencies.getPercentileEstimate(0.5);
	int64_t p95 = latencies.getPercentileEstimate(0.95);
	int64_t p99 = latencies.getPercentileEstimate(0.99);

	std::cout << "p50 = " << p50 << std::endl;
	std::cout << "p95 = " << p95 << std::endl;
	std::cout << "p99 = " << p99 << std::endl;

	return 0;
}

// link:-lfolly -lglog -lgflags