@echo off

mkdir Build
pushd Build

del /q *
for /d %%x in (*) do @rd /s /q "%%x"

cl -EHsc -Zi -I ..\Headers -I ..\Windows\Headers ..\Windows\*.cpp ..\Code\*.cpp User32.lib XInput.lib

popd