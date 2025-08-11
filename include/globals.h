#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

#include "class_packages.h"

#if defined(_WIN32) || defined(_WIN64)
constexpr bool IS_WINDOWS = true;
#else
constexpr bool IS_WINDOWS = false;
#endif

const extern std::string STELARE_TEMP_FOLDER;
const extern std::string STELARE_BACKUP_FOLDER;
const extern std::string STELARE_EXE_FOLDER;
const extern int STELARE_TIME_WAIT;

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"

extern webui::window MAIN;
extern std::map<std::string, webui::window> WEBUI_WINDOWS;
const extern std::string STELARE_GUI_FOLDER;
extern std::unordered_map<std::string, Package*> WEBUI_BINDINGS_MAP;

#else
class Package;
#endif

extern std::vector<Package> PACKAGES;
extern std::string selected_drive_letter;
extern std::string version;
extern std::string region;
extern std::string version_region;
extern std::string mac_address;

extern std::vector<std::string> SUMMARY;