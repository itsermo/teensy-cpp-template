@echo off
pushd %~dp0
    rmdir /S /Q CMakeFiles .cmake ..\bin ..\lib
    del /Q CMake*.* cmake*.* *.map Makefile
popd