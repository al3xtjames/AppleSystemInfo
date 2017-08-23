#include <stdio.h>

#include <AppleSystemInfo/AppleSystemInfo.h>

// Platform features
enum
{
    // /System/Library/SystemProfiler/SPMemoryReporter.spreporter
    // Uses ASI_IsPlatformFeatureEnabled to check
    platform_soldered_system_memory = 0x02,
    // /System/Library/PrivateFrameworks/PhotoLibraryPrivate.framework/Frameworks/PAImaging.framework
    // Uses bitwise AND to check
    platform_headless_gpu_present   = 0x04,
    // /System/Library/Extensions/AppleACPIPlatform.kext/Contents/PlugIns/AppleACPIEC.kext
    // Uses bitwise AND to check
    platform_host_pm_supported      = 0x08,
    // /System/Library/CoreServices/PowerChime.app
    // Uses ASI_IsPlatformFeatureEnabled to check
    platform_power_chime_supported  = 0x10
};

int main(int argc, const char *argv[])
{
    char platform_feature_str[14];

#ifdef TEST_FEATURES
    int platform_feature_prop = 0;
    if (argc != 2 || sscanf(argv[1], "%x", &platform_feature_prop) != 1)
    {
        printf("Usage: %s <platform feature value>\n", argv[0]);
        return 1;
    }
#else
    int platform_feature_prop = GetIOPlatformFeature();
#endif

    snprintf(platform_feature_str, 14, "<%02X 00 00 00>", platform_feature_prop);
    printf("platform-feature = %s\n", platform_feature_str);

    bool host_pm = platform_feature_prop & platform_host_pm_supported;
    bool headless_gpu = platform_feature_prop & platform_headless_gpu_present;

#ifdef TEST_FEATURES
    bool soldered_ram = ASI_IsPlatformFeatureEnabled(platform_feature_prop,
                                                     platform_soldered_system_memory);
    bool power_chime = ASI_IsPlatformFeatureEnabled(platform_feature_prop,
                                                    platform_power_chime_supported);
#else
    bool soldered_ram = ASI_IsPlatformFeatureEnabled(platform_soldered_system_memory);
    bool power_chime = ASI_IsPlatformFeatureEnabled(platform_power_chime_supported);
#endif

    printf("Supported platform features:\n");
    printf(" - Soldered RAM\t%s\n", soldered_ram ? "true" : "false");
    printf(" - Headless GPU\t%s\n", headless_gpu ? "true" : "false");
    printf(" - Host PM\t%s\n", host_pm ? "true" : "false");
    printf(" - Power Chime\t%s\n", power_chime ? "true" : "false");

    return 0;
}
