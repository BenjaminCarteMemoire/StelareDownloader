#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "../include/globals.h"
#include "../include/utils.h"
#include <ctime>
#include "../include/json.hpp"
#include "../lib/httplib/include/httplib.h"

using json = nlohmann::json;

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

std::string yesterday_date() {
    std::time_t now = std::time(nullptr) - 24 * 60 * 60;
    std::tm* tm_local = std::localtime(&now);
    char buffer[11]; // MM/DD/YYYY + null
    std::strftime(buffer, sizeof(buffer), "%m/%d/%Y", tm_local);
    return std::string(buffer);
}

std::string dynamic_download_handle( const std::string& actual_filename, std::pair<std::string,std::string>* download, Package* current_package ) {

    // GitHub part.

    std::string* url = &download->first;
    std::string* file_format = &download->second;

    std::regex github_download_regex(R"(^(?:https://github\.com)/([^/]+)/([^/]+)/releases/download/.+$)");
    std::smatch github_download_smatch;

    if ( std::regex_match( *url, github_download_smatch, github_download_regex ) ) {

        std::string owner = github_download_smatch[1];
        std::string repo = github_download_smatch[2];

        std::string build_url = "/repos/" + owner + "/" + repo + "/releases/latest";

        httplib::SSLClient cli("api.github.com");
        cli.set_follow_location(true);

        httplib::Headers headers = {
            { "User-Agent", "cpp-httplib" },
            { "Accept", "application/vnd.github.v3+json" }
        };

        auto result = cli.Get(build_url.c_str(), headers);

        if (!result)
            return actual_filename;

        if ( result && result->status == 200 ) {

            auto j = json::parse( result->body );
            if ( j.contains( "assets" ) ) {
                for ( auto& file : j["assets"] ) {

                    std::string name = file["name"];
                    std::string new_url = file["browser_download_url"];

                    if ( name.find( *file_format ) != std::string::npos && actual_filename != name ) {

                        log_info( "New update found on Github for : " + actual_filename + "; moved to :" + name );
                        *url = new_url;

                        return name;

                    }

                }
            }

        }


        return actual_filename;

    } else
        return actual_filename;

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
