// Declaration
#ifndef TEST_H
#define TEST_H

#include <stddef.h> // size_t
#include <stdio.h> // FILE

// Runs `testFunction` in a child process and reports if it crashes or exits abnormally.
#define runSuite(testFunction) runSuiteImpl((testFunction), #testFunction, __FILE__, __LINE__, __func__)
#define test(expression) testImpl((expression), #expression, __FILE__, __LINE__, __func__)
#define assert(expression) assertImpl((expression), #expression, __FILE__, __LINE__, __func__)

void beginTesting(void);
void endTesting(void);

size_t *suitesRun;
size_t *suitesPassed;

size_t *testsRun;
size_t *testsPassed;

size_t *assertionsRun;
size_t *assertionsPassed;


// These variables need to be set by code that uses this header. Leave unset for no output.
FILE *suiteOut;
FILE *testOut;
FILE *assertOut;
FILE *resultsOut;

#endif // TEST_H


// Implementation
#ifdef TEST_IMPL
#undef TEST_IMPL

#include <stddef.h> // size_t
#include <stdbool.h> // bool
#include <stdlib.h> // exit()
#include <stdio.h> // FILE, fprintf()
#include <unistd.h> // fork()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // waitpid(), WIFEXITED(), WIFSIGNALED()
#include <sys/mman.h> // mmap(), munmap()

#define TEST_COUNTERS_LENGTH 6

typedef void (*TestFunction)(void);

// Points to the shared memory that holds all of the counters.
size_t *testCounters;

__attribute__((unused))
void beginTesting(void) {
    // mmap the counters so they can be shared with the child process in `runTestImpl()`.
    testCounters = mmap(NULL, TEST_COUNTERS_LENGTH*(sizeof *testCounters), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    testsRun = testCounters;
    testsPassed = testCounters + 1;
    assertionsRun = testCounters + 2;
    assertionsPassed = testCounters + 3;
    suitesRun = testCounters + 4;
    suitesPassed = testCounters + 5;
}

__attribute__((unused))
void endTesting(void) {
    if (resultsOut != NULL) {
        fprintf(resultsOut, "%zu suites run, ", *suitesRun);
        if (*suitesPassed == *suitesRun) {
            fprintf(resultsOut, "all suites passed\n");
        } else {
            fprintf(resultsOut, "%zu suites passed, ", *suitesPassed);
            fprintf(resultsOut, "%zu suites failed\n", *suitesRun - *suitesPassed);
        }

        fprintf(resultsOut, "%zu tests run, ", *testsRun);
        if (*testsRun == *testsPassed) {
            fprintf(resultsOut, "all tests passed.\n");
        } else {
            fprintf(resultsOut, "%zu tests passed, ", *testsPassed);
            fprintf(resultsOut, "%zu tests failed\n", *testsRun - *testsPassed);
        }

        fprintf(resultsOut, "%zu assertions run, ", *assertionsRun);
        if (*assertionsRun == *assertionsPassed) {
            fprintf(resultsOut, "all assertisons passed\n");
        } else {
            fprintf(resultsOut, "%zu assertions passed, ", *assertionsPassed);
            fprintf(resultsOut, "%zu assertions failed\n", *assertionsRun - *assertionsPassed);
        }
    }

    munmap(testCounters, TEST_COUNTERS_LENGTH*(sizeof *testCounters));
}

__attribute__((unused))
void runSuiteImpl(TestFunction testFunction, const char *testName, const char *file, int line, const char *function) {
    pid_t pid = fork();
    if (pid == 0) {
        // We are in the child process, run the test and exit.
        ++*suitesRun;
        size_t previousTestsRun = *testsRun;
        size_t previousTestsPassed = *testsPassed;
        size_t previousAssertionsRun = *assertionsRun;
        size_t previousAssertionsPassed = *assertionsPassed;

        testFunction();
        if (*testsPassed - previousTestsPassed == *testsRun - previousTestsRun
            && *assertionsPassed - previousAssertionsPassed == *assertionsRun - previousAssertionsRun) {
            ++*suitesPassed;
        } else if (suiteOut != NULL) {
            fprintf(suiteOut, "%s:%d:%s:\n    Failed suite '%s'\n\n", file, line, function, testName);
        }
        exit(EXIT_SUCCESS);
    }
    
    // We are in the parent process, wait for the child to finish and print an error.
    int childStatus = 0;
    waitpid(pid, &childStatus, 0);
    if (suiteOut != NULL && (WIFEXITED(childStatus) && childStatus != EXIT_SUCCESS || WIFSIGNALED(childStatus))) {
        fprintf(suiteOut, "%s:%d:%s:\n    Terminated abnormally in suite '%s'\n\n", file, line, function, testName);
    }
    return;
}

__attribute__((unused))
static void testImpl(bool condition, const char *expression, const char *file, int line, const char *function) {
    ++*testsRun;
    if (condition) {
        ++*testsPassed;
    } else if (testOut != NULL) {
        fprintf(testOut, "%s:%d:%s\n    Failed test '%s'\n\n", file, line, function, expression);
    }
}

__attribute__((unused))
static void assertImpl(bool condition, const char *expression, const char *file, int line, const char *function) {
    ++*assertionsRun;
    if (condition) {
        ++*assertionsPassed;
    } else {
        if (assertOut != NULL) {
            fprintf(assertOut, "%s:%d:%s\n    Failed assertion '%s'\n\n", file, line, function, expression);
        }
        exit(EXIT_FAILURE);
    }
}

#undef TEST_COUNTERS_LENGTH

#endif // TEST_IMPL
