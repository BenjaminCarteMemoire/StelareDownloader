#pragma once

#include <regex>

void log_info( std::string message );
bool verify_mac_address( std::string mac_address );
std::string today_date();

#ifndef STELARE_CLI

#include "../lib/webui/include/webui.hpp"
size_t choose_the_real_best_browser();

#endif