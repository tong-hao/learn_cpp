#include <string.h>
#include <atomic>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>
#include <tuple>
#include <typeinfo>
#include <unordered_map>
#include <vector>

using namespace std::placeholders;
using VID_T = unsigned long long;

const bool hasWeighted = false;
std::string kToken = "\t";
// std::string kToken = "\t|'| "; // twitter data may be contained `'`

template <typename CALLBACK>
void readAndParse(std::fstream& reader, CALLBACK callback) {
	char* token_ptr = nullptr;
	while (reader.good() && !reader.eof()) {
		std::unique_ptr<char[]> line_ptr(new char[1024]);
		reader.getline(line_ptr.get(), 1024);
		if (reader.fail() || '\0' == line_ptr[0] || line_ptr[0] == '#') {
			continue;
		}
		token_ptr = strtok(line_ptr.get(), kToken.c_str());
		auto src = strtoull(token_ptr, nullptr, 10);

		token_ptr = strtok(NULL, kToken.c_str());
		if (token_ptr == nullptr) {  // 防止只有一个顶点id
			std::cout << "bad line:" << line_ptr.get() << std::endl;
			continue;
		}
		auto dst = strtoull(token_ptr, nullptr, 10);

		double weight = 1.0;
		if (hasWeighted) {
			token_ptr = strtok(NULL, kToken.c_str());
			weight = strtod(token_ptr, nullptr);
		}
		callback(src, dst, weight);
	}
}

int main(int argc, char const* argv[]) {
	std::string file_r = argv[1];
	std::string file_w = argv[2];
	std::fstream reader(file_r, std::ios::in);
	std::fstream writer(file_w, std::ios::out | std::ios::trunc);
	std::vector<std::string> buffer;
	std::atomic_long count;

	auto doFlush = [&](std::vector<std::string>& buf) {
		for (auto& line : buf) {
			writer << line << "\n";
		}
		writer.flush();
		buffer.clear();
	};

	auto doSave = [&](VID_T src, VID_T dst, double weight) {
		count++;
		std::string line;
		line.append(std::to_string(src))
		    .append(",")
		    .append(std::to_string(dst));
		if (hasWeighted) {
			line.append(",").append(std::to_string(weight));
		}
		buffer.push_back(line);

		if (count >= 1000) {
			doFlush(buffer);
			std::cout << ".";
			count = 0;
		}
	};

	readAndParse(reader, doSave);
	doFlush(buffer);
	writer.flush();
	std::cout << "\n写入完成:" << file_w;

	writer.close();

	return 0;
}

// link
