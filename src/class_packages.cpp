#include "../include/class_packages.h"
#include "../include/globals.h"
#include "../include/storage.h"
#include "../include/utils.h"

#ifndef STELARE_CLI

#include "../include/gui.h"

#else

#include "../include/cli.h"

#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#endif

Package::Package(std::string package_name, std::string package_pretty_name, char identifier, Package_Category category) {

    this->name = package_name;
    this->pretty_name = package_pretty_name;
    this->identifier = identifier;
    this->category = category;

}

void Package::automatic_process() {

    #ifndef STELARE_CLI
        processing_window();
        Sleep( STELARE_TIME_WAIT );
    #endif

    // Downloads...
    if ( !this->downloads.empty() ) {
        for ( auto download : this->downloads ) {
            change_status( "Téléchargement de : " + download.first );
            Storage::download_in_temp_folder( download.second, download.first );
        }
    }

    // Dynamic downloads...
    if ( !this->dynamic_downloads.empty() ) {
        for ( auto &download: this->dynamic_downloads ) {
            change_status( "Tentative de récupération d'une nouvelle version de : " + download.first );
            std::string filename = dynamic_download_handle( download.first, &download.second, this );
            change_status( "Téléchargement de : " + filename );
            Storage::download_in_temp_folder( download.second.first, filename );
        }
    }

    std::string real_filename;

    // Extract All...
    if ( !this->extract_all.empty() ) {
        for ( auto extract_all : this->extract_all ) {
            real_filename = this->filename_replacer( extract_all.first );
            change_status( "Extraction de : " + real_filename + " dans " + extract_all.second );
            Storage::extract_all_in_temp_folder( real_filename, extract_all.second );
        }
    }

    // Extract file...
    if ( !this->extract_file.empty() ) {
        for ( auto extract_file : this->extract_file ) {
            real_filename = this->filename_replacer( extract_file.first );
            change_status( "Extraction de : " + real_filename + "(" + extract_file.second.first + ") dans " + extract_file.second.second );
            Storage::extract_file_in_temp_folder( real_filename, extract_file.second.first, extract_file.second.second );
        }
    }

    // Extract folder...
    if ( !this->extract_folder.empty() ) {
        for ( auto extract_folder : this->extract_folder ) {
            real_filename = this->filename_replacer( extract_folder.first );
            change_status( "Extraction de : " + real_filename + "(" + extract_folder.second.first + ") dans " + extract_folder.second.second );
            Storage::extract_folder_in_temp_folder( real_filename, extract_folder.second.first, extract_folder.second.second );
        }
    }

    // Move to executables...
    if ( !this->move_to_executables.empty() ) {
        for ( std::string move_to_executable : this->move_to_executables ) {
            real_filename = this->filename_replacer( move_to_executable );
            change_status( "Déplacement de l'exécutable : " + real_filename );
            Storage::move_to_executables( real_filename );
        }
    }

    if ( selected_drive_letter != "" ) {

        if ( !this->move_to_drive_files.empty() ) {
            for ( auto move_to_drive_file : this->move_to_drive_files ) {
                real_filename = this->filename_replacer(move_to_drive_file.first );
                change_status( "Copie du fichier : " + real_filename + " dans " + selected_drive_letter + move_to_drive_file.second );
                Storage::do_a_backup_and_copy_file_to_drive( selected_drive_letter, move_to_drive_file.second, real_filename );
            }
        }

        if ( !this->move_to_drive_folders.empty() ) {
            for ( auto move_to_drive_folder : this->move_to_drive_folders ) {
                real_filename = this->filename_replacer(move_to_drive_folder.first );
                change_status( "Copie du fichier : " + real_filename + " dans " + selected_drive_letter + move_to_drive_folder.second );
                Storage::do_a_backup_and_copy_folder_to_drive( selected_drive_letter, move_to_drive_folder.second, real_filename );
            }
        }

    }

}

void Package::add_in_package_global() {

    PACKAGES.push_back( *this );

}

std::string Package::filename_replacer(std::string filename) {

    if ( !this->_filename_replacer.empty() ) {
        for ( auto new_filename : this->_filename_replacer ) {
            int index = filename.find( new_filename.first );
            if ( index != std::string::npos ) {
                filename.replace( index, new_filename.first.size(), new_filename.second );
                break;
            }
        }
    }

    return filename;

}


void Package::filename_replacer_add(std::string old_filename, std::string new_filename) {

    if ( (this->_filename_replacer).find( old_filename ) == (this->_filename_replacer).end() )
        this->_filename_replacer.insert( { old_filename, new_filename } );

}

