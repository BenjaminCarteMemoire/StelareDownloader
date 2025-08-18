// Base librairies
#include <iostream>

// Specific librairies

// Include files
#include "../include/globals.h"
#include "../include/utils.h"
#include "../include/packages.h"
#include "../include/storage.h"
#include "../include/i18n.h"

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

    Storage::read_config_file();
    locale = config["i18n"]["lang"];
    prepare_packages();

    #ifndef STELARE_CLI

        // Launch update package.
        if ( PACKAGES.size() >= 1 && PACKAGES[0].name == "stelare_downloader" ) {
            if ( PACKAGES[0].callbacks.size() >= 1 )
                PACKAGES[0].callbacks[0](nullptr);
        }

        webui::set_default_root_folder( STELARE_GUI_FOLDER + locale + "/" );
        GUI_Tools::bind_main_window_events();
        MAIN.show_browser( "index.html", choose_the_real_best_browser() );
        webui::wait();

    #else

        // Launch update package.
        if ( PACKAGES.size() >= 1 && PACKAGES[0].name == "stelare_downloader" ) {
            if ( PACKAGES[0].callbacks.size() >= 1 )
                PACKAGES[0].callbacks[0]({});
        }

        CLI::start();

    #endif

    return 0;

}