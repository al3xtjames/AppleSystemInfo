#ifndef ASI_APPLE_SYSTEM_INFO_H_
#define ASI_APPLE_SYSTEM_INFO_H_

#include <mach/mach.h>
#include <stdbool.h>

#include <IOKit/IOKitLib.h>

int GetIOPlatformFeature(void);
CFStringRef ASI_CopyComputerModelName(bool modelID);
#ifdef TEST_FEATURES
bool ASI_IsPlatformFeatureEnabled(int override, int feature);
#else
bool ASI_IsPlatformFeatureEnabled(int feature);
#endif

#endif // ASI_APPLE_SYSTEM_INFO_H_
