@echo off
pushd %~dp0
    call generate.bat
    cmake --build . --config Debug
popd