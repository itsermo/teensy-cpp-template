#!/bin/bash
pushd "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )" &> /dev/null
    sh generate.sh
    cmake --build . --config Debug --target flash-teensy
popd &> /dev/null