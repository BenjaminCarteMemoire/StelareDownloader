#pragma once

#include <map>
#include <string>
#include "globals.h"

inline const std::map<std::string, std::map<std::string, std::string>> I18N = {

{"en", {
        { "test", "Test" },
        { "package_download_log", "Download of: " }
    }},
{"fr", {
        { "test", "Ceci est un test" },
        { "package_download_log", "Téléchargement de : "},
        { "package_dynamic_download_get_new_version", "Tentative de récupération d'une nouvelle version de : " },
        { "package_download_extract_1", "Extraction de : " },
        { "package_in", " dans " },
        { "package_move_exe", "Déplacement de l'exécutable : "},
        { "package_file_copy", "Copie du fichier : " },
        { "package_finished", "Le transfert a été effectué sur le lecteur. Vous pouvez fermer la fenêtre et quitter le gestionnaire." },
        { "package_generic_error", "Erreur dans le processus !" },
        { "package_folder_erase", "Suppression des fichiers de : "}
    }}

};

inline std::string _( std::string key ) {

    if ( locale != "en" && locale != "fr" )
        locale = "en";

    return I18N.at(locale).at(key);

}
