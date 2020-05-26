#!/bin/bash
pushd "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )"
    sh generate.sh
    cmake --build . --config Debug
popd
