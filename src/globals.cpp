#include "../include/globals.h"

const std::string STELARE_TEMP_FOLDER = "temp";
const std::string STELARE_BACKUP_FOLDER = "backup";
const std::string STELARE_EXE_FOLDER = "executables";

#ifndef STELARE_CLI

webui::window MAIN;
std::map<std::string, webui::window> WEBUI_WINDOWS = {};
const std::string STELARE_GUI_FOLDER = "gui/";

#endif

std::vector<Package> PACKAGES = {};