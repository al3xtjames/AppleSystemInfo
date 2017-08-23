#include <stdbool.h>
#include <stdio.h>

#include <AppleSystemInfo/AppleSystemInfo.h>

#include <test.h>

int total_tests = 0;

int main()
{
    int passed_tests = 0;
    int failed_tests = 0;

    printf("Testing reversed-engineered implementations:\n");

    failed_tests += test_GetIOPlatformFeature();
    failed_tests += test_ASI_IsPlatformFeatureEnabled();

    passed_tests = total_tests - failed_tests;

    if (failed_tests)
    {
        printf("%d test(s) failed, %d tests completed successfully\n",
               failed_tests, passed_tests);

        return 1;
    }

    printf("%d test(s) completed successfully\n", passed_tests);
    return 0;
}
