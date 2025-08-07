#include "../include/globals.h"
#include "../include/utils.h"

#ifndef STELARE_CLI

/**
 * Because Firefox sucks with event management. Restrict it.
 *
 * @return webui_browser.
 */
size_t choose_the_real_best_browser() {

    size_t pseudo_best_browser = MAIN.get_best_browser();
    if ( pseudo_best_browser == Firefox ) {
        if ( IS_WINDOWS )
            return Edge;
        else
            return ChromiumBased;
    }
    return pseudo_best_browser;

}

#endif
