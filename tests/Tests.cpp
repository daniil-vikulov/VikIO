#include "Tests.h"
#include "../VikIO.h"

#include <cstdio>
#include <iostream>
#include <vector>
#include <chrono>

void redirect() {
    freopen("/mnt/c/Users/dv/CLionProjects/VikIO/tests/input.txt", "r", stdin);
    freopen("/mnt/c/Users/dv/CLionProjects/VikIO/tests/output.txt", "w", stdout);
}

void restore() {
    freopen("/dev/tty", "r", stdin);
    freopen("/dev/tty", "w", stdout);
}


void Tester::test() {
    redirect();

    int num1, num2;
    std::string s;
    std::vector<int> array(3);

    read(num1);
    read(s);
    read(num2);
    read(array);

    print(num1);
    print(s);
    print(num2);
    print(array);

    restore();
}

void Tester::memoryTemp(size_t objectSize) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < 1000000; ++i) {
        new char[objectSize];
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Time taken for " << 1000000 << " allocations of "
              << objectSize << " bytes: " << duration.count() << " microseconds." << std::endl;
}

void Tester::memory() {
    for (int block_size = 2; block_size <= 8; block_size *= 2) {
        memoryTemp(block_size);
    }
}
