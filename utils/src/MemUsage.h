#include <cstdio>
#include <cstring>
#include <iostream>

struct MemStatus {
	size_t vmPeak_;  // KBytes
	size_t vmSize_;  // KBytes
	size_t vmHwm_;   // KBytes
	size_t vmRss_;   // KBytes
};

inline MemStatus memUsage() {
	MemStatus status;
	char buffer[1024] = "";

	FILE *f = fopen("/proc/self/status", "r");
	while (fscanf(f, " %1023s", buffer) == 1) {
		if (strcmp(buffer, "VmRSS:") == 0) {
			fscanf(f, " %lu", &status.vmRss_);
		}
		if (strcmp(buffer, "VmHWM:") == 0) {
			fscanf(f, " %lu", &status.vmHwm_);
		}
		if (strcmp(buffer, "VmSize:") == 0) {
			fscanf(f, " %lu", &status.vmSize_);
		}
		if (strcmp(buffer, "VmPeak:") == 0) {
			fscanf(f, " %lu", &status.vmPeak_);
		}
	}
	fclose(f);

	return status;
}
