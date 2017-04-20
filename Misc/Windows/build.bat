@echo off

mkdir Build
pushd Build

del /q *
for /d %%x in (*) do @rd /s /q "%%x"

cl -EHsc -Zi -I ..\Headers ..\Test_Win32.cpp User32.lib

popd