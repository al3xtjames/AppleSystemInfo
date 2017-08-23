#include <mach/mach.h>
#include <sys/sysctl.h>

#include <AppleSystemInfo/AppleSystemInfo.h>

// Macro for adding RE_ prefix to function names when testing against original
// AppleSystemInfo.framework (to prevent duplicate symbols)
#ifdef TEST
    #define TEST_FUNCTION(x) RE_##x
#else
    #define TEST_FUNCTION(x) x
#endif

int TEST_FUNCTION(GetIOPlatformFeature)(void)
{
    mach_port_t master_port = 0;
    io_registry_entry_t path = 0;
    CFTypeRef platform_feature = NULL;
    const UInt8 *platform_feature_ptr = NULL;

    if (IOMasterPort(0, &master_port) == 0)
    {
        path = IORegistryEntryFromPath(master_port, "IOService:/");
        if (path)
        {
            platform_feature = IORegistryEntryCreateCFProperty(path, CFSTR("platform-feature"), kCFAllocatorDefault, 0);
            IOObjectRelease(path);
        }

        if (master_port)
        {
            mach_port_deallocate(mach_task_self(), master_port);
        }

        path = 0;
        if (platform_feature)
        {
            if (CFGetTypeID(platform_feature) == CFDataGetTypeID())
            {
                platform_feature_ptr = CFDataGetBytePtr(platform_feature);
            }

            CFRelease(platform_feature);
        }
    }

    if (platform_feature_ptr)
    {
        return *platform_feature_ptr;
    }
    else
    {
        return 0;
    }
}

CFStringRef ASI_CopyComputerModelName(bool modelID)
{
    size_t len = 1024;
    char model_name[1024];
    int mib[2];
    CFStringRef cf_model_name;

    mib[0] = CTL_HW;
    mib[1] = HW_MODEL;
    if (sysctl(mib, 2, model_name, &len, NULL, 0))
    {
        cf_model_name = CFStringCreateWithCString(kCFAllocatorDefault,
                                                  "Unknown", kCFStringEncodingASCII);
        return cf_model_name;
    }

    cf_model_name = CFStringCreateWithCString(kCFAllocatorDefault, model_name,
                                              kCFStringEncodingASCII);
    if (!cf_model_name)
    {
        // Localization unimplemented
        return NULL;
    }

    if (modelID)
    {
        return cf_model_name;
    }

    return NULL;
}

#ifdef TEST_FEATURES
bool TEST_FUNCTION(ASI_IsPlatformFeatureEnabled)(int override, int feature)
#else
bool TEST_FUNCTION(ASI_IsPlatformFeatureEnabled)(int feature)
#endif
{
    int v2 = false;
    int v3 = 0;
    bool v4 = false;
    CFStringRef v5 = NULL;
    CFStringRef v6 = NULL;
    bool v7 = false;
    bool v8 = false;
    bool v9 = false;
    bool v10 = false;

    // skipped the platform override part

#ifdef TEST_FEATURES
    v3 = (unsigned int) feature & (unsigned int) override;
#else
    v3 = (unsigned int) feature & (unsigned int) TEST_FUNCTION(GetIOPlatformFeature)();
#endif
    v2 = (v3 == feature);
    v4 = (v3 != (unsigned int) feature);
    if (feature == 2 && v4)
    {
        v5 = ASI_CopyComputerModelName(true);
        v6 = v5;
        if (v5)
        {
            v7 = CFStringHasPrefix(v5, CFSTR("MacBookAir"));
            v8 = CFStringHasPrefix(v6, CFSTR("MacBookPro10"));
            CFRelease(v6);
            v9 = v7 != 0;
            v10 = v8 != 0;
        }
        else
        {
            v9 = false;
            v10 = false;
        }
        if (v9 || v10)
        {
            v2 = true;
        }
    }

    return v2;
}
