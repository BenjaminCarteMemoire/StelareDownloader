# Stelare Downloader

## Description

A download manager for console hacking utilities and emulator utilities, created by the team at Stelare.org.

Available packages (For now): 

- MSET9 (From the official Github)
- 3DS / CFW uninstallation
- Wii / Wilbrand
- 3DS / Hack finalization
- GUIFormat
- Others will be added...

**If you encounter missing DLL issues when launching the software, please install these redistributables: https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170**

This software has two versions:

- Web interface (WEBUI): A modern web interface using WEBUI. (Works on Windows 10 and Windows 11)
- CLI (Command-Line Interface): Interface directly in the terminal. (Works with Windows 8.1 and later)

## Supports

Currently only supports Windows. macOS and Linux support are planned for the future.

## Build

To build the software in web interface:
- Run “build.bat” with MSVC
- Copy the “gui” folder to the same location as the generated executable.

To build the software in CLI interface:
- Run “build_cli.bat” with MSVC
- Or define the “STELARE_CLI” constant, remove “gui.cpp/gui.h” during compilation, and add “cli.cpp/cli.h”.

## Thanks

- Thanks to everyone who created each of the software programs (MSET9, Wilbrand, etc.).
