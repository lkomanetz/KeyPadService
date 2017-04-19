@echo off

mkdir Build
pushd Build

cl -Zi ..\test.cpp User32.lib

popd