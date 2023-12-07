// Declaration
#ifndef TEST_H
#define TEST_H

#include <stddef.h> // size_t
#include <stdio.h> // FILE

#define test(expression) testImpl((expression), #expression, __FILE__, __LINE__, __func__)
#define assert(expression) assertImpl((expression), #expression, __FILE__, __LINE__, __func__)
#define runTest(testFunction) runTestImpl((testFunction), #testFunction, __FILE__, __LINE__, __func__)

void beginTesting(void);
void endTesting(void);

size_t testsRun;
size_t testsPassed;

size_t assertionsRun;
size_t assertionsPassed;

size_t testFunctionsRun;
size_t testFunctionsExited;

// These variables need to be set by code that uses this header.
FILE *testOut; // Output for failed test messages.
FILE *assertOut; // Output for failed assertion messages.
FILE *resultsOut; // Output for test results.

#endif // TEST_H


// Implementation
#ifdef TEST_IMPL
#undef TEST_IMPL

#include <stddef.h> // size_t
#include <stdbool.h> // bool
#include <stdlib.h> // exit()
#include <stdio.h> // FILE, fprintf()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // waitpid(), WIFEXITED(), WIFSIGNALED()
#include <unistd.h> // fork()

typedef void (*TestFunction)(void);

__attribute__((unused))
void beginTesting(void) {
    testsRun = 0;
    testsPassed = 0;
    assertionsRun = 0;
    assertionsPassed = 0;
    testFunctionsRun = 0;
    testFunctionsExited = 0;
    if (testOut == NULL) {
        testOut = stdout;
    }
    if (assertOut == NULL) {
        assertOut = stderr;
    }
    if (resultsOut == NULL) {
        resultsOut = stdout;
    }
}

__attribute__((unused))
void endTesting(void) {
    fprintf(resultsOut, "%zu tests run, ", testsRun);
    fprintf(resultsOut, "%zu tests passed, ", testsPassed);
    fprintf(resultsOut, "%zu tests failed\n", testsRun - testsPassed);

    fprintf(resultsOut, "%zu assertions run, ", assertionsRun);
    fprintf(resultsOut, "%zu assertions passed, ", assertionsPassed);
    fprintf(resultsOut, "%zu assertions failed\n", assertionsRun - assertionsPassed);
}

__attribute__((unused))
void runTestImpl(TestFunction testFunction, const char *testName, const char *file, int line, const char *function) {
    pid_t pid = fork();
    if (pid == 0) {
        // We are in the child process, run the test and exit.
        testFunction();
        exit(EXIT_SUCCESS);
    }
    
    // We are in the parent process, wait for the child to finish and print an error.
    int childStatus = 0;
    waitpid(pid, &childStatus, 0);
    if ((WIFEXITED(childStatus) && childStatus != EXIT_SUCCESS) || WIFSIGNALED(childStatus)) {
        fprintf(testOut, "%s:%d:%s:\nTest function '%s' terminated abnormally with status %d.\n\n", file, line, function, testName, childStatus);
    }
    return;
}

__attribute__((unused))
static void testImpl(bool condition, const char *expression, const char *file, int line, const char *function) {
    ++testsRun;
    if (condition) {
        ++testsPassed;
    } else {
        fprintf(testOut, "%s:%d:%s\nFailed test '%s'\n\n", file, line, function, expression);
    }
}

__attribute__((unused))
static void assertImpl(bool condition, const char *expression, const char *file, int line, const char *function) {
    ++assertionsRun;
    if (condition) {
        ++assertionsPassed;
    } else {
        fprintf(assertOut, "%s:%d:%s\nFailed assertion '%s'\n\n", file, line, function, expression);
    }
    exit(EXIT_FAILURE);
}

#endif // TEST_IMPL
