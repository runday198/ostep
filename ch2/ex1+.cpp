#include <iostream>
#include <chrono>
#include <thread>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: ex1+ <string>\n";
        exit(1);
    }
    char *str = argv[1];
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto a = std::this_thread::get_id();
        std::cout << str << ' ' << a << "\n";
    }
    return 0;
}