#include "../include/packages.h"
#include "../include/class_packages.h"
#include "../include/globals.h"

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"
#endif

void prepare_packages() {

    Package Uninstall_CFW( "uninstall_cfw", "3DS / Retirer le hack" );

    // Step 1.
    Uninstall_CFW.callbacks.push_back([](webui::window::event*e) {

        log_info( "[Pack] Begin Uninstall CFW" );

    });

}
