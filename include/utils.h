#pragma once

#include <regex>

void log_info( std::string message );
bool verify_mac_address( std::string mac_address );
std::string yesterday_date();
std::string dynamic_download_handle( const std::string& actual_filename, std::pair<std::string,std::string>* download, Package* current_package );

#ifndef STELARE_CLI

#include "../lib/webui/include/webui.hpp"
size_t choose_the_real_best_browser();

#endif