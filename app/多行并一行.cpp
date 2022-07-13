
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

const bool hasWeighted = true;
std::string kToken = "\t";

template <typename CALLBACK>
void readAndParse(std::fstream& reader, CALLBACK callback) {
	char* save_ptr = nullptr;
	char* token_ptr = nullptr;
	std::string last_line = "";
	while (reader.good() && !reader.eof()) {
		std::unique_ptr<char[]> line_ptr(new char[1024]);
		reader.getline(line_ptr.get(), 1024);
		if (reader.fail() || '\0' == line_ptr[0] || line_ptr[0] == '#') {
			continue;
		}
		bool is_word = ((line_ptr[0]) >= 'a' && (line_ptr[0]) <= 'z') &&
		               ((line_ptr[1]) >= 'a' && (line_ptr[1]) <= 'z');
		if (is_word) {
			callback(last_line.c_str());
			last_line = "";
			last_line.append(line_ptr.get());
		} else {
			last_line.append(line_ptr.get());
		}
	}
}

int main(int argc, char const* argv[]) {
	std::string file_r = "/Users/ht/Downloads/单词.txt";  // argv[1];
	std::string file_w = "/Users/ht/Downloads/单词2.txt";
	// argv[2];
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

	auto doSave = [&](const char* line) {
		count++;
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

// link:-std=c++11
