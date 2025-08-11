// Base librairies
#include <iostream>

// Specific librairies

// Include files
#include "../include/globals.h"
#include "../include/gui.h"
#include "../include/utils.h"
#include "../include/packages.h"

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"
#endif

int main() {

    prepare_packages();

    #ifndef STELARE_CLI
        webui::set_default_root_folder( STELARE_GUI_FOLDER );
        GUI_Tools::bind_main_window_events();
        MAIN.show_browser( "index.html", choose_the_real_best_browser() );
        webui::wait();
    #endif
    return 0;

}