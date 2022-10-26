#include <sqlite3.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
	printf("%s\n", sqlite3_libversion());
	return 0;
}
