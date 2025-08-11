#include "../include/packages.h"
#include "../include/class_packages.h"
#include "../include/globals.h"
#include "../include/storage.h"
#include "../include/utils.h"

#ifndef STELARE_CLI
#include "../lib/webui/include/webui.hpp"
#include "../include/gui.h"
#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#endif

void prepare_packages() {

    // ==================== UNINSTALL CFW 3DS ====================

    static Package Uninstall_CFW( "uninstall_cfw", "3DS / Retirer le hack", 'U', Package_Category::Pack );

    #ifndef STELARE_CLI

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

    #else

    // Step 1
    Uninstall_CFW.callbacks.push_back( []( std::map<std::string, std::string> add = {}) {
        log_info( "[Pack] Begin Uninstall CFW" );
        if ( Uninstall_CFW.callbacks.size() >= 2 )
            CLI::drive_letter_prompt( Uninstall_CFW.callbacks[1] );
        else
            log_info( "Problem with Uninstall CFW Package callbacks." );

    });

    // Step 2
    Uninstall_CFW.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        Uninstall_CFW.automatic_process();
        job_done();

    });

    #endif

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

    // ==================== MSET9 3DS ====================

    static Package MSET9( "mset9", "3DS / MSET9", 'M', Package_Category::Pack );

    #ifndef STELARE_CLI
    // Step 1
    MSET9.callbacks.push_back([]( webui::window::event *e ) {

        log_info( "[Pack] Begin MSET9" );
        if ( MSET9.callbacks.size() >= 2 )
            select_drive_letter_window( [](webui::window::event *e) { MSET9.callbacks[1](e); } );
        else
            log_info( "Problem with MSET9 Package callbacks." );
    });

    // Step 2.
    MSET9.callbacks.push_back([](webui::window::event*e) {

        selected_drive_letter = e->get_string();
        GUI_Tools::close_a_window( "Drive_Letter" );
        MSET9.automatic_process();
        job_done();
        webui::wait();

    });
    #else

    // Step 1
    MSET9.callbacks.push_back([]( std::map<std::string, std::string> add = {} ) {

        log_info( "[Pack] Begin MSET9" );
        if ( MSET9.callbacks.size() >= 2 )
            CLI::drive_letter_prompt( MSET9.callbacks[1] );
        else
            log_info( "Problem with MSET9 Package callbacks." );
    });

    // Step 2.
    MSET9.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        MSET9.automatic_process();
        job_done();

    });

    #endif

    MSET9.downloads = {
        { "MSET9-v2.1.zip", "https://github.com/hacks-guide/MSET9/releases/download/v2.1/MSET9-v2.1.zip" },
        { "python-3.13.5-amd64.exe", "https://www.python.org/ftp/python/3.13.5/python-3.13.5-amd64.exe" }
    };

    MSET9.extract_all = {
        {"MSET9-v2.1.zip", "mset9"}
    };

    MSET9.move_to_executables = {
        "python-3.13.5-amd64.exe"
    };

    MSET9.move_to_drive_folders = {
        {"mset9", ""}
    };

    MSET9.add_in_package_global();

    // ==================== WILBRAND WII ====================

    static Package Wilbrand( "wilbrand", "Wii / Wilbrand", 'W', Package_Category::Pack );

    #ifndef STELARE_CLI

    // Step 1
    Wilbrand.callbacks.push_back([]( webui::window::event *e ) {

        log_info( "[Pack] Begin Wilbrand" );
        if ( Wilbrand.callbacks.size() >= 2 )
            select_drive_letter_window( [](webui::window::event *e) { Wilbrand.callbacks[1](e); } );
        else
            log_info( "Problem with Wilbrand Package callbacks." );
    });

    // Step 2.
    Wilbrand.callbacks.push_back([](webui::window::event*e) {

        selected_drive_letter = e->get_string();
        GUI_Tools::close_a_window( "Drive_Letter" );

        // New window.
        if ( WEBUI_WINDOWS.find( "Wii_Version_Region" ) != WEBUI_WINDOWS.end() ) {
            // Already exist.
            WEBUI_WINDOWS["Wii_Version_Region"].close();
            WEBUI_WINDOWS["Wii_Version_Region"].destroy();
        }

        WEBUI_WINDOWS["Wii_Version_Region" ] = {};
        WEBUI_WINDOWS["Wii_Version_Region" ].set_size( 640, 480 );
        if ( Wilbrand.callbacks.size() >= 3 )
            WEBUI_WINDOWS["Wii_Version_Region" ].bind( "continue", [](webui::window::event *e) {Wilbrand.callbacks[2](e); } );
        else
            log_info( "Problem with Wilbrand Package callbacks." );

        log_info( "Boot Wii Version / Region window." );

        WEBUI_WINDOWS["Wii_Version_Region" ].show_browser( "wii_version_region.html", choose_the_real_best_browser() );
        webui::wait();

    });

    // Step 3
    Wilbrand.callbacks.push_back([](webui::window::event *e) {

        version_region = e->get_string();
        GUI_Tools::close_a_window( "Wii_Version_Region" );

        // New window.
        if ( WEBUI_WINDOWS.find( "Wii_Mac_Address" ) != WEBUI_WINDOWS.end() ) {
            // Already exist.
            WEBUI_WINDOWS["Wii_Mac_Address"].close();
            WEBUI_WINDOWS["Wii_Mac_Address"].destroy();
        }

        WEBUI_WINDOWS["Wii_Mac_Address" ] = {};
        WEBUI_WINDOWS["Wii_Mac_Address" ].set_size( 640, 480 );
        WEBUI_WINDOWS["Wii_Mac_Address"].bind( "verify_mac_address", [](webui::window::event *e) { e->return_bool( verify_mac_address( e->get_string() ) ); } );
        if ( Wilbrand.callbacks.size() >= 4 )
            WEBUI_WINDOWS["Wii_Mac_Address" ].bind( "continue", [](webui::window::event *e) {Wilbrand.callbacks[3](e); } );
        else
            log_info( "Problem with Wilbrand Package callbacks." );

        log_info( "Boot Wii Mac Address window." );

        WEBUI_WINDOWS["Wii_Mac_Address" ].show_browser( "wii_mac_address.html", choose_the_real_best_browser() );
        webui::wait();

    });

    // Step 4
    Wilbrand.callbacks.push_back([](webui::window::event *e) {

        mac_address = e->get_string();
        GUI_Tools::close_a_window( "Wii_Mac_Address" );
        Wilbrand.automatic_process();

        if ( IS_WINDOWS ) {
            change_status( "Exécution de : Wilbrand.exe" );
            std::string command = std::string( STELARE_EXE_FOLDER ) + "\\Wilbrand.exe " + mac_address + " " + today_date() + " " + version_region + " " + selected_drive_letter;
            system( command.c_str() );
        }

        job_done();
        webui::wait();

    });

    #else

    // Step 1
    Wilbrand.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        log_info( "[Pack] Begin Wilbrand" );
        if ( Wilbrand.callbacks.size() >= 2 )
            CLI::drive_letter_prompt( Wilbrand.callbacks[1] );
        else
            log_info( "Problem with Wilbrand Package callbacks." );
    });

    // Step 2.
    Wilbrand.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        if ( Wilbrand.callbacks.size() >= 3 )
            CLI::wii_mac_address_prompt( Wilbrand.callbacks[2] );
        else
            log_info( "Problem with Wilbrand Package callbacks." );

    });

    // Step 3.
    Wilbrand.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        if ( Wilbrand.callbacks.size() >= 4 )
            CLI::wii_version_prompt( Wilbrand.callbacks[3] );
        else
            log_info( "Problem with Wilbrand Package callbacks." );

    });

    // Step 4.
    Wilbrand.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        if ( Wilbrand.callbacks.size() >= 5 )
            CLI::wii_region_prompt( Wilbrand.callbacks[4] );
        else
            log_info( "Problem with Wilbrand Package callbacks." );

    });

    // Step 5.
    Wilbrand.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        Wilbrand.automatic_process();

        if ( IS_WINDOWS ) {
            change_status( "Exécution de : Wilbrand.exe" );
            std::string command = std::string( STELARE_EXE_FOLDER ) + "\\Wilbrand.exe " + mac_address + " " + today_date() + " " + version_region + " " + selected_drive_letter;
            system( command.c_str() );
        }

        job_done();

    });


    #endif

    Wilbrand.downloads = {
        {"Wilbrand.exe", "https://raw.githubusercontent.com/giantpune/mailboxbomb/master/Wilbrand.exe"},
        {"hackmii_installer_v1.2.zip","https://bootmii.org/hackmii_installer_v1.2.zip"}
    };

    Wilbrand.move_to_executables = {
        "Wilbrand.exe"
    };

    Wilbrand.extract_file = {
        { "hackmii_installer_v1.2.zip", { "hackmii_installer_v1.2/boot.elf", "boot.elf" } }
    };

    Wilbrand.move_to_drive_files = {
        { "boot.elf", "" }
    };

    Wilbrand.add_in_package_global();

    // ==================== GUIFORMAT EXE ====================

    static Package GUIFormat( "guiformat", "GUIFormat", 'G', Package_Category::Exe );

    #ifndef STELARE_CLI

    GUIFormat.callbacks.push_back([]( webui::window::event *e ) {
        GUIFormat.automatic_process();
        job_done();
    });

    #else

    GUIFormat.callbacks.push_back([](std::map<std::string, std::string> add = {}) {
        GUIFormat.automatic_process();
        job_done();
    });

    #endif

    GUIFormat.downloads = {
        {"guiformat.exe", "https://stelare.org/assets/stelare/tutorials/sd/guiformat.exe"}
    };

    GUIFormat.move_to_executables = {
        "guiformat.exe"
    };

    GUIFormat.add_in_package_global();

    // ==================== CLEAR CACHE TOOL ====================

    static Package Clear_Cache( "clear_cache", "Vider le cache / backup / exécutable", 'C', Package_Category::Tools );

    #ifndef STELARE_CLI

    Clear_Cache.callbacks.push_back([](webui::window::event *e ) {

        std::vector<std::string> folders_clear = { STELARE_TEMP_FOLDER, STELARE_BACKUP_FOLDER, STELARE_EXE_FOLDER };

        processing_window();
        Sleep( STELARE_TIME_WAIT );
        for ( auto folder: folders_clear ) {
            change_status( "Suppression des fichiers de : " + folder );
            Storage::clear_folder( folder );
        }
        job_done();

    });

    #else

    Clear_Cache.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        if ( Clear_Cache.callbacks.size() >= 2 )
            CLI::warning( Clear_Cache.callbacks[1] );
        else
            log_info( "Problem with Clear_Cache Package callbacks." );

    });

    Clear_Cache.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        std::vector<std::string> folders_clear = { STELARE_TEMP_FOLDER, STELARE_BACKUP_FOLDER, STELARE_EXE_FOLDER };

        for ( auto folder: folders_clear ) {
            change_status( "Suppression des fichiers de : " + folder );
            Storage::clear_folder( folder );
        }
        job_done();

    });

    #endif

    Clear_Cache.add_in_package_global();

}
