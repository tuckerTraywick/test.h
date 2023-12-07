#include <stdio.h> // stdout
#define TEST_IMPL
#include "test.h"

static int f(int a, int b) {
    return a + b;
}

static void testF() {
    test(f(1, 2) == 3);
    test(f(1, 2) == 4);
    assert(f(1, 2) == 2);
}

int main(void) {
    suiteOut = testOut = assertOut = resultsOut = stdout;
    beginTesting();
        runSuite(testF);
    endTesting();
}
