#define TEST_IMPL
#include "test.h"

static int f(int a, int b) {
    return a + b;
}

static void testF() {
    assert(f(1, 2) == 2);
    test(f(1, 2) == 3);
}

int main(void) {
    beginTesting();
        runTest(testF);
    endTesting();
}
