#include "../include/gui.h"

#include <chrono>

#include "../include/storage.h"
#include "../include/json.hpp"
#include "../include/utils.h"

using json = nlohmann::json;

namespace GUI_Tools {

    void close_a_window( std::string window_name ) {

        if ( WEBUI_WINDOWS.find( window_name ) != WEBUI_WINDOWS.end() ) {
            WEBUI_WINDOWS[window_name].close();
            WEBUI_WINDOWS[window_name].destroy();
        }

    }

    void return_drive_letters(webui::window::event *e) {

        std::vector<std::string> removable_drives = Storage::return_available_removable_drives();

        json j = removable_drives;
        e->return_string(j.dump());

    }

    void global_callback_for_packages( webui::window::event *e ) {

        auto iterator = WEBUI_BINDINGS_MAP.find( e->element );
        if ( iterator != WEBUI_BINDINGS_MAP.end() ) {
            if (iterator->second->callbacks.size() >= 1 )
                iterator->second->callbacks[0](e);
        }

    }

    void bind_main_window_events() {

        for ( auto& package: PACKAGES ) {
            if ( package.callbacks.size() >= 1 ) {
                WEBUI_BINDINGS_MAP[package.name] = &package;
                MAIN.bind( package.name, global_callback_for_packages );
            }
        }

    }

}

void select_drive_letter_window( webui::window::event::handler::callback_t callback ) {

    if ( WEBUI_WINDOWS.find( "Drive_Letter" ) != WEBUI_WINDOWS.end() ) {
        // Already exist.
        WEBUI_WINDOWS["Drive_Letter"].close();
        WEBUI_WINDOWS["Drive_Letter"].destroy();
    }

    WEBUI_WINDOWS["Drive_Letter" ] = {};
    WEBUI_WINDOWS["Drive_Letter" ].set_size( 640, 480 );
    WEBUI_WINDOWS["Drive_Letter" ].bind( "get_drives",  GUI_Tools::return_drive_letters );
    WEBUI_WINDOWS["Drive_Letter" ].bind( "continue", callback );

    log_info( "Boot drive window." );

    WEBUI_WINDOWS["Drive_Letter" ].show_browser( "select_drive.html", choose_the_real_best_browser() );
    webui::wait();

}

void processing_window() {

    GUI_Tools::close_a_window( "Processing" );
    WEBUI_WINDOWS["Processing" ] = {};
    WEBUI_WINDOWS["Processing" ].set_size( 640, 480 );

    log_info( "Boot processing window." );
    WEBUI_WINDOWS["Processing" ].show_browser( "process.html", choose_the_real_best_browser() );
    // webui::wait();

}

void change_status( std::string new_status )  {

    if ( WEBUI_WINDOWS.find( "Processing" ) != WEBUI_WINDOWS.end() ) {
        WEBUI_WINDOWS["Processing" ].run( "document.getElementById('waiting_text').innerHTML = '" + new_status + "'" );
    } else
        std::cout << "Can't change status. Processing not loaded." << std::endl;

    SUMMARY.push_back( new_status );

}

void job_done() {

    if ( WEBUI_WINDOWS.find( "Processing" ) != WEBUI_WINDOWS.end() ) {
        WEBUI_WINDOWS["Processing"].run( "document.getElementById('loader_bar').style.display='none'" );
        WEBUI_WINDOWS["Processing"].run( "document.getElementById('success_mark').style.display='block'" );
        WEBUI_WINDOWS["Processing"].run( "document.getElementById('warning_text').innerHTML=''" );
        WEBUI_WINDOWS["Processing"].run("document.getElementById('title_text').innerHTML='Processus terminé !'");
        change_status( "Le transfert a été effectué sur le lecteur. Vous pouvez fermer la fenêtre et quitter le gestionnaire." );
    } else
        std::cout << "Can't change status. Processing not loaded." << std::endl;

    SUMMARY.clear();
}