#include <fstream>
#include <iostream>
#include <assert.h>

int main(int argc, char const *argv[])
{
	// read
	std::ifstream reader;
	reader.open("read.txt");
	std::string line;
	while(getline(reader, line)) {
		std::cout << line << std::endl;
	}
	reader.close();
	
	// write
	{
		std::ofstream writer;
		writer.open("write.txt");
		assert(writer);

		for(int i = 0; i < 10; i++) {
			writer << i << "\n";
			writer.flush();
		}
		writer.close();

	}

	return 0;
}