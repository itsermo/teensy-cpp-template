#!/bin/bash
{
    pushd "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
        rm -rf CMake*
        rm Makefile
        rm cmake*
    popd
} &> /dev/null