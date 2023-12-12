#include <array>
#include <iostream>
#include <unordered_map>
#include <vector>

// clang-format off

// HEAP SUMMARY:
// in use at exit: 0 bytes in 0 blocks
// total heap usage: 1,000,002 allocs, 1,000,002 frees, 24,523,288 bytes
// allocated
// 占用：24MB
int main1(int argc, char const* argv[]) {
	std::unordered_map<int, int> m;
	m.reserve(1000000);
	for (int i = 0; i < 1000000; i++) {
		m[i] = 2 * i;
	}
	return 0;
}

// HEAP SUMMARY:
//    in use at exit: 0 bytes in 0 blocks
//  total heap usage: 1 allocs, 1 frees, 72,704 bytes allocated
// 72KB

// --------------------------------------------------------------------------------
//   n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
// --------------------------------------------------------------------------------
//   0              0                0                0             0            0
//   1      3,410,109           72,712           72,704             8            0
//   2      3,577,970           72,712           72,704             8            0
// 99.99% (72,704B) (heap allocation functions) malloc/new/new[], --alloc-fns, etc.
// ->99.99% (72,704B) 0x48E6765: ??? (in /opt/vesoft/toolset/gcc/9.3.0/lib64/libstdc++.so.6.0.28)
//   ->99.99% (72,704B) 0x4011B99: call_init.part.0 (dl-init.c:72)
//     ->99.99% (72,704B) 0x4011CA0: call_init (dl-init.c:30)
//       ->99.99% (72,704B) 0x4011CA0: _dl_init (dl-init.c:119)
//         ->99.99% (72,704B) 0x4001139: ??? (in /usr/lib/x86_64-linux-gnu/ld-2.31.so)
int main2(int argc, char const* argv[]) {
	int32_t m[1000000];  // 4*1000 KB=4M
	return 0;
}

// --------------------------------------------------------------------------------
//   n        time(i)         total(B)   useful-heap(B) extra-heap(B)    stacks(B)
// --------------------------------------------------------------------------------
//   0              0                0                0             0            0
//   1      3,410,109           72,712           72,704             8            0
//   2      3,563,465        4,072,720        4,072,704            16            0
//   3     11,564,738        4,072,720        4,072,704            16            0

// HEAP SUMMARY:
//     in use at exit: 0 bytes in 0 blocks
//   total heap usage: 2 allocs, 2 frees, 4,072,704 bytes allocated
// 4M
int main3(int argc, char const* argv[]) {
	std::vector<int32_t> m;  // 4*1000 KB=4M
	m.resize(1000000);
	return 0;
}

// HEAP SUMMARY:
//     in use at exit: 0 bytes in 0 blocks
//   total heap usage: 2 allocs, 2 frees, 72,744 bytes allocated
int main31(int argc, char const* argv[]) {
	std::vector<int32_t> m;  // 4*10byte=40kb
	m.resize(10);
	return 0;
}

// HEAP SUMMARY:
//    in use at exit: 1,000,000 bytes in 1 blocks
//  total heap usage: 2 allocs, 1 frees, 1,072,704 bytes allocated
//
// 1,000,000 bytes in 1 blocks are definitely lost in loss record 1 of 1
//   at 0x483C77D: malloc (vg_replace_malloc.c:431)
//   by 0x40135D: main (std_map.cpp:47)
//
// LEAK SUMMARY:
//   definitely lost: 1,000,000 bytes in 1 blocks
//   indirectly lost: 0 bytes in 0 blocks
//     possibly lost: 0 bytes in 0 blocks
//   still reachable: 0 bytes in 0 blocks
//        suppressed: 0 bytes in 0 blocks
// 1M
int main4(int argc, char const* argv[]) {
	void* p = malloc(1000000);
	return 0;
}



struct A {
	int i;
	double d;
	std::string s;
};

int main() {
	int max = 1468365182;
	std::vector<int> s;

	return 0;
}

// 分析方法：
// 方法1：
// valgrind --leak-check=full ./main
// 方法2:
// valgrind --tool=massif --stacks=yes --time-unit=B  bin/std_map
// ms_print  massif.out.3823024
//
// massif选项：
// --max-snapshots
//
// ms_print选项：
// --x --y
