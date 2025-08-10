#pragma once

#ifndef STELARE_CLI
#include "globals.h"
#include "../lib/webui/include/webui.hpp"

namespace GUI_Tools {

    void close_a_window( std::string window_name );

    void return_drive_letters( webui::window::event* e );

}

void select_drive_letter_window( webui::window::event::handler::callback_t callback );

void processing_window();

void change_status( std::string new_status );

void job_done();

#endif

