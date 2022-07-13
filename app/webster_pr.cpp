#include <algorithm>
#include <cctype>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <sstream>
#include <string>

std::smatch m;
std::regex e_word("[a-z]+");
std::regex e_pr("(?:<span class=\"pr\">)([^</>]*)(?:</span>)");
std::regex e_dt(
    "(?:<span class=\"dtText\"><strong "
    "class=\"mw_t_bc\">: </strong>)([^<]*)(?:<)");

bool exec(const std::string& cmd, std::stringstream& stream) {
	FILE* f = popen(cmd.c_str(), "r");
	const int max_buf = 1024;
	char buffer[max_buf];
	size_t len = 0;
	do {
		len = fread(buffer, 1, max_buf, f);
		for (size_t i = 0; i < len; i++) {
			stream << buffer[i];
		}
	} while (len == max_buf);

	if (ferror(f)) {
		fclose(f);
		return false;
	}
	pclose(f);

	return true;
}

std::string get_pr(const std::string& word) {
	std::stringstream stream;
	auto url = "curl -s https://www.merriam-webster.com/dictionary/" + word;
	if (exec(url, stream)) {
		auto s = stream.str();

		std::set<std::string> pr_set;
		while (std::regex_search(s, m, e_pr)) {
			pr_set.insert(m[1]);
			s = m.suffix().str();
		}

		// translation
		// pr.append("\n\n");
		// while (std::regex_search(s, m, e_dt)) {
		// 	pr.append(m[1]).append("\n");
		// 	s = m.suffix().str();
		// }

		std::string pr;
		for (auto iter = pr_set.begin(); iter != pr_set.end(); iter++) {
			pr.append(*iter).append(" ");
		}
		return pr;
	}

	return "";
}

void to_lower(std::string& str) {
	std::transform(str.begin(), str.end(), str.begin(), tolower);
}
std::string get_prs(const std::string& file) {
	std::string buf;
	std::fstream stream(file);
	std::string line;
	std::set<std::string> word_set;
	while (std::getline(stream, line, ' ')) {
		to_lower(line);
		while (std::regex_search(line, m, e_word)) {
			std::string w = m[0];
			word_set.insert(w);
			line = m.suffix().str();
		}
	}
	for (auto iter = word_set.begin(); iter != word_set.end(); iter++) {
		buf.append(*iter);
		buf.append(" : ");
		buf.append(get_pr(*iter));
		buf.append("\n");
	}

	stream.close();
	return buf;
}

int main(int argc, char const* argv[]) {
	auto prs = get_prs(argv[1]);

	std::cout << prs << std::endl;

	return 0;
}