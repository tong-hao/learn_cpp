#include "hello.h"

int gId = 1;

int next_id() {
	return ++gId;
}
