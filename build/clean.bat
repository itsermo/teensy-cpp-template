@echo off
pushd %~dp0
    rmdir /S /Q CMakeFiles .cmake ..\bin ..\lib 2>NUL
    del /Q CMake*.* cmake*.* *.map Makefile 2>NUL
popd