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
%CC% %CFLAGS% -c "%SRCDIR%\logger.c" -o "%BUILDDIR%\logger.o"
%CC% %CFLAGS% -c "%SRCDIR%\utils.c" -o "%BUILDDIR%\utils.o"
%CC% %CFLAGS% -c "%SRCDIR%\sort.c" -o "%BUILDDIR%\sort.o"
%CC% %CFLAGS% -c "%SRCDIR%\matrix.c" -o "%BUILDDIR%\matrix.o"

echo Linking executable...

%CC% -o "%BINDIR%\app.exe" "%BUILDDIR%\main.o" "%BUILDDIR%\logger.o" "%BUILDDIR%\utils.o" "%BUILDDIR%\sort.o" "%BUILDDIR%\matrix.o"

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