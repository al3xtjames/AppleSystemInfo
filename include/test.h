#ifndef ASI_TEST_H_
#define ASI_TEST_H_

// Reverse-engineered function implementations to test
int RE_GetIOPlatformFeature(void);
bool RE_ASI_IsPlatformFeatureEnabled(int feature);

// Tester functions
int test_GetIOPlatformFeature(void);
int test_ASI_IsPlatformFeatureEnabled(void);

// Number of total tests
extern int total_tests;

#endif // ASI_TEST_H_
