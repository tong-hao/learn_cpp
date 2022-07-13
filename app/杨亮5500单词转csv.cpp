
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
	while (reader.good() && !reader.eof()) {
		std::unique_ptr<char[]> line_ptr(new char[1024]);
		reader.getline(line_ptr.get(), 1024);
		if (reader.fail() || '\0' == line_ptr[0] || line_ptr[0] == '#') {
			continue;
		}
		char* begin = line_ptr.get();
		while (*begin == ' ' || (*begin >= '0' && *begin <= '9')) {
			begin++;
		}
		if (*begin == '.' && *(begin + 1) == ' ') {
			begin++;
		} else if (line_ptr[0] == 'E' && line_ptr[4] == '|') {
			callback(line_ptr.get(), nullptr, nullptr);
			std::cout << "title:" << begin << std::endl;
			continue;
		}
		char* ptr_word = strtok(begin, "[");
		char* ptr_tone = strtok(nullptr, "]");
		char* ptr_desc = strtok(nullptr, "");

		if (!ptr_word || !ptr_tone || !ptr_desc) {
			std::cout << "bad line:" << begin << std::endl;
			continue;
		}
		callback(ptr_word, ptr_tone, ptr_desc);
	}
}

int main(int argc, char const* argv[]) {
	std::string file_r =
	    "/Users/ht/Documents/99-个人/杨亮5500单词/E41-E50.txt";  // argv[1];
	std::string file_w = "/Users/ht/Documents/99-个人/杨亮5500单词/4.csv";
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

	auto doReplace = [&](char* c) {
		if (c == nullptr) {
			return;
		}
		char* p = c;
		while (*p != '\0') {
			if (*p == ',')
				*p = ';';
			p++;
		}
	};

	auto doSave = [&](char* word, char* tone, char* desc) {
		doReplace(tone);
		doReplace(desc);
		count++;
		std::string line;
		if (tone == nullptr) {
			line.append(word);
		} else {
			line.append(word).append(",[").append(tone).append("],").append(
			    desc);
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

// link:-std=c++11
