#include "../include/class_packages.h"
#include "../include/globals.h"
#include "../include/storage.h"

#ifndef STELARE_CLI

#include "../include/gui.h"

#endif

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#include <io.h>
#endif

Package::Package(std::string package_name, std::string package_pretty_name, Package_Category category) {

    this->name = package_name;
    this->pretty_name = package_pretty_name;
    this->category = category;

}

void Package::automatic_process() {

    #ifndef STELARE_CLI
        processing_window();
        Sleep( 2000 );
    #endif

    // Downloads...
    if ( !this->downloads.empty() ) {
        for ( auto download : this->downloads ) {
            change_status( "Téléchargement de : " + download.first );
            Storage::download_in_temp_folder( download.second, download.first );
        }
    }

    // Extract All...
    if ( !this->extract_all.empty() ) {
        for ( auto extract_all : this->extract_all ) {
            change_status( "Extraction de : " + extract_all.first + " dans " + extract_all.second );
            Storage::extract_all_in_temp_folder( extract_all.first, extract_all.second );
        }
    }

    // Extract file...
    if ( !this->extract_file.empty() ) {
        for ( auto extract_file : this->extract_file ) {
            change_status( "Extraction de : " + extract_file.first + "(" + extract_file.second.first + ") dans " + extract_file.second.second );
            Storage::extract_file_in_temp_folder( extract_file.first, extract_file.second.first, extract_file.second.second );
        }
    }

    // Extract folder...
    if ( !this->extract_folder.empty() ) {
        for ( auto extract_folder : this->extract_folder ) {
            change_status( "Extraction de : " + extract_folder.first + "(" + extract_folder.second.first + ") dans " + extract_folder.second.second );
            Storage::extract_folder_in_temp_folder( extract_folder.first, extract_folder.second.first, extract_folder.second.second );
        }
    }

    // Move to executables...
    if ( !this->move_to_executables.empty() ) {
        for ( std::string move_to_executable : this->move_to_executables ) {
            change_status( "Déplacement de l'exécutable : " + move_to_executable );
            Storage::move_to_executables( move_to_executable );
        }
    }

    if ( selected_drive_letter != "" ) {

        if ( !this->move_to_drive_files.empty() ) {
            for ( auto move_to_drive_file : this->move_to_drive_files ) {
                change_status( "Copie du fichier : " + move_to_drive_file.first + " dans " + selected_drive_letter + move_to_drive_file.second );
                Storage::do_a_backup_and_copy_file_to_drive( selected_drive_letter, move_to_drive_file.second, move_to_drive_file.first );
            }
        }

        if ( !this->move_to_drive_folders.empty() ) {
            for ( auto move_to_drive_folder : this->move_to_drive_folders ) {
                change_status( "Copie du fichier : " + move_to_drive_folder.first + " dans " + selected_drive_letter + move_to_drive_folder.second );
                Storage::do_a_backup_and_copy_folder_to_drive( selected_drive_letter, move_to_drive_folder.second, move_to_drive_folder.first );
            }
        }

    }

}

void Package::add_in_package_global() {

    PACKAGES.push_back( *this );

}

