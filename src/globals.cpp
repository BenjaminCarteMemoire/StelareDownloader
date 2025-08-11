#include "../include/globals.h"

const std::string STELARE_TEMP_FOLDER = "temp";
const std::string STELARE_BACKUP_FOLDER = "backup";
const std::string STELARE_EXE_FOLDER = "executables";
const int STELARE_TIME_WAIT = 2000;

#ifndef STELARE_CLI

webui::window MAIN;
std::map<std::string, webui::window> WEBUI_WINDOWS = {};
const std::string STELARE_GUI_FOLDER = "gui/";
std::unordered_map<std::string, Package*> WEBUI_BINDINGS_MAP = {};

#endif

std::vector<Package> PACKAGES = {};
std::string selected_drive_letter = "";
std::string version = "";
std::string region = "";
std::string version_region = "";
std::string mac_address = "";

std::vector<std::string> SUMMARY = {};