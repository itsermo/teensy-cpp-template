#!/bin/bash
{
    pushd "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
        find . -maxdepth 1 -type d -exec rm -rf {} +
        find . -type f ! \( -name "generate.sh" -o -name "clean.sh" -o -name "build.sh" -o -name "flash.sh" -name "generate.bat" -o -name "clean.bat" -o -name "build.bat" -o -name "flash.bat" \)  -exec rm -f {} +
        rm -fr ../bin
        rm -fr ../lib
    popd
} &> /dev/null