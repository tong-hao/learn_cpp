#include <iostream>
#include <memory>

struct Vertex {
    int32_t id;
};

void change(Vertex &v) { v.id = 100; }

int main(int argc, char const *argv[]) {
    auto doHandler = [&]() {
        std::unique_ptr<Vertex> v = std::make_unique<Vertex>();
        change(*v);
        std::cout << &(*v) << std::endl;
        return v;
    };

    auto res = doHandler();
    std::cout << &(*res) << std::endl;
    std::cout << "vertex id:" << res->id << std::endl;

    return 0;
}
