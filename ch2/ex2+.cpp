#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

int main() {
    int *p = new int;
    assert(p != nullptr);
    std::cout << "address pointed to by p: " << p << '\n';
    *p = 0;
    while (1) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        *p += 1;
        std::cout << "p: " << *p << '\n';
    }
    return 0;
}