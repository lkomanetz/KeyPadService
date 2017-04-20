@echo off

mkdir Build
pushd Build

cl -Zi -I ..\Headers ..\Test_Win32.cpp User32.lib

popd