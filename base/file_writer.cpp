#include <fstream>
#include <memory>
#include <string>

int main(int argc, char const *argv[]) {
    std::string line = R"(
hello, 
this is a test.

)";

    std::shared_ptr<std::fstream> fs = std::make_shared<std::fstream>();
    fs->open("./out.txt", std::fstream::out);
    *fs << line;
    fs->flush();
    fs->close();
    fs.reset();
    return 0;
}