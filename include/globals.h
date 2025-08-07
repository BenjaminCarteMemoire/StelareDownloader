#pragma once

#include <iostream>
#include <vector>
#include <map>

#include "class_packages.h"

#if defined(_WIN32) || defined(_WIN64)
constexpr bool IS_WINDOWS = true;
#else
constexpr bool IS_WINDOWS = false;
#endif

const extern std::string STELARE_TEMP_FOLDER;
const extern std::string STELARE_BACKUP_FOLDER;
const extern std::string STELARE_EXE_FOLDER;

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"

extern webui::window MAIN;
extern std::map<std::string, webui::window> WEBUI_WINDOWS;
const extern std::string STELARE_GUI_FOLDER;

#endif

extern std::vector<Package> PACKAGES;