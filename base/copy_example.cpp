#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

class Vertex {
public:
    Vertex() = default;
    ~Vertex() = default;
    Vertex(const Vertex& v) {
        this->id_ = v.id_;
        this->props_ = v.props_;
    }
    Vertex& operator=(const Vertex& v) {
        this->id_ = v.id_;
        this->props_ = v.props_;
        return *this;
    };

public:
    int id_;
    std::map<std::string, std::string> props_;
};

int main(int argc, char const* argv[]) {
    std::vector<Vertex> vct;
    for (int i = 1; i < 10; i++) {
        std::cout << vct.size() << std::endl;
        Vertex v;
        v.id_ = i;
        v.props_.emplace("a", "1");
        v.props_.emplace("b", "2");
        v.props_.emplace("c", "3");
        vct.emplace_back(v);
    }

    std::cout << "begin: copy" << std::endl;
    std::vector<Vertex> vct2(vct.size());
    std::copy(vct.begin(), vct.end(), vct2.begin());
    std::cout << "end: copy" << std::endl;

    for (Vertex v : vct2) {
        std::cout << v.props_.size() << std::endl;
    }

    return 0;
}
