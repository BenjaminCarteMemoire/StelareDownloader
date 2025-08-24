@echo off
setlocal

REM ========= CONFIGURATION =========
set SRC_DIR=updater

set OUT_EXE=bin/updater.exe
set OUT_OBJ=build\\
set CFLAGS=/std:c++17 /MD /EHsc /nologo

set SOURCES=^
 %SRC_DIR%\main.cpp

set LIBS=^
 urlmon.lib ole32.lib oleaut32.lib uuid.lib ws2_32.lib ^
 user32.lib gdi32.lib advapi32.lib shell32.lib legacy_stdio_definitions.lib

REM ========= BUILD =========
echo Compiling...
cl %CFLAGS% %SOURCES% /Fe%OUT_EXE% /Fo"%OUT_OBJ%" /link %LIBS%

endlocal
pause