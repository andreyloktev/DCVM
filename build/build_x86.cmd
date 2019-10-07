@echo off


cmake .. -DCMAKE_TOOLCHAIN_FILE="%~dp0/toolchains/windows_x86.cmake"
rem cmake --build .