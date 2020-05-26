@echo off
pushd %~dp0
cmake ../ -DCMAKE_TOOLCHAIN_FILE=../submodules/cmake-arm-embedded/toolchain-arm-none-eabi.cmake -DTOOLCHAIN_PREFIX="c:/Program Files (x86)/GNU Tools Arm Embedded/9 2019-q4-major" -G "MinGW Makefiles"
popd