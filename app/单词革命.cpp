#include <fstream>
#include <iostream>
#include <string>

bool replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

int main() {
	std::string path_in = "/Users/ht/Downloads/1401-1500.txt";
	std::string path_out = path_in + ".md";
	std::ifstream in(path_in, std::ios::in);
	std::ofstream out(path_out);
	if (in) {
		std::string last_line;
		for (std::string line; std::getline(in, line);) {
			if (line.rfind("英", 0) == 0) {
				last_line = "\n### " + last_line;
			}
			out << last_line << "\n";

			replace(line, "然后给⼤家光速秒杀下系列词", "");
			if (line.size() > 0 && line.find("系列") != std::string::npos) {
				replace(line, "今天给⼤家撸下", "");
				line = "\n## " + line;
			}

			last_line = line;
		}
		out << last_line << "\n";
		in.close();
	} else {
		std::cout << "cannot open file" << std::endl;
	}
	std::cout << path_out << std::endl;
	return 0;
}
