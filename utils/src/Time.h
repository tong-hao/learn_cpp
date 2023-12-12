#include <sys/time.h>

inline double current_milliseconds(void) {
	struct timeval tv;
	gettimeofday(&tv, nullptr);
	return tv.tv_sec * 1000UL + tv.tv_usec / 1000UL;
}
