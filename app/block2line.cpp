#include <exception>
#include <iostream>
#include <sstream>
#include <string>

// std::stringstream stream("123", std::ios_base::in | std::ios_base::app);
std::stringstream stream;

int block_idx = 1;
bool NextBlock(std::string& block) {
	if (block_idx > 3)
		return false;

	block.append("hello\n").append(std::to_string(block_idx));
	block_idx++;

	return true;
}

bool NextLine(std::string& line, int try_time = 0) {
	// line.resize(10);

	if (try_time > 3) {
		throw std::exception();
	}
	// read
	// stream.getline(&line[0], line.size(), '\n');
	std::getline(stream, line);
	std::cout << "state=" << stream.rdstate() << std::endl;
	if (stream.rdstate() == std::ios_base::goodbit) {
		// line.resize(stream.gcount() - 1);
		return true;
	} else if (stream.rdstate() == std::ios_base::eofbit) {
		// line.resize(stream.gcount());

		std::string block(line);
		if (NextBlock(block)) {
			std::cout << "block={" << block << "}\n\n";
			// stream << line;
			stream.str(block);
			stream.clear();  // clear rdstate
			return NextLine(line, try_time + 1);
		} else {
			return true;
		}
	} else {
		return false;
	}
}

int main() {
	std::cout << std::ios_base::badbit << std::endl;
	std::string line;
	while (NextLine(line)) {
		std::cout << "line:" << line << std::endl;
	}
}