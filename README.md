# AppleSystemInfo

### Source
An incomplete reverse-engineered implementation of AppleSystemInfo.framework
is available in the `src` directory, along with an incomplete header in the
`include/AppleSystemInfo` directory. The reverse-engineered implementation can
be tested against the system implementation by running `make test_impl`:

    $ make test_impl
    clang -o obj/asi_test.o -c src/AppleSystemInfo.c -O2 -std=c99 -g -O0 -D TEST -I include
    clang -o obj/test_platformfeature.o -c test/test_platformfeature.c -O2 -std=c99 -g -O0 -I include
    clang -o out/test_impl obj/asi_test.o obj/test_platformfeature.o test/test.c -O2 -std=c99 -g -O0 -F /System/Library/PrivateFrameworks -framework AppleSystemInfo -framework CoreFoundation -framework IOKit -I include
    Testing reversed-engineered implementations:
    Testing GetIOPlatformFeature()...       passed
    Testing IsPlatformFeatureEnabled(1)...  passed
    Testing IsPlatformFeatureEnabled(2)...  passed
    Testing IsPlatformFeatureEnabled(3)...  passed
    Testing IsPlatformFeatureEnabled(4)...  passed
    Testing IsPlatformFeatureEnabled(5)...  passed
    Testing IsPlatformFeatureEnabled(6)...  passed
    Testing IsPlatformFeatureEnabled(7)...  passed
    Testing IsPlatformFeatureEnabled(8)...  passed
    Testing IsPlatformFeatureEnabled(9)...  passed
    Testing IsPlatformFeatureEnabled(10)... passed
    Testing IsPlatformFeatureEnabled(11)... passed
    Testing IsPlatformFeatureEnabled(12)... passed
    Testing IsPlatformFeatureEnabled(13)... passed
    Testing IsPlatformFeatureEnabled(14)... passed
    Testing IsPlatformFeatureEnabled(15)... passed
    Testing IsPlatformFeatureEnabled(16)... passed
    17 test(s) completed successfully

### Tools
`dump_features` checks the supported platform features on the current
system, using the system implementation of AppleSystemInfo.framework.

    $ make
    $ out/dump_features
    platform-feature = <1A 00 00 00>
    Supported platform features:
     - Soldered RAM true
     - Headless GPU false
     - Host PM      true
     - Power Chime  true

`test_features` allows you to check the supported platform features for an input
`platform-feature` value, using the reverse-engineered implementation of
AppleSystemInfo.framework.

    $ make
    $ out/test_features 0x18
    platform-feature = <18 00 00 00>
    Supported platform features:
     - Soldered RAM false
     - Headless GPU false
     - Host PM      true
     - Power Chime  true
