@echo off

cmake .. -DCMAKE_TOOLCHAIN_FILE="%~dp0/toolchains/windows_x64.cmake" -A x64
rem cmake --build .