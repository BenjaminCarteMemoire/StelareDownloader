// Base librairies
#include <iostream>

// Specific librairies

// Include files
#include "../include/globals.h"
#include "../include/utils.h"
#include "../include/packages.h"

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"
#include "../include/gui.h"
#else
#include "../include/cli.h"
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

int main() {

    if ( IS_WINDOWS )
        SetConsoleOutputCP( CP_UTF8 );

    prepare_packages();

    #ifndef STELARE_CLI
        webui::set_default_root_folder( STELARE_GUI_FOLDER );
        GUI_Tools::bind_main_window_events();
        MAIN.show_browser( "index.html", choose_the_real_best_browser() );
        webui::wait();
    #else
        CLI::start();
    #endif
    return 0;

}