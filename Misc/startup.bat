@echo off
subst w: /d
subst w: c:\Code
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x64
set path=w:\KeyPad\Misc;%path%