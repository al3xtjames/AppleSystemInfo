#define MAX_PLATFORM_FEATURE 0x10

#include <stdio.h>

#include <AppleSystemInfo/AppleSystemInfo.h>

#include <test.h>

int test_GetIOPlatformFeature(void)
{
    int failed_tests = 0;

    printf("Testing GetIOPlatformFeature()...\t");
    total_tests++;

    int platform_feature    = GetIOPlatformFeature();
    int re_platform_feature = RE_GetIOPlatformFeature();

    if (platform_feature != re_platform_feature)
    {
        printf("failed (mismatch)\n");
        printf(" - original: %d\n", platform_feature);
        printf(" - reversed: %d\n", re_platform_feature);

        return failed_tests++;
    }

    printf("passed\n");
    return failed_tests;
}

int test_ASI_IsPlatformFeatureEnabled(void)
{
    int failed_tests = 0;

    for (int i = 1; i < (MAX_PLATFORM_FEATURE + 1); i++)
    {
        printf("Testing IsPlatformFeatureEnabled(%d)...\t", i);
        total_tests++;

        bool feature_enabled    = ASI_IsPlatformFeatureEnabled(i);
        bool re_feature_enabled = RE_ASI_IsPlatformFeatureEnabled(i);

        if (feature_enabled != re_feature_enabled)
        {
            printf("failed (mismatch):\n");
            printf(" - original: %s\n", feature_enabled    ? "true" : "false");
            printf(" - reversed: %s\n", re_feature_enabled ? "true" : "false");
            failed_tests++;
        }

        printf("passed\n");
    }

    return failed_tests;
}
