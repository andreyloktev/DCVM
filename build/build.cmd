@echo off

del /Q /S .\*
rmdir /Q *
cmake .. -D-DCMAKE_TOOLCHAIN_FILE=%BUILDTLS%\vcpkg\scripts\buildsystems\vcpkg.cmake