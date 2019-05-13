@echo off

cmake .. -DCMAKE_TOOLCHAIN_FILE=%BUILDTLS%\vcpkg\scripts\buildsystems\vcpkg.cmake -A x64 -T host=x64