include($ENV{BUILDTLS}/vcpkg/scripts/buildsystems/vcpkg.cmake)

#
# Platform type (WINDOWS, WINDOWSXP, BLUESCREEN, LINUX and etc.)
#
set(PLATFORM_TYPE WINDOWS)

#
# Cross compiling CMake-identifiers
#
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 1)
set(CMAKE_SYSTEM_PROCESSOR "x86")

#
# Variables
#
set(CMAKE_GENERATOR_PLATFORM Win32)