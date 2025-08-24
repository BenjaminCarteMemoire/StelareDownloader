#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include "class_packages.h"

const inline std::string STELARE_VERSION = "0.3.1";

// Control values.

#if defined(_WIN32) || defined(_WIN64)
constexpr bool IS_WINDOWS = true;
#else
constexpr bool IS_WINDOWS = false;
#endif

#if defined(STELARE_CLI)
constexpr bool IS_CLI = true;
constexpr bool IS_GUI = false;
#else
constexpr bool IS_CLI = false;
constexpr bool IS_GUI = true;
#endif

// Path values.

const extern std::string STELARE_TEMP_FOLDER;
const extern std::string STELARE_BACKUP_FOLDER;
const extern std::string STELARE_EXE_FOLDER;
const extern std::string STELARE_CONFIG_FILE;

// Time values.

const extern int STELARE_TIME_WAIT;

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"

// WebUI Values.
extern webui::window MAIN;
extern std::map<std::string, webui::window> WEBUI_WINDOWS;
const extern std::string STELARE_GUI_FOLDER;
extern std::unordered_map<std::string, Package*> WEBUI_BINDINGS_MAP;

#else
class Package;
#endif

// Storage values.
extern std::vector<Package> PACKAGES;

extern std::string selected_drive_letter;
extern std::string version;
extern std::string region;
extern std::string version_region;
extern std::string mac_address;

extern std::vector<std::string> SUMMARY;

// Update values.
extern bool need_to_update;
extern std::string new_version_filename;
extern std::string new_version_url;

// Config values
#include "../lib/mini/ini.h"
extern mINI::INIFile config_file;
extern mINI::INIStructure config;

extern std::string locale;