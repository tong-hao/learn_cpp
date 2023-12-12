#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>

void genGraph(int maxVid, int maxWide, std::function<void(int, int)> callback) {
	for (int vid = 0; vid < maxVid; vid++) {
		int src = vid;
		int curWide = maxWide / 2 + rand() % (maxWide / 2) + 1;
		// std::cout << "curWide:" << curWide << std::endl;
		for (int i = 0; i < curWide; i++) {
			int dst = rand() % maxVid;
			callback(src, dst);
		}
	}
}

int main(int argc, char const *argv[]) {
	srand(time(0));

	std::string outFile = "./graph.txt";
	int maxVid = 10;
	int maxWide = 3;
	if (argc == 4) {
		outFile = argv[1];
		maxVid = std::stoi(argv[2]);
		maxWide = std::stoi(argv[3]);
	}
	std::cout << "outFile=" << outFile << std::endl;
	std::cout << "maxVid=" << maxVid << std::endl;
	std::cout << "maxWide=" << maxWide << std::endl;
	std::cout << "start..." << std::endl;

	std::fstream out;
	out.open(outFile, std::fstream::out | std::fstream::trunc);
	genGraph(maxVid, maxWide, [&](int src, int dst) {
		out << std::to_string(src) << "," << std::to_string(dst) << "\n";
		out.flush();
	});
	out.close();
	return 0;
}
