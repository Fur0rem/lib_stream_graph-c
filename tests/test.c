#include "test.h"
#include "../src/utils.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

bool test(const char* suite_name, ...) {
    printf(" -- Running test suite : " TEXT_BOLD"%s"TEXT_RESET " --\n", suite_name);
    // For each test in the suite
    va_list args;
    va_start(args, suite_name);
    Test* test;
    bool success = true;
    while ((test = va_arg(args, Test*))) {
        // Run the test
        printf("Testing " TEXT_BOLD "%s\n" TEXT_RESET, test->name);
        bool result = test->fn();
        printf("%s : ", test->name);
        if (!result) {
            printf(TEXT_BOLD TEXT_RED"FAIL\n"TEXT_RESET);
            success = false;
        }
        else {
            printf(TEXT_BOLD TEXT_GREEN"SUCCESS\n"TEXT_RESET);
        }
        
    }
    va_end(args);

    printf("-- " TEXT_BOLD "%s : ", suite_name);
    if (success) {
        printf(TEXT_GREEN "SUCCESS");
    }
    else {
        printf(TEXT_RED "FAIL");
    }
    printf(TEXT_RESET " --\n");
    return success;
}

bool EXPECT_ALL(int expr, ...) {
    va_list args;
    va_start(args, expr);
    int success = expr;
    int arg;
    while ((arg = va_arg(args, int))) {
        success = success && arg;
    }
    va_end(args);
    return success;
}