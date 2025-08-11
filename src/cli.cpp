#include "../include/cli.h"
#include "../include/storage.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "../include/utils.h"

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

namespace CLI_Tools {

    void clear() {

        if ( IS_WINDOWS )
            system("CLS");
    }

    void separator() {

        std::cout << "==========================" << std::endl;

    }

    void header() {

        separator();
        std::cout << "=== STELARE DOWNLOADER ===" << std::endl;
        separator();
        std::cout << std::endl;

    }

    char upper_to_lower( char c ) {

        if ( c >= 'A' && c <= 'Z' )
            c = c + ('a' - 'A');
        return c;

    }

}

namespace CLI {

    void start() {

        while ( true ) {

            CLI_Tools::clear();
            CLI_Tools::header();

            char select = select_pack();

            if ( select == 'q' || select == 'Q' )
                return;

            for ( auto package: PACKAGES ) {
                if ( select == package.identifier || select == CLI_Tools::upper_to_lower( package.identifier ) ) {
                    if ( package.callbacks.size() >= 1 )
                        package.callbacks[0]({});
                }
            }

        }

    }

    char select_pack() {

        char select;

        std::cout << "Télécharger un paquet." << std::endl << std::endl;
        for ( auto package: PACKAGES ) {
            if ( package.category == Package_Category::Pack ) {
                std::cout << package.identifier << " : " << package.pretty_name << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << "Télécharger un exécutable." << std::endl << std::endl;
        for ( auto package: PACKAGES ) {
            if ( package.category == Package_Category::Exe ) {
                std::cout << package.identifier << " : " << package.pretty_name << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << "Autres actions." << std::endl << std::endl;
        for ( auto package: PACKAGES ) {
            if ( package.category == Package_Category::Tools ) {
                std::cout << package.identifier << " : " << package.pretty_name << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << "Q : Quitter";
        std::cout << std::endl;
        CLI_Tools::separator();
        std::cout << std::endl;
        std::cout << "Votre choix : ";
        std::cin >> select;

        return select;

    }

    void warning( std::function<void(std::map<std::string, std::string> add)> callback ) {

        char c;
        CLI_Tools::separator();
        std::cout << "Êtes-vous sûr de vouloir effectuer cette action ? [o/N] ";
        std::cin >> c;

        if ( c == 'o' || c == 'O' || c == 'y' || c == 'Y' )
            callback({});
        return;

    }

    void drive_letter_prompt( std::function<void(std::map<std::string, std::string> add)> callback ) {

        while ( true ) {
            std::vector<std::string> removable_drives = Storage::return_available_removable_drives();
            CLI_Tools::clear();
            CLI_Tools::header();

            char c;

            std::cout << "Sélectionner un lecteur." << std::endl << std::endl;

            for (int i = 0; i < removable_drives.size(); i++) {
                std::cout << i << " : " << removable_drives[i] << std::endl;
            }

            std::cout << std::endl << "Q : Retour à la page précédente" << std::endl;
            CLI_Tools::separator();
            std::cout << std::endl;
            std::cout << "Votre choix : ";
            std::cin >> c;

            if ( c == 'q' || c == 'Q' )
                return;

            int ic = c - '0';
            if ( ic >= 0 && ic < removable_drives.size()  ) {

                selected_drive_letter = removable_drives[ic];
                callback({});
                return;

            }
        }
    }

    void wii_mac_address_prompt( std::function<void(std::map<std::string, std::string> add)> callback ) {

        while ( true ) {
            CLI_Tools::clear();
            CLI_Tools::header();

            std::string temp_mac_address;

            std::cout << "Entrez l'addresse MAC de votre Wii." << std::endl << std::endl;
            std::cout << "Elle est trouvable dans les paramètres Internet de votre Wii.\nExemple: 01-23-45-67-89-AB" << std::endl;
            std::cout << std::endl << "Q : Retour à la page précédente" << std::endl;
            CLI_Tools::separator();
            std::cout << std::endl;
            std::cout << "Votre addresse MAC : ";
            std::cin >> temp_mac_address;

            if ( temp_mac_address == "q" || temp_mac_address == "Q" )
                return;

            if ( verify_mac_address( temp_mac_address ) ) {
                mac_address = temp_mac_address;
                callback({});
                return;
            }
        }

    }

    void wii_version_prompt( std::function<void(std::map<std::string, std::string> add)> callback ) {

        std::vector<std::string> wii_version = { "4.3", "4.2", "4.1", "4.0", "3.5", "3.4", "3.3", "3.2", "3.1", "3.0" };

        while ( true ) {

            CLI_Tools::clear();
            CLI_Tools::header();

            char c;

            std::cout << "Sélectionner le numéro de version de votre Wii." << std::endl << std::endl;
            for ( int i = 0; i < wii_version.size(); i++ ) {
                std::cout << i << " : " + wii_version[i] << std::endl;
            }

            std::cout << std::endl << "Q : Retour à la page précédente" << std::endl;
            CLI_Tools::separator();
            std::cout << std::endl;
            std::cout << "Votre choix : ";
            std::cin >> c;

            if ( c == 'q' || c == 'Q' )
                return;

            int ic = c - '0';

            if ( ic >= 0 && ic < wii_version.size() ) {
                version = wii_version[ic];
                callback({});
                return;
            }

        }

    }

    void wii_region_prompt( std::function<void(std::map<std::string, std::string> add)> callback ) {

        std::vector<std::string> wii_region = { "E", "U", "J", "K" };

        while ( true ) {

            CLI_Tools::clear();
            CLI_Tools::header();

            char c;

            std::cout << "Sélectionner la région de votre Wii (Dans les paramètres systèmes)" << std::endl << std::endl;
            for ( int i = 0; i < wii_region.size(); i++ ) {
                std::cout << i << " : " + wii_region[i] << std::endl;
            }

            std::cout << std::endl << "Q : Retour à la page précédente" << std::endl;
            CLI_Tools::separator();
            std::cout << std::endl;
            std::cout << "Votre choix : ";
            std::cin >> c;

            if ( c == 'q' || c == 'Q' )
                return;

            int ic = c - '0';

            if ( ic >= 0 && ic < wii_region.size() ) {
                region = wii_region[ic];
                version_region = version + region;
                callback({});
                return;
            }

        }

    }

}

void change_status( std::string new_status ) {

    std::cout << new_status << std::endl;
    SUMMARY.push_back( new_status );

}

void job_done() {

    change_status( "Le transfert a été effectué sur le lecteur. Vous pouvez fermer la fenêtre et quitter le gestionnaire." );
    if ( IS_WINDOWS )
        system("pause");
    return;
}