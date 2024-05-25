#include <cstddef>

struct Tester {
public:
    static void test();

    static void memory();

private:
    static void memoryTemp(size_t objectSize);
};