#pragma once

#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
constexpr bool IS_WINDOWS = true;
#else
constexpr bool IS_WINDOWS = false;
#endif

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"

extern webui::window MAIN;
const extern std::string STELARE_GUI_FOLDER;

#endif