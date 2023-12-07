#include <stdio.h> // stdout
#define TEST_IMPL
#include "test.h"

static int f(int a, int b) {
    return a + b;
}

static void testF() {
    test(f(1, 2) == 3);
    assert(f(1, 2) == 2);
    test(f(3, 4) == 5); // This statement is never reached.
}

int main(void) {
    suiteOut = testOut = assertOut = resultsOut = stdout;
    beginTesting();
        runSuite(testF);
    endTesting();
}
