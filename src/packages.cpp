#include "../include/packages.h"
#include "../include/class_packages.h"
#include "../include/globals.h"
#include "../include/utils.h"

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"
#include "../include/gui.h"
#endif

void prepare_packages() {

    static Package Uninstall_CFW( "uninstall_cfw", "3DS / Retirer le hack", Package_Category::Pack );

    // Step 1.
    Uninstall_CFW.callbacks.push_back([](webui::window::event*e) {

        log_info( "[Pack] Begin Uninstall CFW" );
        if ( Uninstall_CFW.callbacks.size() >= 2 )
            select_drive_letter_window( [](webui::window::event *e) { Uninstall_CFW.callbacks[1](e); } );
        else
            log_info( "Problem with Uninstall CFW Package callbacks." );

    });

    // Step 2.
    Uninstall_CFW.callbacks.push_back([](webui::window::event*e) {

        selected_drive_letter = e->get_string();
        GUI_Tools::close_a_window( "Drive_Letter" );
        Uninstall_CFW.automatic_process();
        job_done();
        webui::wait();

    });

    Uninstall_CFW.downloads = {
        { "Luma3DSv13.3.3.zip", "https://github.com/LumaTeam/Luma3DS/releases/download/v13.3.3/Luma3DSv13.3.3.zip" },
        { "GodMode9-v2.1.1-20220322194259.zip", "https://github.com/d0k3/GodMode9/releases/download/v2.1.1/GodMode9-v2.1.1-20220322194259.zip" },
        { "DSiWareUninstaller.3dsx", "https://github.com/MechanicalDragon0687/DSiWare-Uninstaller/releases/download/1.0.1/DSiWareUninstaller.3dsx" },
        { "safety_test.gm9", "https://stelare.org/assets/stelare/tutorials/uninstall_cfw/safety_test.gm9" },
        { "uninstall_cfw.gm9", "https://stelare.org/assets/stelare/tutorials/uninstall_cfw/uninstall_cfw.gm9" }
    };

    Uninstall_CFW.extract_all = {
        {"Luma3DSv13.3.3.zip", "luma3ds"}
    };

    Uninstall_CFW.extract_file = {
        {"GodMode9-v2.1.1-20220322194259.zip", {"GodMode9.firm", "GodMode9.firm"} }
    };

    Uninstall_CFW.extract_folder = {
        { "GodMode9-v2.1.1-20220322194259.zip", { "gm9", "godmode9/gm9" } }
    };

    Uninstall_CFW.move_to_drive_files = {
        {"GodMode9.firm", "luma/payloads/"},
        {"DSiWareUninstaller.3dsx", "3ds/"},
        {"safety_test.gm9", "gm9/scripts/"},
        {"uninstall_cfw.gm9", "gm9/scripts/"},
    };

    Uninstall_CFW.move_to_drive_folders = {
        {"luma3ds", ""},
        {"godmode9", ""}
    };

    Uninstall_CFW.add_in_package_global();

}
