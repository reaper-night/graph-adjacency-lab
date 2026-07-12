@echo off
chcp 65001 >nul
cd /d "%~dp0"

set CC=gcc
set CFLAGS=-Wall -Wextra -g -Iinclude -finput-charset=UTF-8 -fexec-charset=GBK
set SRCDIR=src
set BINDIR=bin
set BUILDDIR=build

if not exist "%BUILDDIR%" mkdir "%BUILDDIR%"
if not exist "%BINDIR%" mkdir "%BINDIR%"

echo Compiling source files...

%CC% %CFLAGS% -c "%SRCDIR%\main.c" -o "%BUILDDIR%\main.o"
%CC% %CFLAGS% -c "%SRCDIR%\graph.c" -o "%BUILDDIR%\graph.o"
%CC% %CFLAGS% -c "%SRCDIR%\utils.c" -o "%BUILDDIR%\utils.o"

echo Linking executable...

%CC% -o "%BINDIR%\app.exe" "%BUILDDIR%\main.o" "%BUILDDIR%\graph.o" "%BUILDDIR%\utils.o"

if %ERRORLEVEL% equ 0 (
    echo Build successful!
    echo Executable: %BINDIR%\app.exe
    echo.
    echo Running test...
    "%BINDIR%\app.exe"
    echo.
    echo Press any key to exit...
    pause >nul
) else (
    echo Build failed!
    pause
)