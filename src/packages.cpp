#include "../include/packages.h"
#include "../include/class_packages.h"
#include "../include/globals.h"
#include "../include/storage.h"
#include "../include/utils.h"
#include "../include/i18n.h"

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

    // ==================== STELARE DOWNLOADER UPDATE CHECK ====================

    static Package Stelare_Downloader( "stelare_downloader", "Vérifier les mises à jour de Stelare Downloader", '#', Package_Category::Essentials);

    #ifndef STELARE_CLI

    Stelare_Downloader.callbacks.push_back([](webui::window::event *e) {

        log_info( "[Update] Check if updates are available" );

        if ( Stelare_Downloader.dynamic_downloads.empty() || Stelare_Downloader.dynamic_downloads.size() != 1 )
            return;

        for ( auto update : Stelare_Downloader.dynamic_downloads ) {

            std::string current_version_filename = update.first;
            std::string new_filename = dynamic_download_handle( current_version_filename, &update.second, &Stelare_Downloader );

            if ( new_filename == current_version_filename ) // Same version, don't update.
                break;

            log_info( "[Update] There is a new update available." );

            need_to_update = true;
            new_version_filename = new_filename;
            new_version_url = update.second.first;

        }

    });

    #else

    Stelare_Downloader.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        log_info( "[Update] Check if updates are available" );

        if ( Stelare_Downloader.dynamic_downloads.empty() || Stelare_Downloader.dynamic_downloads.size() != 1 )
            return;

        for ( auto update : Stelare_Downloader.dynamic_downloads ) {

            std::string current_version_filename = update.first;
            std::string new_filename = dynamic_download_handle( current_version_filename, &update.second, &Stelare_Downloader );

            if ( new_filename == current_version_filename ) // Same version, don't update.
                break;

            log_info( "[Update] There is a new update available." );

            need_to_update = true;
            new_version_filename = new_filename;
            new_version_url = update.second.first;

        }

    });

    #endif

    Stelare_Downloader.dynamic_downloads = {
        {"Stelare_Downloader_v0.1.0_x64.zip ", {"https://github.com/BenjaminCarteMemoire/StelareDownloader/releases/download/v0.1.0/Stelare_Downloader_v0.1.0_x64.zip", "zip" } }
    };

    Stelare_Downloader.add_in_package_global();

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
        // { "Luma3DSv13.3.2.zip", "https://github.com/LumaTeam/Luma3DS/releases/download/v13.3.2/Luma3DSv13.3.2.zip" },
        // { "GodMode9-v2.1.1-20220322194259.zip", "https://github.com/d0k3/GodMode9/releases/download/v2.1.1/GodMode9-v2.1.1-20220322194259.zip" },
        // { "DSiWareUninstaller.3dsx", "https://github.com/MechanicalDragon0687/DSiWare-Uninstaller/releases/download/1.0.1/DSiWareUninstaller.3dsx" },
        { "safety_test.gm9", "https://stelare.org/assets/stelare/tutorials/uninstall_cfw/safety_test.gm9" },
        { "uninstall_cfw.gm9", "https://stelare.org/assets/stelare/tutorials/uninstall_cfw/uninstall_cfw.gm9" }
    };

    Uninstall_CFW.dynamic_downloads = {
        { "Luma3DSv13.3.3.zip", { "https://github.com/LumaTeam/Luma3DS/releases/download/v13.3.3/Luma3DSv13.3.3.zip", "zip" } },
        { "GodMode9-v2.1.1-20220322194259.zip", { "https://github.com/d0k3/GodMode9/releases/download/v2.1.1/GodMode9-v2.1.1-20220322194259.zip", "zip" } },
        { "DSiWareUninstaller.3dsx", { "https://github.com/MechanicalDragon0687/DSiWare-Uninstaller/releases/download/1.0.1/DSiWareUninstaller.3dsx", "3dsx" } }
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
        // { "MSET9-v2.1.zip", "https://github.com/hacks-guide/MSET9/releases/download/v2.1/MSET9-v2.1.zip" },
        { "python-3.13.5-amd64.exe", "https://www.python.org/ftp/python/3.13.5/python-3.13.5-amd64.exe" }
    };

    MSET9.dynamic_downloads = {
        { "MSET9-v2.1.zip", { "https://github.com/hacks-guide/MSET9/releases/download/v2.1/MSET9-v2.1.zip", "zip" } }
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

    // ==================== 3DS TRUE FINALIZE KIT ====================

    // ==================== 3DS FINALIZE KIT ====================

    static Package Finalize_Kit( "finalize_kit", "3DS / Kit applications du hack", 'K', Package_Category::Pack );

    #ifndef STELARE_CLI

    // Step 1.
    Finalize_Kit.callbacks.push_back([](webui::window::event*e) {

        log_info( "[Pack] Begin Finalize Kit" );
        if ( Finalize_Kit.callbacks.size() >= 2 )
            select_drive_letter_window( [](webui::window::event *e) { Finalize_Kit.callbacks[1](e); } );
        else
            log_info( "Problem with Finalize Kit Package callbacks." );

    });

    // Step 2.
    Finalize_Kit.callbacks.push_back([](webui::window::event*e) {

        selected_drive_letter = e->get_string();
        GUI_Tools::close_a_window( "Drive_Letter" );
        Finalize_Kit.automatic_process();
        job_done();
        webui::wait();

    });

    #else

    // Step 1
    Finalize_Kit.callbacks.push_back( []( std::map<std::string, std::string> add = {}) {
        log_info( "[Pack] Begin Finalize Kit" );
        if ( Finalize_Kit.callbacks.size() >= 2 )
            CLI::drive_letter_prompt( Finalize_Kit.callbacks[1] );
        else
            log_info( "Problem with Finalize Kit Package callbacks." );

    });

    // Step 2
    Finalize_Kit.callbacks.push_back([](std::map<std::string, std::string> add = {}) {

        Finalize_Kit.automatic_process();
        job_done();

    });

    #endif

    Finalize_Kit.dynamic_downloads = {
        { "Luma3DSv13.3.3.zip", { "https://github.com/LumaTeam/Luma3DS/releases/download/v13.3.3/Luma3DSv13.3.3.zip", "zip" } },
        { "GodMode9-v2.1.1-20220322194259.zip", { "https://github.com/d0k3/GodMode9/releases/download/v2.1.1/GodMode9-v2.1.1-20220322194259.zip", "zip" } },
        { "Homebrew_Launcher.cia", { "https://github.com/PabloMK7/homebrew_launcher_dummy/releases/download/v1.0/Homebrew_Launcher.cia", "cia" } },
        { "FBI.3dsx", {"https://github.com/Steveice10/FBI/releases/download/2.6.1/FBI.3dsx", "3dsx" } },
        { "FBI.cia", {"https://github.com/Steveice10/FBI/releases/download/2.6.1/FBI.cia", "cia" } },
        { "faketik.3dsx", {"https://github.com/ihaveamac/faketik/releases/download/v1.1.2/faketik.3dsx", "3dsx" } },
        { "Universal-Updater.cia", {"https://github.com/Universal-Team/Universal-Updater/releases/download/v3.2.8/Universal-Updater.cia", "cia"} },
        { "Anemone3DS.cia", {"https://github.com/astronautlevel2/Anemone3DS/releases/download/v3.0.1/Anemone3DS.cia", "cia"} },
        { "Checkpoint.cia", { "https://github.com/BernardoGiordano/Checkpoint/releases/download/v3.10.1/Checkpoint.cia", "cia" } },
        { "ftpd.cia", { "https://github.com/mtheall/ftpd/releases/download/v3.2.1/ftpd.cia", "ftpd.cia" } },
        { "y_title_fixer.firm", {"https://github.com/chalenged/gm9-title-fixer/releases/download/v1.1.4/y_title_fixer.firm", "firm" } }
    };

    Finalize_Kit.extract_all = {
        {"Luma3DSv13.3.3.zip", "luma3ds"}
    };

    Finalize_Kit.extract_file = {
        {"GodMode9-v2.1.1-20220322194259.zip", {"GodMode9.firm", "GodMode9.firm"} }
    };

    Finalize_Kit.extract_folder = {
        { "GodMode9-v2.1.1-20220322194259.zip", { "gm9", "godmode9/gm9" } }
    };

    Finalize_Kit.move_to_drive_files = {
        {"GodMode9.firm", "luma/payloads/"},
        {"FBI.3dsx", "3ds/"},
        {"faketik.3dsx", "3ds/"},
        {"Homebrew_Launcher.cia", "cias/"},
        {"FBI.cia", "cias/"},
        {"Universal-Updater.cia", "cias/"},
        {"Anemone3DS.cia", "cias/"},
        {"Checkpoint.cia", "cias/"},
        {"ftpd.cia", "cias/"},
        {"y_title_fixer.firm", "luma/payloads/"}
    };

    Finalize_Kit.move_to_drive_folders = {
        {"luma3ds", ""},
        {"godmode9", ""}
    };

    Finalize_Kit.add_in_package_global();

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
            std::string command = std::string( STELARE_EXE_FOLDER ) + "\\Wilbrand.exe " + mac_address + " " + yesterday_date() + " " + version_region + " " + selected_drive_letter;
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
            std::string command = std::string( STELARE_EXE_FOLDER ) + "\\Wilbrand.exe " + mac_address + " " + yesterday_date() + " " + version_region + " " + selected_drive_letter;
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
            change_status( _( "package_folder_erase" ) + folder );
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
