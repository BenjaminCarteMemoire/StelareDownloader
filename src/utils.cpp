#include "../include/globals.h"
#include "../include/utils.h"

/**
 * Log some info in the console.
 *
 * @param message
 */
void log_info( std::string message) {

    std::cout << "[INFO] " + message << std::endl;

}

/**
 * Verify if a string provided is a MAC Address.
 *
 * @param mac_address
 * @return bool
 */
bool verify_mac_address( std::string mac_address ) {

    std::regex mac_regex("^([0-9A-Fa-f]{2}[:-]){5}([0-9A-Fa-f]{2})$");
    return std::regex_match(mac_address, mac_regex);

}

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
