#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char const *argv[]) {
	if (argc != 3) {
		std::cout << "Please input srt file path." << std::endl;
		return 1;
	}
	std::regex e_title("^.*口读生词$");
	std::regex e_num("^[0-9]*\\. ");
	std::regex e_def("^[0-9]*\\. (.*)(（.*）)$");

	std::string input = argv[1];
	std::string output = argv[2];
	std::cout << "input:" << input << std::endl;
	std::cout << "output:" << output << std::endl;

	std::fstream reader;
	std::fstream writer;
	reader.open(input, std::fstream::in);
	writer.open(output, std::fstream::out | std::fstream::trunc);

	std::string line;
	while (std::getline(reader, line)) {
		if (line.empty()) {
			writer << "\n";
			continue;
		}

		std::smatch m;
		if (std::regex_search(line, e_title)) {
			writer << "\n# " << line << "\n";
		} else if (std::regex_search(line, m, e_def) && m.size() == 3) {
			for (int i = 1; i < 3; i++) {
				writer << "\t" << m[i] << "\n";
			}
		} else if (std::regex_search(line, m, e_num)) {
			writer << "\t" << m.suffix().str() << "\n";
		} else {
			writer << "\t" << line << "\n";
		}

		writer.flush();
	}

	//
	reader.close();
	writer.close();

	return 0;
}