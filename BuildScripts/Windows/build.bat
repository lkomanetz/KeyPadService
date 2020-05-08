@echo off

mkdir Build
pushd Build

del /q *
for /d %%x in (*) do @rd /s /q "%%x"

cl -D PLATFORM_WINDOWS=1 -EHsc -Zi -I ..\Headers -I ..\Windows\Headers ..\keypadservice.cpp ..\Windows\*.cpp ..\Code\*.cpp User32.lib XInput.lib Advapi32.lib

popd