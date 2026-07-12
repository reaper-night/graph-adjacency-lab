@echo off
cd /d "%~dp0"

set BINDIR=bin
set BUILDDIR=build

if exist "%BUILDDIR%" (
    rmdir /s /q "%BUILDDIR%"
    echo Removed %BUILDDIR%
)

if exist "%BINDIR%" (
    rmdir /s /q "%BINDIR%"
    echo Removed %BINDIR%
)

echo Clean completed!
pause