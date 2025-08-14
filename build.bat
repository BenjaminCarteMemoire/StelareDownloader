@echo off
setlocal

REM ========= CONFIGURATION =========
set SRC_DIR=src
set INCLUDE_DIR=include
set WEBUI_DIR=lib\webui
set LIBZIP_DIR=lib\libzip
set ZLIB_DIR=lib\zlib
set HTTPLIB_DIR=lib\httplib

set OUT_EXE=bin/StelareDownloader.exe
set OUT_OBJ=build\\
set CFLAGS=/std:c++17 /MD /EHsc /nologo
set DEFINES=/D ZIP_STATIC

set INCLUDES=^
 /I%INCLUDE_DIR% ^
 /I%WEBUI_DIR%\include ^
 /I%ZLIB_DIR%\include ^
 /I%LIBZIP_DIR%\include ^
 /I%HTTPLIB_DIR%\include

set SOURCES=^
 %SRC_DIR%\main.cpp ^
 %SRC_DIR%\globals.cpp ^
 %SRC_DIR%\utils.cpp ^
 %SRC_DIR%\class_packages.cpp ^
 %SRC_DIR%\storage.cpp ^
 %SRC_DIR%\gui.cpp ^
 %SRC_DIR%\packages.cpp

set LIBS=^
 %WEBUI_DIR%\lib\webui-2-static.lib ^
 %ZLIB_DIR%\lib\libz-static.lib ^
 %LIBZIP_DIR%\lib\libzip-static.lib ^
 urlmon.lib ole32.lib oleaut32.lib uuid.lib ws2_32.lib ^
 user32.lib gdi32.lib advapi32.lib shell32.lib legacy_stdio_definitions.lib

REM ========= BUILD =========
echo Compiling...
cl %CFLAGS% %DEFINES% %SOURCES% %INCLUDES% /Fe%OUT_EXE% /Fo"%OUT_OBJ%" /link %LIBS%

endlocal
pause