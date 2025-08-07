#pragma once

#ifndef STELARE_CLI
#include "globals.h"
#include "../lib/webui/include/webui.hpp"

namespace GUI_Tools {

    void return_drive_letters( webui::window::event* e );

}

void select_drive_letter_window( webui::window::event::handler::callback_t callback );

#endif

