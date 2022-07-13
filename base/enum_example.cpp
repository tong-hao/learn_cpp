#include <iostream>

enum Opt1 { Add, Del, Update };

enum class Opt2 : int16_t { Add = 5, Del = 6, Update = 7 };

int main(int argc, char const *argv[]) {
    {
        int i = Opt1::Add;
        std::cout << i << std::endl;

        Opt1 opt = Opt1(2);
        std::cout << opt << ", " << (opt == Opt1::Update) << std::endl;
    }

    // opt2
    {
        // convert to int
        int16_t i = static_cast<int16_t>(Opt2::Add);
        std::cout << i << std::endl;

        Opt2 opt = static_cast<Opt2>(7);
        std::cout << static_cast<int16_t>(opt) << ", " << (opt == Opt2::Update)
                  << std::endl;
        // std::cout << opt << sizeof(Opt2) << std::endl;
    }

    return 0;
}