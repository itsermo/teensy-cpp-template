#!/bin/bash
{
    pushd "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
    cmake ../ -DCMAKE_TOOLCHAIN_FILE=../submodules/cmake-arm-embedded/toolchain-arm-none-eabi.cmake
    popd
} &> /dev/null