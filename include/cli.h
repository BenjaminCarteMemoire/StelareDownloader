#pragma once

#include "globals.h"

#ifdef STELARE_CLI

namespace CLI {

    void start();

    char select_pack();

    void warning( std::function<void(std::map<std::string, std::string> add)> callback );

    void drive_letter_prompt( std::function<void(std::map<std::string, std::string> add)> callback );

    void wii_mac_address_prompt( std::function<void(std::map<std::string, std::string> add)> callback );

    void wii_version_prompt( std::function<void(std::map<std::string, std::string> add)> callback );

    void wii_region_prompt( std::function<void(std::map<std::string, std::string> add)> callback );

}

void change_status( std::string new_status );

void job_done();

#endif