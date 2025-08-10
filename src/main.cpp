// Base librairies
#include <iostream>

// Specific librairies

// Include files
#include "../include/globals.h"
#include "../include/utils.h"
#include "../include/packages.h"

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"
#endif

int main() {

    webui::set_default_root_folder( STELARE_GUI_FOLDER );
    MAIN.show_browser( "index.html", choose_the_real_best_browser() );
    webui::wait();
    return 0;

}