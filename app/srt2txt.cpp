#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		std::cout << "Please input srt file path." << std::endl;
		return 1;
	}
	std::regex e_num("^\\d+$");
	std::regex e_time("^[0-9]{2}:[0-9]{2}:[0-9]{2},[0-9]{1,3}");

	std::string input = argv[1];
	std::string output = argv[2];
	std::cout << "input:" << input << std::endl;
	std::cout << "output:" << output << std::endl;

	std::fstream reader;
	std::fstream writer;
	reader.open(input, std::fstream::in);
	writer.open(output, std::fstream::out | std::fstream::trunc);

	size_t line_len = 0;
	bool lastline_is_text = false;
	std::string line;
	while (std::getline(reader, line)) {
		auto pos = line.rfind("\r");
		if (pos != std::string::npos) {
			line.replace(pos, 1, "");
		}

		if (std::regex_search(line, e_time)) {
			lastline_is_text = false;
			continue;
		}
		if (line.empty() || line == "\r") {
			lastline_is_text = false;
			continue;
		}
		if (std::regex_search(line, e_num)) {
			if (line_len > 100) {
				writer << "\n";
				line_len = 0;
			} else if (line_len > 0) {
				writer << "    ";
			}
			writer << line << ": ";
			lastline_is_text = false;
			continue;
		}

		line_len += line.length();
		if (lastline_is_text) {
			writer << " ";
		}
		writer << line;
		writer.flush();
		lastline_is_text = true;
	}

	//
	reader.close();
	writer.close();

	return 0;
}