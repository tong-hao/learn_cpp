#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

int MAX_ID = 800 * 10000;

int main() {
	srand(time(NULL));  // 设置随机数种子

	ofstream f_v("v-800w.csv");
	ofstream f_e("e-800w.csv");

	for (int i = 0; i <= MAX_ID; i++) {
		string vid = "v_" + std::to_string(i);

		f_v << vid << "," << i << "," << (i + 1) << "," << (i + 2) << "\n";

		if ((i + 1) % 10000 == 0) {
			f_v.flush();
		}
	}

	for (int i = 0; i < 2 * MAX_ID; i++) {
		int num1 = rand() % MAX_ID + 1;
		int num2 = rand() % MAX_ID + 1;
		string src = "v_" + std::to_string(num1);
		string dst = "v_" + std::to_string(num2);

		f_e << src << "," << dst << "," << num1 << "," << num2 << ","
		    << (num1 + num2) << "\n";

		if ((i + 1) % 10000 == 0) {
			f_e.flush();
		}
	}

	f_v.close();  // 关闭文件
	return 0;
}
