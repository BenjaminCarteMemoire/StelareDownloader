#include "../include/gui.h"
#include "../include/storage.h"
#include "../include/json.hpp"
#include "../include/utils.h"

namespace GUI_Tools {

    void return_drive_letters(webui::window::event *e) {

        std::vector<std::string> removable_drives = Storage::return_available_removable_drives();

        json j = removable_drives;
        json_string | e->return_string;

    }

}

void select_drive_letter_window( webui::window::event::handler::callback_t callback ) {

    if ( WEBUI_WINDOWS.find( "Drive_Letter" ) != WEBUI_WINDOWS.end() ) {
        // Already exist.
        WEBUI_WINDOWS["Drive_Letter"].close();
        WEBUI_WINDOWS["Drive_Letter"].destroy();
    }

    WEBUI_WINDOWS["Drive_Letter" ] = new webui::window;
    WEBUI_WINDOWS["Drive_Letter" ].set_size( 640, 480 );
    WEBUI_WINDOWS["Drive_Letter" ].bind( "get_drives",  GUI_Tools::return_drive_letters );
    WEBUI_WINDOWS["Drive_Letter" ].bind( "continue", callback );

    log_info( "Boot drive window." );

    WEBUI_WINDOWS["Drive_Letter" ].show_browser( "select_drive.html", choose_the_real_best_browser() );
    webui::wait();

}